#!/usr/bin/env python3
"""AdaptiveYosys contest entry point."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from config import ConfigError, select_point
from rtl_analysis import analyze_rtl
from sdc import delay_target_ps
from yosys_flow import SynthesisError, run_yosys


def _readable_file(value: str, label: str) -> Path:
    path = Path(value).expanduser()
    if not path.is_file():
        raise ValueError(f"{label} is not a readable file: {path}")
    return path


def parser() -> argparse.ArgumentParser:
    result = argparse.ArgumentParser(description="Adaptive offline RTL synthesis with Yosys/ABC")
    result.add_argument("--rtl", required=True)
    result.add_argument("--top", required=True)
    result.add_argument("--sdc", required=True)
    result.add_argument("--liberty", required=True)
    result.add_argument("--config", required=True)
    result.add_argument("--circuit", required=True)
    result.add_argument("--point", required=True, type=int)
    result.add_argument("--output", required=True, help="Required netlist output path")
    return result


def main(argv: list[str] | None = None) -> int:
    args = parser().parse_args(argv)
    try:
        rtl = _readable_file(args.rtl, "RTL")
        sdc = _readable_file(args.sdc, "SDC")
        liberty = _readable_file(args.liberty, "LIBERTY")
        config = _readable_file(args.config, "CONFIG")
        if not args.top.strip():
            raise ValueError("TOP must not be empty")
        if args.point < 1:
            raise ValueError("POINT must be at least 1")
        output = Path(args.output).expanduser()
        output.parent.mkdir(parents=True, exist_ok=True)

        point, selected_key = select_point(config, args.circuit, args.point)
        features = analyze_rtl(rtl)
        base_delay_ps = delay_target_ps(sdc)
        scaled_delay_ps = max(1, round(base_delay_ps * point.delay_scale))
        metadata = run_yosys(
            rtl=rtl,
            top=args.top,
            liberty=liberty,
            sdc=sdc,
            final_output=output,
            point=point,
            features=features,
            delay_ps=scaled_delay_ps,
        )
        print(
            f"synthesis complete: circuit={args.circuit} config={selected_key} "
            f"point={args.point} profile={metadata['resolved_profile']} output={output}"
        )
        return 0
    except (ValueError, OSError, ConfigError, SynthesisError) as exc:
        print(f"synth_tool: error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
