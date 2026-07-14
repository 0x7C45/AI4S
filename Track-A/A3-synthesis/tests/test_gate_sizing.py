import tempfile
import unittest
from pathlib import Path

from gate_sizing import upsize_high_fanout_gates


class GateSizingTests(unittest.TestCase):
    def test_upsizes_supported_high_fanout_combinational_gate_only(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            liberty = root / "cells.lib"
            liberty.write_text("cell (INV_X1) {}\ncell (INV_X4) {}\ncell (DFF_X1) {}\ncell (DFF_X4) {}\n")
            netlist = root / "netlist.v"
            netlist.write_text(
                "module top(input a, input ck, output y);\n"
                "  wire n; wire q;\n"
                "  INV_X1 u0 ( .A(a), .ZN(n) );\n"
                "  INV_X1 u1 ( .A(n), .ZN(y) );\n"
                "  INV_X1 u2 ( .A(n), .ZN(q) );\n"
                "  DFF_X1 ff ( .D(n), .CK(ck), .Q(q) );\n"
                "endmodule\n"
            )
            changed = upsize_high_fanout_gates(netlist, liberty, threshold=3, strength=4)
            text = netlist.read_text()
            self.assertEqual(changed, 1)
            self.assertIn("INV_X4 u0", text)
            self.assertIn("INV_X1 u1", text)
            self.assertIn("DFF_X1 ff", text)

    def test_skips_cell_without_requested_liberty_variant(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            liberty = root / "cells.lib"
            liberty.write_text("cell (NAND2_X1) {}\n")
            netlist = root / "netlist.v"
            netlist.write_text(
                "module top(input a,b, output y,z); wire n;\n"
                "NAND2_X1 u0 (.A1(a), .A2(b), .ZN(n));\n"
                "NAND2_X1 u1 (.A1(n), .A2(b), .ZN(y));\n"
                "NAND2_X1 u2 (.A1(n), .A2(a), .ZN(z));\nendmodule\n"
            )
            self.assertEqual(upsize_high_fanout_gates(netlist, liberty, threshold=2, strength=4), 0)
