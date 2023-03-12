`timescale 1ns / 1ps
module lab4ROM (input [3:0] romAddr, output reg[4:0] romOutput);
always @*
begin
// SATILMIŞ ÖRENCİK
	case(romAddr)
		
	0: romOutput = 5'b00000;
	1: romOutput = 5'b00001;
	2: romOutput = 5'b00110;
	3: romOutput = 5'b00111;
		
	4: romOutput = 5'b01011;
	5: romOutput = 5'b01100;
	6: romOutput = 5'b01101;
	7: romOutput = 5'b01110;
		
	8: romOutput = 5'b11101;
	9: romOutput = 5'b11110;
	10: romOutput = 5'b11111;
	11: romOutput = 5'b10000;
		
	12: romOutput = 5'b10111;
	13: romOutput = 5'b11000;
	14: romOutput = 5'b11001;
	15: romOutput = 5'b11010;
		
	endcase
end
endmodule
																							
module lab4RAM (
	input ramMode,
	input [3:0] ramAddr, 
	input [4:0] ramInput,
	input  ramOp,
	input [1:0] ramArg,  
	input CLK, 
	output reg [8:0] ramOutput);
	
	reg [8:0]memory[0:15];
	
	reg index_0;
	reg index_1;
	reg index_2;
	reg index_3;
	reg index_4;
	
	reg [1:0] value;
	reg [8:0] positive;
	reg [8:0] negative;
	reg [8:0] subtraction;
	
	initial begin
		memory[0] = 0;
		memory[1] = 0;
		memory[2] = 0;
		memory[3] = 0;
		memory[4] = 0;
		memory[5] = 0;
		memory[6] = 0;
		memory[7] = 0;
		memory[8] = 0;
		memory[9] = 0;
		memory[10] = 0;
		memory[11] = 0;
		memory[12] = 0;
		memory[13] = 0;
		memory[14] = 0;
		memory[15] = 0;
		
		ramOutput = 0;
		
		positive = 0;
		value = 0;
		negative = 0;
		subtraction = 9'b100000000;
	end
	
	always @*
	if(ramMode == 1'b0)
	begin
		ramOutput<=memory[ramAddr];
	end
	
	always @(posedge CLK)
	if(ramMode==1'b1)
	begin
	
		casex (ramInput)
			5'b0xxxx : index_0 = 0;
			5'b1xxxx : index_0 = 1;
		endcase
		casex (ramInput)
			5'bx0xxx : index_1 = 0;
			5'bx1xxx : index_1 = 1;
		endcase
		casex (ramInput)
			5'bxx0xx : index_2 = 0;
			5'bxx1xx : index_2 = 1;
		endcase
		casex (ramInput)	
			5'bxxx0x : index_3 = 0;
			5'bxxx1x : index_3 = 1;
		endcase
		casex (ramInput)	
			5'bxxxx0 : index_4 = 0;
			5'bxxxx1 : index_4 = 1;
		endcase
	
		if (ramArg==2'b00 || ramArg==2'b10)
		begin
			value = 1;
		end
		
		else
		begin
			value = 2;
		end
		
		
		if ((ramOp == 0)&&(ramArg==2'b10 || ramArg==2'b11)) 
		begin
				if (index_0==0) 
				begin
					positive= positive+(value*value*value*value);
				end
				else  
				begin
					negative= negative+(value*value*value*value);
				end
				if (index_1==0) 
				begin
					negative= negative+(value*value*value);
				end
				else 
				begin
					positive= positive+(value*value*value);
				end
				if (index_2==0) 
				begin
					positive= positive+(value*value);
				end
				else 
				begin
					negative= negative+(value*value);
				end
				
				if (index_3==0) 
				begin
					negative= negative+value;
				end
				else 
				begin
					positive= positive+value;
				end
				
				if (index_4==0) 
				begin
					positive= positive+1;
				end
				else 
				begin
					negative= negative+1;
				end
		
		end
		else if ((ramOp == 0)&&(ramArg==2'b00 || ramArg==2'b01))
		begin
		
				if (index_0==0) 
				begin
					positive= positive+(value*value*value*value);
				end
				else  
				begin
					negative= negative+(value*value*value*value);
				end
				
				if (index_1==0) 
				begin
					positive= positive+(value*value*value);
				end
				else 
				begin
					negative= negative+(value*value*value);
				end
				
				if (index_2==0) 
				begin
					positive= positive+(value*value);
				end
				else 
				begin
					negative= negative+(value*value);
				end
				
				if (index_3==0) 
				begin
					positive= positive+value;
				end
				else 
				begin
					negative= negative+value;
				end
				
				if (index_4==0) 
				begin
					positive= positive+1;
				end
				else 
				begin
					negative= negative+1;
				end
		end
		else if ((ramOp == 1)&&(ramArg==2'b10 || ramArg==2'b11))
		begin
		
				if (index_0==0)
				begin		
					negative= negative+(4*value*value*value); 
				end
				else 
				begin
					positive= positive+(4*value*value*value); 
				end
			
				if (index_1==0) 
				begin	
					positive= positive+(3*value*value); 
				end
				else 
				begin
					negative= negative+(3*value*value);
				end
				
				if (index_2==0)
				begin
					negative= negative+(2*value); 
				end
				else 
				begin
					positive= positive+(2*value);
				end
				
				if (index_3==0)
				begin
					positive= positive+1; 
				end
				else 
				begin
					negative= negative+1; 
				end
		
		end
		else if ((ramOp == 1)&&(ramArg==2'b00 || ramArg==2'b01))
		begin
				if (index_0==0) 
				begin
					positive= positive+(4*value*value*value);
				end
				else  
				begin
					negative= negative+(4*value*value*value);
				end
				
				if (index_1==0) 
				begin	
					positive= positive+(3*value*value);
				end
				else 
				begin
					negative= negative+(3*value*value);
				end
				
				if (index_2==0) 
				begin
					positive= positive+(2*value);
				end
				else 
				begin
					negative= negative+(2*value);
				end
				
				if (index_3==0) 
				begin
					positive= positive+1;
				end
				else 
				begin
					negative= negative+1;
				end
		end
		
		if (positive < negative) 
		begin
			subtraction = subtraction + (negative-positive);
			memory[ramAddr] <= subtraction;
		end
		else 
		begin
			memory[ramAddr]<=(positive-negative);
		end
		
		
		
	end
	

endmodule


module polMEM(input mode, input [3:0] memAddr, input op, input [1:0] arg, input CLK, output wire [8:0] memOutput);

	/*Don't edit this module*/
	wire [4:0]  romOutput;

	lab4ROM RO(memAddr, romOutput);
	lab4RAM RA(mode, memAddr, romOutput, op, arg, CLK, memOutput);



endmodule
