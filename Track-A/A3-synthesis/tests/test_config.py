import json
import tempfile
import unittest
from pathlib import Path

from config import ConfigError, load_config, select_point


class ConfigTests(unittest.TestCase):
    def write(self, data):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        path = Path(directory.name) / "config.json"
        path.write_text(json.dumps(data), encoding="utf-8")
        return path

    def test_selects_circuit_point(self):
        path = self.write({"$default": [{"profile": "balanced"}], "LSV01": [{"profile": "area"}]})
        point, key = select_point(path, "LSV01", 1)
        self.assertEqual((point.profile, key), ("area", "LSV01"))

    def test_unknown_circuit_uses_default(self):
        path = self.write({"$default": [{"profile": "timing", "adaptive": True}]})
        point, key = select_point(path, "HIDDEN", 1)
        self.assertEqual(key, "$default")
        self.assertTrue(point.adaptive)

    def test_rejects_out_of_range_point(self):
        path = self.write({"$default": [{"profile": "balanced"}]})
        with self.assertRaises(ConfigError):
            select_point(path, "HIDDEN", 2)

    def test_rejects_missing_default(self):
        path = self.write({"LSV01": [{"profile": "area"}]})
        with self.assertRaises(ConfigError):
            select_point(path, "LSV01", 1)

    def test_reads_delay_scale(self):
        path = self.write({"$default": [{"profile": "timing", "delay_scale": 0.25}]})
        point, _ = select_point(path, "HIDDEN", 1)
        self.assertEqual(point.delay_scale, 0.25)

    def test_rejects_invalid_delay_scale(self):
        for value in (0, -0.1, "fast", True):
            path = self.write({"$default": [{"delay_scale": value}]})
            with self.subTest(value=value), self.assertRaises(ConfigError):
                select_point(path, "HIDDEN", 1)

    def test_reads_safe_synth_options(self):
        path = self.write({"$default": [{"synth_options": ["-noalumacc", "-noshare"]}]})
        point, _ = select_point(path, "HIDDEN", 1)
        self.assertEqual(point.synth_options, ("-noalumacc", "-noshare"))

    def test_rejects_unsafe_or_duplicate_synth_options(self):
        for value in (["-noabc"], ["-noalumacc", "-noalumacc"], "-noalumacc"):
            path = self.write({"$default": [{"synth_options": value}]})
            with self.subTest(value=value), self.assertRaises(ConfigError):
                select_point(path, "HIDDEN", 1)

    def test_reads_gate_sizing_options(self):
        path = self.write({"$default": [{"upsize_fanout_threshold": 100, "upsize_strength": 4}]})
        point, _ = select_point(path, "HIDDEN", 1)
        self.assertEqual((point.upsize_fanout_threshold, point.upsize_strength), (100, 4))

    def test_rejects_invalid_gate_sizing_options(self):
        for value in (0, 1, True, 1.5, "100"):
            path = self.write({"$default": [{"upsize_fanout_threshold": value}]})
            with self.subTest(value=value), self.assertRaises(ConfigError):
                select_point(path, "HIDDEN", 1)
        path = self.write({"$default": [{"upsize_strength": 8}]})
        with self.assertRaises(ConfigError):
            select_point(path, "HIDDEN", 1)

    def test_reads_high_fanout_buffer_options(self):
        path = self.write({"$default": [{"buffer_fanout_threshold": 25, "buffer_strength": 16, "buffer_group_size": 12}]})
        point, _ = select_point(path, "HIDDEN", 1)
        self.assertEqual((point.buffer_fanout_threshold, point.buffer_strength), (25, 16))
        self.assertEqual(point.buffer_group_size, 12)

    def test_rejects_invalid_high_fanout_buffer_options(self):
        for value in (0, 1, True, 1.5, "25"):
            path = self.write({"$default": [{"buffer_fanout_threshold": value}]})
            with self.subTest(value=value), self.assertRaises(ConfigError):
                select_point(path, "HIDDEN", 1)
        path = self.write({"$default": [{"buffer_strength": 32}]})
        with self.assertRaises(ConfigError):
            select_point(path, "HIDDEN", 1)
        for value in (0, 1, 257, True, 1.5, "16"):
            path = self.write({"$default": [{"buffer_fanout_threshold": 25, "buffer_group_size": value}]})
            with self.subTest(group_size=value), self.assertRaises(ConfigError):
                select_point(path, "HIDDEN", 1)
        path = self.write({"$default": [{"buffer_group_size": 16}]})
        with self.assertRaises(ConfigError):
            select_point(path, "HIDDEN", 1)

    def test_submission_config_has_valid_unique_points(self):
        path = Path(__file__).resolve().parents[1] / "config.json"
        config = load_config(path)
        self.assertEqual(set(config), {"$default", *(f"LSV{i:02d}" for i in range(1, 11))})
        for circuit, entries in config.items():
            points = [select_point(path, circuit, index)[0] for index in range(1, len(entries) + 1)]
            names = [point.name for point in points]
            with self.subTest(circuit=circuit):
                self.assertEqual(len(names), len(set(names)))

    def test_reads_and_validates_critical_path_sizing(self):
        path = self.write({"$default": [{"critical_path_upsize_cells": 25, "critical_path_count": 40, "critical_path_strength": 2}]})
        point, _ = select_point(path, "HIDDEN", 1)
        self.assertEqual((point.critical_path_upsize_cells, point.critical_path_count), (25, 40))
        for field, value in (
            ("critical_path_upsize_cells", 0),
            ("critical_path_upsize_cells", 501),
            ("critical_path_count", 0),
            ("critical_path_count", 201),
            ("critical_path_strength", 8),
        ):
            with self.subTest(field=field, value=value), self.assertRaises(ConfigError):
                select_point(self.write({"$default": [{field: value}]}), "HIDDEN", 1)


if __name__ == "__main__":
    unittest.main()
