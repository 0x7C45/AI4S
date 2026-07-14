"""Parser for the scalar subset used by public problem.yaml files."""

from __future__ import annotations

from pathlib import Path
from typing import Any


def _scalar(value: str) -> Any:
    value = value.strip().strip("'\"")
    if value.lower() in {"true", "false"}:
        return value.lower() == "true"
    try:
        return float(value) if "." in value else int(value)
    except ValueError:
        return value


def parse_problem(path: Path) -> dict[str, Any]:
    result: dict[str, Any] = {}
    for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        stripped = line.strip()
        if not stripped or stripped.startswith("#"):
            continue
        if ":" not in stripped:
            raise ValueError(f"unsupported problem metadata at {path}:{number}")
        key, value = stripped.split(":", 1)
        result[key.strip()] = _scalar(value.split(" #", 1)[0])
    return result
