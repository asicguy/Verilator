#include <systemc.h>
SC_MODULE(tb)
{
  sc_in<bool>           clk;
  sc_out<unsigned int > a_in;
  sc_out<unsigned int > b_in;
  sc_out<unsigned int > c_in;
  sc_out<unsigned int > d_in;
  sc_in<unsigned int >  a_out;
  sc_in<unsigned int >  b_out;
  sc_in<unsigned int >  c_out;
  sc_in<unsigned int >  d_out;

  void source();
  void sink();

  SC_CTOR(tb) {
    SC_CTHREAD(source, clk.pos() );
    SC_CTHREAD(sink,   clk.pos() );
  }
};

