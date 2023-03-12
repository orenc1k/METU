`timescale 1ns / 1ps

module ab(input A, input B, input clk, output reg Q);

    initial begin 
		Q = 0;
	end	

    // You can implement your code here
    // ...
	always@(posedge clk)
	begin
		case({A,B})
			2'b00:Q<=Q;
			2'b01:Q<=1;
			2'b10:Q<=0;
			2'b11:Q<=!Q;
		endcase
	end
endmodule


	
module ic1337(// Inputs
	input I0,
    input I1,
    input I2,
    input clk,
    // Outputs
    output Q0,
    output Q1,
    output Z);
		
	assign Z=Q0^Q1;
	ab ab0(!I0&I1&!I2,I2,clk,Q0);
	ab ab1(!I2,(((I0)&(I1)&(!I2))|((!I0)&((!I1)|I2))),clk,Q1);	
				
    // You can implement your code here
    // ...

endmodule
