import tempfile
import unittest
from pathlib import Path

from timing_sizing import upsize_reported_critical_cells


class TimingSizingTests(unittest.TestCase):
    def test_upsizes_frequently_critical_pin_compatible_cells(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            netlist = root / "netlist.v"
            netlist.write_text(
                "module top(input a, output y);\n"
                "INV_X1 u0 (.A(a), .ZN(n));\n"
                "NAND2_X1 u1 (.A1(n), .A2(a), .ZN(y));\nendmodule\n"
            )
            liberty = root / "cells.lib"
            liberty.write_text("cell (INV_X1) {} cell (INV_X2) {} cell (NAND2_X1) {}\n")
            report = root / "paths.rpt"
            report.write_text(
                "Startpoint: in\n  0.1 ^ u0/ZN (INV_X1)\n  0.2 v u1/ZN (NAND2_X1)\n"
                "Startpoint: in2\n  0.1 ^ u0/ZN (INV_X1)\n"
            )
            changed = upsize_reported_critical_cells(
                netlist, liberty, report, strength=2, paths=2, max_cells=2
            )
            self.assertEqual(changed, 1)
            self.assertIn("INV_X2 u0", netlist.read_text())
            self.assertIn("NAND2_X1 u1", netlist.read_text())


if __name__ == "__main__":
    unittest.main()
