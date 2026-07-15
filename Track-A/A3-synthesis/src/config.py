"""Point configuration loading and validation."""

from __future__ import annotations

import json
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any


class ConfigError(ValueError):
    """Raised when the contest point configuration is invalid."""


@dataclass(frozen=True)
class PointConfig:
    name: str
    profile: str = "balanced"
    abc_script: str | None = None
    adaptive: bool = False
    fallback_on_error: bool = False
    timeout_seconds: int = 600
    delay_scale: float = 1.0
    synth_options: tuple[str, ...] = ()
    upsize_fanout_threshold: int | None = None
    upsize_strength: int = 4
    buffer_fanout_threshold: int | None = None
    buffer_strength: int = 16
    buffer_group_size: int | None = None
    critical_path_upsize_cells: int | None = None
    critical_path_count: int = 50
    critical_path_strength: int = 2
    extra: dict[str, Any] = field(default_factory=dict)


def _validate_entries(key: str, entries: Any) -> list[Any]:
    if not isinstance(entries, list) or not 1 <= len(entries) <= 7:
        raise ConfigError(f"configuration key {key!r} must contain 1-7 points")
    return entries


def load_config(path: Path) -> dict[str, list[Any]]:
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except OSError as exc:
        raise ConfigError(f"cannot read configuration {path}: {exc}") from exc
    except json.JSONDecodeError as exc:
        raise ConfigError(f"invalid JSON in {path}: {exc}") from exc
    if not isinstance(data, dict):
        raise ConfigError("configuration root must be a JSON object")
    if "$default" not in data:
        raise ConfigError("configuration must define a $default fallback")
    return {str(key): _validate_entries(str(key), value) for key, value in data.items()}


def _normalize(raw: Any, index: int) -> PointConfig:
    if isinstance(raw, str):
        return PointConfig(name=f"point-{index}", abc_script=raw)
    if isinstance(raw, list) and all(isinstance(item, str) for item in raw):
        return PointConfig(name=f"point-{index}", abc_script="; ".join(raw))
    if not isinstance(raw, dict):
        raise ConfigError(f"point {index} must be an object, string, or string array")

    known = {
        "name",
        "profile",
        "abc_script",
        "adaptive",
        "fallback_on_error",
        "timeout_seconds",
        "delay_scale",
        "synth_options",
        "upsize_fanout_threshold",
        "upsize_strength",
        "buffer_fanout_threshold",
        "buffer_strength",
        "buffer_group_size",
        "critical_path_upsize_cells",
        "critical_path_count",
        "critical_path_strength",
    }
    timeout = raw.get("timeout_seconds", 600)
    if not isinstance(timeout, int) or timeout < 1:
        raise ConfigError(f"point {index} timeout_seconds must be a positive integer")
    profile = raw.get("profile", "balanced")
    if not isinstance(profile, str) or not profile:
        raise ConfigError(f"point {index} profile must be a non-empty string")
    script = raw.get("abc_script")
    if script is not None and not isinstance(script, str):
        raise ConfigError(f"point {index} abc_script must be a string")
    delay_scale = raw.get("delay_scale", 1.0)
    if isinstance(delay_scale, bool) or not isinstance(delay_scale, (int, float)) or delay_scale <= 0:
        raise ConfigError(f"point {index} delay_scale must be a positive number")
    synth_options = raw.get("synth_options", [])
    allowed_synth_options = {"-nofsm", "-noalumacc", "-noshare", "-nordff", "-no-rw-check"}
    if (
        not isinstance(synth_options, list)
        or not all(isinstance(option, str) and option in allowed_synth_options for option in synth_options)
        or len(synth_options) != len(set(synth_options))
    ):
        raise ConfigError(
            f"point {index} synth_options must be a unique list containing only supported synth flags"
        )
    upsize_threshold = raw.get("upsize_fanout_threshold")
    if upsize_threshold is not None and (
        isinstance(upsize_threshold, bool) or not isinstance(upsize_threshold, int) or upsize_threshold < 2
    ):
        raise ConfigError(f"point {index} upsize_fanout_threshold must be an integer of at least 2")
    upsize_strength = raw.get("upsize_strength", 4)
    if isinstance(upsize_strength, bool) or upsize_strength not in {2, 4}:
        raise ConfigError(f"point {index} upsize_strength must be 2 or 4")
    buffer_threshold = raw.get("buffer_fanout_threshold")
    if buffer_threshold is not None and (
        isinstance(buffer_threshold, bool)
        or not isinstance(buffer_threshold, int)
        or buffer_threshold < 2
    ):
        raise ConfigError(f"point {index} buffer_fanout_threshold must be an integer of at least 2")
    buffer_strength = raw.get("buffer_strength", 16)
    if isinstance(buffer_strength, bool) or buffer_strength not in {2, 4, 8, 16}:
        raise ConfigError(f"point {index} buffer_strength must be one of 2, 4, 8, or 16")
    buffer_group_size = raw.get("buffer_group_size")
    if buffer_group_size is not None and (
        isinstance(buffer_group_size, bool)
        or not isinstance(buffer_group_size, int)
        or not 2 <= buffer_group_size <= 256
    ):
        raise ConfigError(f"point {index} buffer_group_size must be an integer from 2 to 256")
    if buffer_group_size is not None and buffer_threshold is None:
        raise ConfigError(f"point {index} buffer_group_size requires buffer_fanout_threshold")
    critical_cells = raw.get("critical_path_upsize_cells")
    if critical_cells is not None and (
        isinstance(critical_cells, bool) or not isinstance(critical_cells, int) or not 1 <= critical_cells <= 500
    ):
        raise ConfigError(f"point {index} critical_path_upsize_cells must be an integer from 1 to 500")
    critical_paths = raw.get("critical_path_count", 50)
    if isinstance(critical_paths, bool) or not isinstance(critical_paths, int) or not 1 <= critical_paths <= 200:
        raise ConfigError(f"point {index} critical_path_count must be an integer from 1 to 200")
    critical_strength = raw.get("critical_path_strength", 2)
    if isinstance(critical_strength, bool) or critical_strength not in {2, 4}:
        raise ConfigError(f"point {index} critical_path_strength must be 2 or 4")
    return PointConfig(
        name=str(raw.get("name", f"point-{index}")),
        profile=profile,
        abc_script=script,
        adaptive=bool(raw.get("adaptive", False)),
        fallback_on_error=bool(raw.get("fallback_on_error", False)),
        timeout_seconds=timeout,
        delay_scale=float(delay_scale),
        synth_options=tuple(synth_options),
        upsize_fanout_threshold=upsize_threshold,
        upsize_strength=upsize_strength,
        buffer_fanout_threshold=buffer_threshold,
        buffer_strength=buffer_strength,
        buffer_group_size=buffer_group_size,
        critical_path_upsize_cells=critical_cells,
        critical_path_count=critical_paths,
        critical_path_strength=critical_strength,
        extra={key: value for key, value in raw.items() if key not in known},
    )


def select_point(path: Path, circuit: str, point: int) -> tuple[PointConfig, str]:
    config = load_config(path)
    selected_key = circuit if circuit in config else "$default"
    entries = config[selected_key]
    if not 1 <= point <= len(entries):
        raise ConfigError(
            f"POINT={point} is outside 1..{len(entries)} for configuration key {selected_key}"
        )
    return _normalize(entries[point - 1], point), selected_key
