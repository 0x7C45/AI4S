import tempfile
import unittest
from pathlib import Path

from gate_sizing import insert_high_fanout_buffers, upsize_high_fanout_gates


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

    def test_inserts_buffer_between_driver_and_high_fanout_loads(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            liberty = root / "cells.lib"
            liberty.write_text(
                "cell (BUF_X8) { pin (A) { direction: input; } pin (Z) { direction: output; } }\n"
                "cell (DFFR_X1) {}\ncell (INV_X1) {}\n"
            )
            netlist = root / "netlist.v"
            netlist.write_text(
                "module top(input d, input ck, output y0, y1, y2);\n"
                "  wire q;\n"
                "  DFFR_X1 ff ( .D(d), .CK(ck), .Q(q) );\n"
                "  INV_X1 u0 ( .A(q), .ZN(y0) );\n"
                "  INV_X1 u1 ( .A(q), .ZN(y1) );\n"
                "  INV_X1 u2 ( .A(q), .ZN(y2) );\n"
                "endmodule\n"
            )
            changed = insert_high_fanout_buffers(netlist, liberty, threshold=3, strength=8)
            text = netlist.read_text()
            self.assertEqual(changed, 1)
            self.assertIn("wire __a3_buffer_net_0;", text)
            self.assertIn(".Q(__a3_buffer_net_0)", text)
            self.assertIn("BUF_X8 __a3_buffer_0 ( .A(__a3_buffer_net_0), .Z(q) );", text)
            self.assertEqual(text.count(".A(q)"), 3)

    def test_skips_buffer_insertion_when_variant_is_unavailable(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            liberty = root / "cells.lib"
            liberty.write_text(
                "cell (BUF_X4) { pin (A) { direction: input; } pin (Z) { direction: output; } }\n"
                "cell (INV_X1) {}\n"
            )
            netlist = root / "netlist.v"
            original = (
                "module top(input a, output y0, y1); wire n;\n"
                "INV_X1 d (.A(a), .ZN(n));\n"
                "INV_X1 u0 (.A(n), .ZN(y0));\n"
                "INV_X1 u1 (.A(n), .ZN(y1));\nendmodule\n"
            )
            netlist.write_text(original)
            self.assertEqual(insert_high_fanout_buffers(netlist, liberty, threshold=2, strength=8), 0)
            self.assertEqual(netlist.read_text(), original)

    def test_buffer_preserves_escaped_net_terminator(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            liberty = root / "cells.lib"
            liberty.write_text(
                "cell (BUF_X16) { pin (A) { direction: input; } pin (Z) { direction: output; } }\n"
                "cell (INV_X1) {}\n"
            )
            netlist = root / "netlist.v"
            netlist.write_text(
                "module top(input a, output y0, y1);\nwire \\escaped.net ;\n"
                "INV_X1 d (.A(a), .ZN(\\escaped.net ));\n"
                "INV_X1 u0 (.A(\\escaped.net ), .ZN(y0));\n"
                "INV_X1 u1 (.A(\\escaped.net ), .ZN(y1));\nendmodule\n"
            )
            self.assertEqual(insert_high_fanout_buffers(netlist, liberty, threshold=2, strength=16), 1)
            self.assertIn(".Z(\\escaped.net )", netlist.read_text())

    def test_skips_buffer_insertion_for_multimodule_netlist(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            liberty = root / "cells.lib"
            liberty.write_text(
                "cell (BUF_X8) { pin (A) { direction: input; } pin (Z) { direction: output; } }\n"
            )
            netlist = root / "netlist.v"
            original = (
                "module helper(input a, output y); assign y = a; endmodule\n"
                "module top(input a, output y0, y1); wire n;\n"
                "INV_X1 d (.A(a), .ZN(n));\n"
                "INV_X1 u0 (.A(n), .ZN(y0));\n"
                "INV_X1 u1 (.A(n), .ZN(y1));\nendmodule\n"
            )
            netlist.write_text(original)
            self.assertEqual(insert_high_fanout_buffers(netlist, liberty, threshold=2, strength=8), 0)
            self.assertEqual(netlist.read_text(), original)

    def test_requires_compatible_buffer_pin_directions(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            liberty = root / "cells.lib"
            liberty.write_text(
                "cell (BUF_X8) { pin (I) { direction: input; } pin (O) { direction: output; } }\n"
            )
            netlist = root / "netlist.v"
            original = (
                "module top(input a, output y0, y1); wire n;\n"
                "INV_X1 d (.A(a), .ZN(n));\n"
                "INV_X1 u0 (.A(n), .ZN(y0));\n"
                "INV_X1 u1 (.A(n), .ZN(y1));\nendmodule\n"
            )
            netlist.write_text(original)
            self.assertEqual(insert_high_fanout_buffers(netlist, liberty, threshold=2, strength=8), 0)
            self.assertEqual(netlist.read_text(), original)
