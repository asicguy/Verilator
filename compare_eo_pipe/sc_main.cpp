// -*- SystemC -*-
// DESCRIPTION: Verilator Example: Top level main for invoking SystemC model
//
// Copyright 2003-2017 by Wilson Snyder. This program is free software; you can
// redistribute it and/or modify it under the terms of either the GNU
// Lesser General Public License Version 3 or the Perl Artistic License
// Version 2.0.
//====================================================================

#include <cstdio>
#include <iostream>
#include <sys/times.h>
#include <sys/stat.h>

#include "systemc.h"		// SystemC global header
#include "verilated_vcd_sc.h"	// Tracing

#include "Vcompare.h"		// Top level header, generated from verilog
#include "tb.h"

Vcompare *top0;
tb       *tb0;

int sc_main(int argc, char* argv[]) {
    Verilated::commandArgs(argc, argv);
    Verilated::randReset(2);
    Verilated::debug(0);	// We compiled with it on for testing, turn it back off

    // General logfile
    ios::sync_with_stdio();

    // Defaults
#if (SYSTEMC_VERSION>20011000)
#else
    sc_time dut(1.0, sc_ns);
    sc_set_default_time_unit(dut);
#endif

    //==========
    // Define the Clocks

    cout << "Defining Clocks\n";
#if (SYSTEMC_VERSION>=20070314)
    sc_clock clk     ("clk",    10,SC_NS, 0.5, 3,SC_NS, true);
#else
    sc_clock clk     ("clk",    10, 0.5, 3, true);
#endif

    cout << "Defining Interconnect\n";
  sc_signal<unsigned int > a_in;
  sc_signal<unsigned int > b_in;
  sc_signal<unsigned int > c_in;
  sc_signal<unsigned int > d_in;
  sc_signal<unsigned int > a_out;
  sc_signal<unsigned int > b_out;
  sc_signal<unsigned int > c_out;
  sc_signal<unsigned int > d_out;
  //  sc_clock clk;

    //==========
    // Part under test

    Vcompare* top0 = new Vcompare("top");
    top0->clk(clk);             // SP_PIN
    top0->a_in(a_in);           // SP_PIN
    top0->b_in(b_in);           // SP_PIN
    top0->c_in(c_in);           // SP_PIN
    top0->d_in(d_in);           // SP_PIN
    top0->a_out(a_out);         // SP_PIN
    top0->b_out(b_out);         // SP_PIN
    top0->c_out(c_out);         // SP_PIN
    top0->d_out(d_out);         // SP_PIN
    tb0 = new tb("tb0");   // SP_CELL (top, Vcompare);
    tb0->clk(clk);             // SP_PIN
    tb0->a_in(a_in);           // SP_PIN
    tb0->b_in(b_in);           // SP_PIN
    tb0->c_in(c_in);           // SP_PIN
    tb0->d_in(d_in);           // SP_PIN
    tb0->a_out(a_out);         // SP_PIN
    tb0->b_out(b_out);         // SP_PIN
    tb0->c_out(c_out);         // SP_PIN
    tb0->d_out(d_out);         // SP_PIN

    //==========
    //  Waves

#if VM_TRACE
    // Before any evaluation, need to know to calculate those signals only used for tracing
    Verilated::traceEverOn(true);
#endif

    // You must do one evaluation before enabling waves, in order to allow
    // SystemC to interconnect everything for testing.
    cout <<("Test initialization...\n");
#if (SYSTEMC_VERSION>=20070314)
    sc_start(1,SC_NS);
#else
    sc_start(1);
#endif

    //==========
    //  Waves

#if VM_TRACE
    cout << "Enabling waves...\n";
    VerilatedVcdSc* tfp = new VerilatedVcdSc;
    top0->trace (tfp, 99);
    tfp->open ("vlt_dump.vcd");
#endif

    //==========
    // Start of Test

    cout <<("Test beginning...\n");

    while (!Verilated::gotFinish()) {
#if VM_TRACE
	// Flush the wave files each cycle so we can immediately see the output
	// Don't do this in "real" programs, do it in an abort() handler instead
	if (tfp) tfp->flush();
#endif
#if (SYSTEMC_VERSION>=20070314)
	sc_start(1,SC_NS);
#else
	sc_start(1);
#endif
    }

    top0->final();

    //==========
    //  Close Waves
#if VM_TRACE
    if (tfp) tfp->close();
#endif

    //==========
    //  Coverage analysis (since test passed)
    mkdir("logs", 0777);
#if VM_COVERAGE
    VerilatedCov::write("logs/coverage.dat");
#endif // VM_COVERAGE

    //==========
    //  Close LogFiles

    cout << "*-* All Finished *-*\n";  // Magic if using perl's Log::Detect

    return(0);
}
