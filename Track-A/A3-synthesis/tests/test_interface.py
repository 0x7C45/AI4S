import json
import os
import subprocess
import tempfile
import textwrap
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class InterfaceTests(unittest.TestCase):
    def test_built_tool_runs_complete_fake_yosys_flow(self):
        with tempfile.TemporaryDirectory() as temporary:
            tmp = Path(temporary)
            rtl = tmp / "design.v"
            rtl.write_text("module top(input a, output y); assign y=a; endmodule\n", encoding="utf-8")
            sdc = tmp / "constraints.sdc"
            sdc.write_text("create_clock -period 10 [get_ports clk]\n", encoding="utf-8")
            liberty = tmp / "cells.lib"
            liberty.write_text("library(test) {}\n", encoding="utf-8")
            config = tmp / "config.json"
            config.write_text(json.dumps({"$default": [{"profile": "balanced"}]}), encoding="utf-8")
            fake = tmp / "fake_yosys.py"
            fake.write_text(
                textwrap.dedent(
                    """\
                    #!/usr/bin/env python3
                    import pathlib, re, sys
                    script = pathlib.Path(sys.argv[sys.argv.index('-s') + 1]).read_text()
                    output = re.findall(r'write_verilog[^\\n]*\\s([^\\s]+)', script)[-1]
                    pathlib.Path(output).write_text('module top(input a, output y); assign y = a; endmodule\\n')
                    """
                ),
                encoding="utf-8",
            )
            fake.chmod(0o755)
            output = tmp / "out" / "netlist.v"
            env = dict(os.environ, YOSYS_BIN=str(fake))
            result = subprocess.run(
                [
                    "make", "-j1", "synth",
                    f"RTL={rtl}",
                    "TOP=top",
                    f"SDC={sdc}",
                    f"LIBERTY={liberty}",
                    f"CONFIG={config}",
                    "CIRCUIT=HIDDEN",
                    "POINT=1",
                    f"OUT_DIR={output.parent}",
                ],
                cwd=ROOT,
                env=env,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                check=False,
            )
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertIn("module top", output.read_text(encoding="utf-8"))
            self.assertTrue((output.parent / ".synth_tool" / "run.ys").is_file())


if __name__ == "__main__":
    unittest.main()
