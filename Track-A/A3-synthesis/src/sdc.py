"""Minimal, dependency-free timing extraction from contest SDC files."""

from __future__ import annotations

import re
from pathlib import Path


_SET_RE = re.compile(r"^\s*set\s+([A-Za-z_][A-Za-z0-9_]*)\s+([0-9]+(?:\.[0-9]+)?)\s*(?:#.*)?$")
_PERIOD_RE = re.compile(r"\bcreate_clock\b[^\n]*?\s-period\s+(\$\{?[A-Za-z_][A-Za-z0-9_]*\}?|[0-9]+(?:\.[0-9]+)?)")


def clock_period_ns(path: Path, default: float = 10.0) -> float:
    text = path.read_text(encoding="utf-8", errors="replace")
    variables: dict[str, float] = {}
    for line in text.splitlines():
        match = _SET_RE.match(line)
        if match:
            variables[match.group(1)] = float(match.group(2))

    match = _PERIOD_RE.search(text)
    if not match:
        return default
    token = match.group(1)
    if token.startswith("$"):
        name = token[1:].strip("{}")
        return variables.get(name, default)
    value = float(token)
    return value if value > 0 else default


def delay_target_ps(path: Path, default_ns: float = 10.0) -> int:
    return max(1, round(clock_period_ns(path, default_ns) * 1000.0))
