module compare
  #
  (
   parameter           DWIDTH = 8
   )
  (
   input 	       clk,
   
   input [DWIDTH-1:0]  a_in,
   input [DWIDTH-1:0]  b_in,
   input [DWIDTH-1:0]  c_in,
   input [DWIDTH-1:0]  d_in,

   output [DWIDTH-1:0] a_out,
   output [DWIDTH-1:0] b_out,
   output [DWIDTH-1:0] c_out,
   output [DWIDTH-1:0] d_out
   );

  logic [DWIDTH-1:0]      a_reg;
  logic [DWIDTH-1:0]      b_reg;
  logic [DWIDTH-1:0]      c_reg;
  logic [DWIDTH-1:0]      d_reg;
  logic [DWIDTH-1:0] 	  a_odd;
  logic [DWIDTH-1:0] 	  b_odd;
  logic [DWIDTH-1:0] 	  c_odd;
  logic [DWIDTH-1:0] 	  d_odd;
  logic [DWIDTH-1:0] 	  a_even;
  logic [DWIDTH-1:0]      b_even;
  logic [DWIDTH-1:0]      c_even;
  logic [DWIDTH-1:0]      d_even;
  logic [DWIDTH-1:0] 	  a_odd1;
  logic [DWIDTH-1:0] 	  b_odd1;
  logic [DWIDTH-1:0] 	  c_odd1;
  logic [DWIDTH-1:0] 	  d_odd1;
  
  always_ff @(posedge clk) begin
    a_reg <= a_in;
    b_reg <= b_in;
    c_reg <= c_in;
    d_reg <= d_in;
    // First stage, compare odds
    a_odd <= (a_reg < b_reg) ? a_reg : b_reg;
    b_odd <= (a_reg < b_reg) ? b_reg : a_reg;
    c_odd <= (c_reg < d_reg) ? c_reg : d_reg;
    d_odd <= (c_reg < d_reg) ? d_reg : c_reg;
    // Sort evens
    a_even <= a_odd;
    b_even <= (b_odd < c_odd) ? b_odd : c_odd;
    c_even <= (b_odd < c_odd) ? c_odd : b_odd;
    d_even <= d_odd;
    // Sort odds again - we are now guaranteed to be sorted
    a_odd1 <= (a_even < b_even) ? a_even : b_even;
    b_odd1 <= (a_even < b_even) ? b_even : a_even;
    c_odd1 <= (c_even < d_even) ? c_even : d_even;
    d_odd1 <= (c_even < d_even) ? d_even : c_even;

    a_out <= a_odd1;
    b_out <= (b_odd1 < c_odd1) ? b_odd1 : c_odd1;
    c_out <= (b_odd1 < c_odd1) ? c_odd1 : b_odd1;
    d_out <= d_odd1;
  end
  
endmodule
 
