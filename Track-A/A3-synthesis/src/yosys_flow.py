"""Yosys/ABC program generation and safe execution."""

from __future__ import annotations

import json
import os
import shutil
import subprocess
from pathlib import Path

from config import PointConfig
from gate_sizing import upsize_high_fanout_gates
from rtl_analysis import RtlFeatures, adaptive_profile


class SynthesisError(RuntimeError):
    """Raised when synthesis cannot produce a valid netlist."""


COMPRESS = "balance; rewrite; rewrite -z; balance; rewrite -z; balance"
RESYN = "balance; rewrite; refactor; balance; rewrite; rewrite -z; balance; refactor -z; rewrite -z; balance"
IF_K6 = "if -K 6 -g -C 8"


def _mapping(delay_ps: int) -> str:
    return f"&get -n; &dch -f; &nf -D {delay_ps}; &put"


def abc_script(point: PointConfig, features: RtlFeatures, delay_ps: int) -> tuple[str, str]:
    if point.abc_script:
        script = point.abc_script.strip()
        if "&nf" not in script and not any(token in script for token in ("map", "amap")):
            script = f"{script}; {_mapping(delay_ps)}"
        return (script if script.startswith("+") else f"+strash; {script}"), "custom"

    profile = adaptive_profile(point.profile, features) if point.adaptive else point.profile
    sequences = {
        "balanced": f"{COMPRESS}; {_mapping(delay_ps)}",
        "area": f"{RESYN}; {_mapping(delay_ps)}",
        "timing": f"{IF_K6}; {_mapping(delay_ps)}",
        "deep-area": f"{COMPRESS}; {COMPRESS}; {_mapping(delay_ps)}",
        "deep-timing": f"{IF_K6}; {IF_K6}; {_mapping(delay_ps)}",
    }
    if profile not in sequences:
        raise SynthesisError(f"unknown optimization profile: {profile}")
    return f"+strash; {sequences[profile]}", profile


def _quote(value: str | Path) -> str:
    text = str(value)
    # Yosys command scripts do not treat shell-style double quotes as string
    # delimiters: `hierarchy -top "top"` asks for a module literally named
    # `"top"`.  Contest paths are normal absolute POSIX paths, so emit a raw
    # token after rejecting characters that could split or inject commands.
    if any(char.isspace() for char in text) or any(char in text for char in ";\n\r\""):
        raise SynthesisError("Yosys paths and module names may not contain whitespace, quotes, or semicolons")
    return text


def _abc_script_token(value: str) -> str:
    if "\n" in value or "\r" in value or '"' in value:
        raise SynthesisError("ABC scripts may not contain newlines or double quotes")
    return f'"{value}"'


def render_script(
    rtl: Path,
    top: str,
    liberty: Path,
    output: Path,
    script: str,
    synth_options: tuple[str, ...] = (),
) -> str:
    synth_suffix = "" if not synth_options else " " + " ".join(synth_options)
    commands = [
        f"read_verilog -sv {_quote(rtl)}",
        f"hierarchy -check -top {_quote(top)}",
        f"synth -top {_quote(top)} -flatten -noabc{synth_suffix}",
    ]
    commands.append("opt_clean -purge")
    commands.extend(
        [
            f"dfflibmap -liberty {_quote(liberty)}",
            f"abc -liberty {_quote(liberty)} -script {_abc_script_token(script)}",
            "clean -purge",
            f"stat -liberty {_quote(liberty)}",
            "setundef -zero",
            # `splitnets -driver` disconnects vector top-level outputs in
            # Yosys 0.54 (for example LSV04's x_out[5:0]).  Keep vectors
            # intact: ABC has already completed mapping and the Verilog
            # backend preserves legal bus connections without this pass.
            "clean -purge",
            "check",
            "select -assert-none t:$*",
            f"write_verilog -noattr -noexpr {_quote(output)}",
            "",
        ]
    )
    return "\n".join(commands)


def _resolve_yosys() -> str:
    configured = os.environ.get("YOSYS_BIN", "yosys")
    candidates = [configured]
    # The official SiliconCompiler image installs Yosys here but does not add
    # the directory to its default PATH.
    if configured == "yosys":
        candidates.append("/root/.local/bin/yosys")
    for candidate in candidates:
        resolved = shutil.which(candidate)
        if resolved:
            return resolved
    raise SynthesisError(
        f"Yosys executable {configured!r} was not found; set YOSYS_BIN or use the contest image"
    )


def run_yosys(
    *,
    rtl: Path,
    top: str,
    liberty: Path,
    final_output: Path,
    point: PointConfig,
    features: RtlFeatures,
    delay_ps: int,
) -> dict[str, object]:
    # The Yosys process runs with OUT_DIR as its working directory.  Make all
    # generated paths absolute first, otherwise a relative OUT_DIR is applied
    # twice when Yosys opens its log/script files.
    final_output = final_output.resolve()
    out_dir = final_output.parent
    work_dir = out_dir / ".synth_tool"
    work_dir.mkdir(parents=True, exist_ok=True)
    temporary_output = work_dir / "netlist.pending.v"
    metadata_path = work_dir / "run.json"
    final_output.unlink(missing_ok=True)
    temporary_output.unlink(missing_ok=True)

    sequence, resolved_profile = abc_script(point, features, delay_ps)
    attempts = [(sequence, resolved_profile)]
    if point.fallback_on_error and resolved_profile != "balanced":
        conservative = PointConfig(
            name=f"{point.name}-fallback",
            profile="balanced",
            timeout_seconds=point.timeout_seconds,
            synth_options=point.synth_options,
            upsize_fanout_threshold=point.upsize_fanout_threshold,
            upsize_strength=point.upsize_strength,
        )
        attempts.append(abc_script(conservative, features, delay_ps))
    metadata = {
        "point": point.name,
        "requested_profile": point.profile,
        "resolved_profile": resolved_profile,
        "delay_target_ps": delay_ps,
        "delay_scale": point.delay_scale,
        "features": features.__dict__,
        "attempts": [],
    }
    yosys = _resolve_yosys()
    last_error = "Yosys did not run"
    for index, (attempt_sequence, attempt_profile) in enumerate(attempts, 1):
        suffix = "" if index == 1 else f".retry{index}"
        script_path = work_dir / f"run{suffix}.ys"
        log_path = work_dir / f"yosys{suffix}.log"
        temporary_output.unlink(missing_ok=True)
        script_path.write_text(
            render_script(
                rtl.resolve(),
                top,
                liberty.resolve(),
                temporary_output.resolve(),
                attempt_sequence,
                point.synth_options,
            ),
            encoding="utf-8",
        )
        command = [yosys, "-q", "-l", str(log_path), "-s", str(script_path)]
        try:
            completed = subprocess.run(
                command,
                cwd=out_dir,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                timeout=point.timeout_seconds,
                check=False,
            )
        except subprocess.TimeoutExpired as exc:
            metadata["attempts"].append({"profile": attempt_profile, "status": "timeout"})
            metadata_path.write_text(json.dumps(metadata, indent=2, sort_keys=True), encoding="utf-8")
            raise SynthesisError(
                f"Yosys exceeded {point.timeout_seconds}s; generated script: {script_path}"
            ) from exc

        succeeded = (
            completed.returncode == 0
            and temporary_output.is_file()
            and temporary_output.stat().st_size > 0
        )
        metadata["attempts"].append(
            {"profile": attempt_profile, "status": "ok" if succeeded else f"exit-{completed.returncode}"}
        )
        if succeeded:
            metadata["resolved_profile"] = attempt_profile
            if point.upsize_fanout_threshold is not None:
                metadata["upsized_cells"] = upsize_high_fanout_gates(
                    temporary_output,
                    liberty,
                    threshold=point.upsize_fanout_threshold,
                    strength=point.upsize_strength,
                )
            break
        diagnostic = completed.stderr.strip().splitlines()[-1:] or completed.stdout.strip().splitlines()[-1:]
        detail = f" ({diagnostic[0]})" if diagnostic else ""
        last_error = f"Yosys failed with exit code {completed.returncode}{detail}; log: {log_path}"
    else:
        metadata_path.write_text(json.dumps(metadata, indent=2, sort_keys=True), encoding="utf-8")
        raise SynthesisError(last_error)

    metadata_path.write_text(json.dumps(metadata, indent=2, sort_keys=True), encoding="utf-8")
    os.replace(temporary_output, final_output)
    return metadata
