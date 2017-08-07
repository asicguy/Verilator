module compare
  (
   input        clk,

   input [7:0]  a_in,
   input [7:0]  b_in,
   input [7:0]  c_in,
   input [7:0]  d_in,

   output [7:0] a_out,
   output [7:0] b_out,
   output [7:0] c_out,
   output [7:0] d_out
   );

  logic [7:0] 	a_reg;
  logic [7:0] 	b_reg;
  logic [7:0] 	c_reg;
  logic [7:0] 	d_reg;
  logic 	a_lt_b;
  logic 	a_lt_c;
  logic 	a_lt_d;
  logic 	b_lt_c;
  logic 	b_lt_d;
  logic 	c_lt_d;

  always_ff @(posedge clk) begin
    a_reg <= a_in;
    b_reg <= b_in;
    c_reg <= c_in;
    d_reg <= d_in;
  end
  
  assign a_lt_b = a_reg < b_reg;
  assign a_lt_c = a_reg < c_reg;
  assign a_lt_d = a_reg < d_reg;
  assign b_lt_c = b_reg < c_reg;
  assign b_lt_d = b_reg < d_reg;
  assign c_lt_d = c_reg < d_reg;
   
  always_ff @(posedge clk) begin /* verilator lint_off CASEINCOMPLETE */
    unique case ({a_lt_b, a_lt_c, a_lt_d, b_lt_c, b_lt_d, c_lt_d})
      // A first
      6'b111111: begin
	a_out <= a_reg;
	b_out <= b_reg;
	c_out <= c_reg;
	d_out <= d_reg;
      end
      6'b111110: begin
	a_out <= a_reg;
	b_out <= b_reg;
	c_out <= d_reg;
	d_out <= c_reg;
      end
      6'b111011: begin
	a_out <= a_reg;
	b_out <= c_reg;
	c_out <= b_reg;
	d_out <= d_reg;
      end
      6'b111001: begin
	a_out <= a_reg;
	b_out <= c_reg;
	c_out <= d_reg;
	d_out <= b_reg;
      end
      6'b111100: begin
	a_out <= a_reg;
	b_out <= d_reg;
	c_out <= b_reg;
	d_out <= c_reg;
      end
      6'b111000: begin
	a_out <= a_reg;
	b_out <= d_reg;
	c_out <= c_reg;
	d_out <= b_reg;
      end
      // B first
      6'b011111: begin
	a_out <= b_reg;
	b_out <= a_reg;
	c_out <= c_reg;
	d_out <= d_reg;
      end
      6'b011110: begin
	a_out <= b_reg;
	b_out <= a_reg;
	c_out <= d_reg;
	d_out <= c_reg;
      end
      6'b001111: begin
	a_out <= b_reg;
	b_out <= c_reg;
	c_out <= a_reg;
	d_out <= d_reg;
      end
      6'b000111: begin
	a_out <= b_reg;
	b_out <= c_reg;
	c_out <= d_reg;
	d_out <= a_reg;
      end
      6'b010110: begin
	a_out <= b_reg;
	b_out <= d_reg;
	c_out <= a_reg;
	d_out <= c_reg;
      end
      6'b000110: begin
	a_out <= b_reg;
	b_out <= d_reg;
	c_out <= c_reg;
	d_out <= a_reg;
      end
      // C first
      6'b101011: begin
	a_out <= c_reg;
	b_out <= a_reg;
	c_out <= b_reg;
	d_out <= d_reg;
      end
      6'b101001: begin
	a_out <= c_reg;
	b_out <= a_reg;
	c_out <= d_reg;
	d_out <= b_reg;
      end
      6'b001011: begin
	a_out <= c_reg;
	b_out <= b_reg;
	c_out <= a_reg;
	d_out <= d_reg;
      end
      6'b000011: begin
	a_out <= c_reg;
	b_out <= b_reg;
	c_out <= d_reg;
	d_out <= a_reg;
      end
      6'b100001: begin
	a_out <= c_reg;
	b_out <= d_reg;
	c_out <= a_reg;
	d_out <= b_reg;
      end
      6'b000001: begin
	a_out <= c_reg;
	b_out <= d_reg;
	c_out <= b_reg;
	d_out <= a_reg;
      end
      // D first
      6'b110100: begin
	a_out <= d_reg;
	b_out <= a_reg;
	c_out <= b_reg;
	d_out <= c_reg;
      end
      6'b110000: begin
	a_out <= d_reg;
	b_out <= a_reg;
	c_out <= c_reg;
	d_out <= b_reg;
      end
      6'b010100: begin
	a_out <= d_reg;
	b_out <= b_reg;
	c_out <= a_reg;
	d_out <= c_reg;
      end
      6'b000100: begin
	a_out <= d_reg;
	b_out <= b_reg;
	c_out <= c_reg;
	d_out <= a_reg;
      end
      6'b100000: begin
	a_out <= d_reg;
	b_out <= c_reg;
	c_out <= a_reg;
	d_out <= b_reg;
      end
      6'b000000: begin
	a_out <= d_reg;
	b_out <= c_reg;
	c_out <= b_reg;
	d_out <= a_reg;
      end
    endcase // unique case ({a_lt_b, a_lt_c, a_lt_d, b_lt_c, b_lt_d, c_lt_d})
  end
endmodule
 
