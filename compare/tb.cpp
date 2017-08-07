#include "tb.h"

void tb::source() {
  for (int i = 0; i < 8; i++) {
    cout << i << endl;
    for (int j = 0; j < 8; j++) {
      for (int k = 0; k < 8; k++) {
	for (int l = 0; l < 8; l++) {
	  a_in.write(i);
	  b_in.write(j);
	  c_in.write(k);
	  d_in.write(l);
	  wait();
	}
      }
    }
  }
  wait();
  wait();
  wait();
  wait();
  sc_stop();
}
  
void tb::sink() {
  int a, b, c, d;
  while(1) {
    a = a_out.read();
    b = b_out.read();
    c = c_out.read();
    d = d_out.read();
    wait();
    cout << a << "\t" << b << "\t" << c << "\t" << d << endl;
  }
}
