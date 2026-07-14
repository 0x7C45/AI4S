import tempfile
import subprocess
import unittest
from pathlib import Path
from unittest.mock import patch

from config import PointConfig
from rtl_analysis import RtlFeatures, adaptive_profile, analyze_rtl
from sdc import clock_period_ns, delay_target_ps
from yosys_flow import _resolve_yosys, abc_script, render_script, run_yosys
from verify import _ideal_cell_library, parse_top_interface, render_testbench


class FlowTests(unittest.TestCase):
    def temp_file(self, text, name="input.txt"):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        path = Path(directory.name) / name
        path.write_text(text, encoding="utf-8")
        return path

    def test_variable_clock_period(self):
        sdc = self.temp_file("set CLK_PERIOD 7.500\ncreate_clock -period $CLK_PERIOD [get_ports clk]\n")
        self.assertEqual(clock_period_ns(sdc), 7.5)
        self.assertEqual(delay_target_ps(sdc), 7500)

    def test_literal_clock_period(self):
        sdc = self.temp_file("create_clock -name clk -period 3.2 [get_ports clk]\n")
        self.assertEqual(clock_period_ns(sdc), 3.2)

    def test_rtl_features_and_adaptation(self):
        rtl = self.temp_file("module m(input clk, input [7:0] a,b, output reg [7:0] y); always @(posedge clk) y <= a*b+a; endmodule", "m.v")
        features = analyze_rtl(rtl)
        self.assertTrue(features.is_sequential)
        self.assertGreaterEqual(features.arithmetic_ops, 2)
        large = RtlFeatures(3000, 1, 40, 2, 2, 0)
        self.assertEqual(adaptive_profile("area", large), "deep-area")

    def test_abc_profiles_are_mapped(self):
        features = RtlFeatures(10, 0, 0, 0, 0, 0)
        script, profile = abc_script(PointConfig(name="p", profile="timing"), features, 10000)
        self.assertEqual(profile, "timing")
        self.assertIn("&nf -D 10000", script)
        self.assertTrue(script.startswith("+strash"))

    def test_delay_scale_changes_mapping_target(self):
        features = RtlFeatures(10, 0, 0, 0, 0, 0)
        point = PointConfig(name="tight", profile="timing", delay_scale=0.25)
        script, _ = abc_script(point, features, 2500)
        self.assertIn("&nf -D 2500", script)

    def test_yosys_script_has_required_stages(self):
        text = render_script(Path("a.v"), "top", Path("cells.lib"), Path("netlist.v"), "+strash; map")
        self.assertIn("hierarchy -check -top", text)
        self.assertIn("hierarchy -check -top top", text)
        self.assertNotIn('hierarchy -check -top "top"', text)
        self.assertLess(text.index("dfflibmap"), text.index("abc -liberty"))
        self.assertIn("select -assert-none t:$*", text)
        self.assertIn("write_verilog -noattr -noexpr", text)

    def test_yosys_script_applies_frontend_options(self):
        text = render_script(
            Path("a.v"),
            "top",
            Path("cells.lib"),
            Path("netlist.v"),
            "+strash; map",
            ("-noalumacc", "-noshare"),
        )
        self.assertIn("synth -top top -flatten -noabc -noalumacc -noshare", text)

    def test_official_image_yosys_fallback_path(self):
        with patch("yosys_flow.shutil.which", side_effect=[None, "/root/.local/bin/yosys"]):
            self.assertEqual(_resolve_yosys(), "/root/.local/bin/yosys")

    def test_failed_adaptive_point_retries_balanced_profile(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            rtl = root / "design.v"
            liberty = root / "cells.lib"
            rtl.write_text("module top(input a, output y); assign y=a; endmodule\n", encoding="utf-8")
            liberty.write_text("library(test) {}\n", encoding="utf-8")
            output = root / "out" / "netlist.v"
            output.parent.mkdir()
            calls = 0

            def fake_run(command, **kwargs):
                nonlocal calls
                calls += 1
                if calls == 1:
                    return subprocess.CompletedProcess(command, 1, "", "first strategy failed")
                pending = output.parent / ".synth_tool" / "netlist.pending.v"
                pending.write_text("module top(input a, output y); assign y=a; endmodule\n", encoding="utf-8")
                return subprocess.CompletedProcess(command, 0, "", "")

            point = PointConfig(name="adaptive-area", profile="area", fallback_on_error=True)
            features = RtlFeatures(100, 0, 10, 0, 0, 0)
            with patch("yosys_flow._resolve_yosys", return_value="/fake/yosys"), patch(
                "yosys_flow.subprocess.run", side_effect=fake_run
            ):
                metadata = run_yosys(
                    rtl=rtl,
                    top="top",
                    liberty=liberty,
                    sdc=rtl,
                    final_output=output,
                    point=point,
                    features=features,
                    delay_ps=10000,
                )

            self.assertEqual(calls, 2)
            self.assertEqual(metadata["resolved_profile"], "balanced")
            self.assertTrue(output.is_file())

    def test_invalid_post_map_rewrite_is_reverted(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            rtl = root / "design.v"
            liberty = root / "cells.lib"
            original = "module top(input a, output y); assign y=a; endmodule\n"
            rtl.write_text(original, encoding="utf-8")
            liberty.write_text("library(test) {}\n", encoding="utf-8")
            output = root / "out" / "netlist.v"
            output.parent.mkdir()

            def fake_run(command, **kwargs):
                pending = output.parent / ".synth_tool" / "netlist.pending.v"
                pending.write_text(original, encoding="utf-8")
                return subprocess.CompletedProcess(command, 0, "", "")

            def corrupt_netlist(path, *args, **kwargs):
                path.write_text("not valid Verilog\n", encoding="utf-8")
                return 1

            point = PointConfig(
                name="buffered", profile="balanced", buffer_fanout_threshold=2, buffer_strength=8
            )
            features = RtlFeatures(1, 0, 0, 0, 0, 0)
            with patch("yosys_flow._resolve_yosys", return_value="/fake/yosys"), patch(
                "yosys_flow.subprocess.run", side_effect=fake_run
            ), patch("yosys_flow.insert_high_fanout_buffers", side_effect=corrupt_netlist), patch(
                "yosys_flow._validate_mapped_netlist", return_value=(False, "/tmp/validate.log")
            ):
                metadata = run_yosys(
                    rtl=rtl,
                    top="top",
                    liberty=liberty,
                    sdc=rtl,
                    final_output=output,
                    point=point,
                    features=features,
                    delay_ps=10000,
                )

            self.assertEqual(output.read_text(encoding="utf-8"), original)
            self.assertEqual(metadata["inserted_buffers"], 0)
            self.assertEqual(metadata["post_map_validation"], "reverted")

    def test_verifier_parses_escaped_scalar_ports(self):
        rtl = self.temp_file(
            "module top(\\A[0] , clk, Y); input \\A[0] , clk; output Y; assign Y = \\A[0] ; endmodule\n",
            "escaped.v",
        )
        ports, inputs, outputs = parse_top_interface(rtl, "top")
        self.assertEqual(ports, ["\\A[0]", "clk", "Y"])
        self.assertEqual(inputs, {"\\A[0]", "clk"})
        self.assertEqual(outputs, {"Y"})

    def test_verifier_parses_ansi_ports_without_comment_words(self):
        rtl = self.temp_file(
            "module top(input wire clk, input wire [3:0] data, output wire y); // input output comment\nassign y = data[0]; endmodule\n",
            "ansi.v",
        )
        ports, inputs, outputs = parse_top_interface(rtl, "top")
        self.assertEqual(ports, ["clk", "data", "y"])
        self.assertEqual(inputs, {"clk", "data"})
        self.assertEqual(outputs, {"y"})

    def test_verifier_parses_grouped_ansi_vector_ports(self):
        rtl = self.temp_file(
            "module top(input [7:0] a, b, output [7:0] y, z); assign y = a; assign z = b; endmodule\n",
            "grouped.v",
        )
        ports, inputs, outputs = parse_top_interface(rtl, "top")
        self.assertEqual(ports, ["a", "b", "y", "z"])
        self.assertEqual(inputs, {"a", "b"})
        self.assertEqual(outputs, {"y", "z"})

    def test_verifier_testbench_connects_by_port_order(self):
        text = render_testbench(
            ports=["a", "clk", "y"],
            inputs={"a", "clk"},
            outputs={"y"},
            clock="clk",
            reset=None,
            reset_active=None,
            samples=3,
        )
        self.assertIn("golden dut_gold(sig_0, sig_1, gold_2);", text)
        self.assertIn("gate dut_gate(sig_0, sig_1, gate_2);", text)
        self.assertIn("sig_1 = 1'b0", text)
        self.assertIn("RANDOM_EQUIV_PASS", text)

    def test_verifier_idealizes_sequential_cells_only(self):
        library = self.temp_file(
            "module AND2_X1(A, B, Z); input A, B; output Z; and(Z, A, B); endmodule\n"
            "module DFF_X1(D, CK, Q, QN); endmodule\n",
            "cells.v",
        )
        netlist = self.temp_file(
            "module top(input a, input ck, output y); wire q; DFF_X1 ff(.D(a), .CK(ck), .Q(q), .QN()); AND2_X1 g(.A(q), .B(a), .Z(y)); endmodule\n",
            "netlist.v",
        )
        text = _ideal_cell_library(library, netlist)
        self.assertIn("always @(posedge CK)", text)
        self.assertIn("module AND2_X1", text)


if __name__ == "__main__":
    unittest.main()
