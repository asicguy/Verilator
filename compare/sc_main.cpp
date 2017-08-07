#include "Vcompare.h"
#include "tb.h"

SC_MODULE(SYSTEM) {
  Vcompare* top0;
  tb*       tb0;

  sc_signal<unsigned int > a_in;
  sc_signal<unsigned int > b_in;
  sc_signal<unsigned int > c_in;
  sc_signal<unsigned int > d_in;
  sc_signal<unsigned int > a_out;
  sc_signal<unsigned int > b_out;
  sc_signal<unsigned int > c_out;
  sc_signal<unsigned int > d_out;
  sc_clock clk;
  //  sc_clock clk ("clk",10, 0.5, 3, true);

  SC_CTOR( SYSTEM ) : clk ("clk",10, 0.5, 3, true) {
    top0 = new Vcompare("top0"); // SP_CELL (top, Vcompare);
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
  }

  ~SYSTEM() {
    delete tb0;
    delete top0;
  }
  
};

SYSTEM *top = NULL;

int sc_main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);

  top = new SYSTEM("top");
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("compare");
  // Dump the desired signals
  sc_trace(wf, clock, "clk");
  sc_trace(wf, clock, "a_in");
  sc_trace(wf, clock, "b_in");
  sc_trace(wf, clock, "c_in");
  sc_trace(wf, clock, "d_in");
  sc_trace(wf, clock, "a_out");
  sc_trace(wf, clock, "b_out");
  sc_trace(wf, clock, "c_out");
  sc_trace(wf, clock, "d_out");
  sc_start();
  sc_close_vcd_trace_file(wf);
  return 0;

}


