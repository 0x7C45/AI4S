"""Lightweight RTL feature analysis for circuit-ID-independent strategy choice."""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class RtlFeatures:
    lines: int
    sequential_blocks: int
    arithmetic_ops: int
    mux_ops: int
    compare_ops: int
    memory_declarations: int

    @property
    def is_sequential(self) -> bool:
        return self.sequential_blocks > 0


def _without_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.DOTALL)
    return re.sub(r"//[^\n]*", " ", text)


def analyze_rtl(path: Path) -> RtlFeatures:
    raw = path.read_text(encoding="utf-8", errors="replace")
    text = _without_comments(raw)
    return RtlFeatures(
        lines=len(raw.splitlines()),
        sequential_blocks=len(re.findall(r"\b(?:always_ff|always)\b[^\n]*\b(?:posedge|negedge)\b", text)),
        arithmetic_ops=len(re.findall(r"(?<![+\-*/])(?:\+|-|\*|/)(?![+\-*/])", text)),
        mux_ops=text.count("?") + len(re.findall(r"\bcase[xz]?\s*\(", text)),
        compare_ops=len(re.findall(r"(?:==|!=|<=|>=|<|>)", text)),
        memory_declarations=len(re.findall(r"\breg\s*(?:\[[^\]]+\]\s*)?\w+\s*\[[^\]]+\]", text)),
    )


def adaptive_profile(requested: str, features: RtlFeatures) -> str:
    """Refine a generic objective from observable structure, never circuit ID."""
    if requested not in {"balanced", "area", "timing"}:
        return requested
    if requested == "balanced":
        if features.arithmetic_ops > max(8, features.mux_ops * 2):
            return "area"
        if features.mux_ops + features.compare_ops > max(12, features.arithmetic_ops * 2):
            return "timing"
    if requested == "area" and features.lines > 2500:
        return "deep-area"
    if requested == "timing" and features.is_sequential and features.lines > 800:
        return "deep-timing"
    return requested
