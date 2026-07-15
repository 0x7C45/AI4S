read_liberty $env(LIBERTY)
read_verilog $env(NETLIST)
link_design $env(TOP)
read_sdc $env(SDC)
report_checks -path_delay max -group_path_count 20 -endpoint_path_count 1 -unique_paths_to_endpoint -format full -fields {capacitance slew input_pin net} -digits 4
exit
