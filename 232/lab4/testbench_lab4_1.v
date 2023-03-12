`timescale 1ns / 1ps
module testbench_lab4_1(
    );
	
	//ROM variables 
	reg [3:0] romAddr; 
	wire[4:0] romOutput;
	reg [5:0] expectedROM [15:0];
	//polMEM variables
	reg mode;
	reg [3:0] memAddr;
	reg op;
	reg [1:0] arg; 
	reg CLK;
	wire [8:0] memOutput;
	reg [8:0] expectedPolMemOutput;
	reg [8:0] expectedPolMemOutput_op_0_arg_0 [15:0];
	reg [8:0] expectedPolMemOutput_op_0_arg_1 [15:0];
	reg [8:0] expectedPolMemOutput_op_0_arg_2 [15:0];
	reg [8:0] expectedPolMemOutput_op_0_arg_3 [15:0];
	reg [8:0] expectedPolMemOutput_op_1_arg_0 [15:0];
	reg [8:0] expectedPolMemOutput_op_1_arg_1 [15:0];
	reg [8:0] expectedPolMemOutput_op_1_arg_2 [15:0];
	reg [8:0] expectedPolMemOutput_op_1_arg_3 [15:0];
	//local variables
	integer i,memAddrTmp,argTmp,opTmp;
	reg [8:0] tmpOutput;
	real result;
	reg tmp;
	//Set initial values
	initial CLK = 1;	
	always #5 CLK = ~CLK;		
	
	
	//instance
	lab4ROM ROM(romAddr,romOutput);
	polMEM INS(mode, memAddr, op, arg, CLK, memOutput);
	
	initial begin
	
	
		result=0;
		$display("Starting Testbench");
		
		expectedROM[0]=5'b00000;
		expectedROM[1]=5'b00001;
		expectedROM[2]=5'b00110;
		expectedROM[3]=5'b00111;
		expectedROM[4]=5'b01011;
		expectedROM[5]=5'b01100;
		expectedROM[6]=5'b01101;
		expectedROM[7]=5'b01110;
		expectedROM[8]=5'b11101;
		expectedROM[9]=5'b11110;
		expectedROM[10]=5'b11111;
		expectedROM[11]=5'b10000;
		expectedROM[12]=5'b10111;
		expectedROM[13]=5'b11000;
		expectedROM[14]=5'b11001;
		expectedROM[15]=5'b11010;
		
		//op=0 (polynomial), arg=0 (+1)  
		expectedPolMemOutput_op_0_arg_0 [0] = 9'b000000101;
		expectedPolMemOutput_op_0_arg_0 [1] = 9'b000000011;
		expectedPolMemOutput_op_0_arg_0 [2] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_0 [3] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_0 [4] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_0 [5] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_0 [6] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_0 [7] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_0 [8] = 9'b100000011;
		expectedPolMemOutput_op_0_arg_0 [9] = 9'b100000011;
		expectedPolMemOutput_op_0_arg_0 [10] = 9'b100000101;
		expectedPolMemOutput_op_0_arg_0 [11] = 9'b000000011;
		expectedPolMemOutput_op_0_arg_0 [12] = 9'b100000011;
		expectedPolMemOutput_op_0_arg_0 [13] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_0 [14] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_0 [15] = 9'b100000001;
		//op=0 (polynomial), arg=1 (+2)
		expectedPolMemOutput_op_0_arg_1 [0] = 9'b000011111;
		expectedPolMemOutput_op_0_arg_1 [1] = 9'b000011101;
		expectedPolMemOutput_op_0_arg_1 [2] = 9'b000010011;
		expectedPolMemOutput_op_0_arg_1 [3] = 9'b000010001;
		expectedPolMemOutput_op_0_arg_1 [4] = 9'b000001001;
		expectedPolMemOutput_op_0_arg_1 [5] = 9'b000000111;
		expectedPolMemOutput_op_0_arg_1 [6] = 9'b000000101;
		expectedPolMemOutput_op_0_arg_1 [7] = 9'b000000011;
		expectedPolMemOutput_op_0_arg_1 [8] = 9'b100011011;
		expectedPolMemOutput_op_0_arg_1 [9] = 9'b100011101;
		expectedPolMemOutput_op_0_arg_1 [10] = 9'b100011111;
		expectedPolMemOutput_op_0_arg_1 [11] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_1 [12] = 9'b100001111;
		expectedPolMemOutput_op_0_arg_1 [13] = 9'b100010001;
		expectedPolMemOutput_op_0_arg_1 [14] = 9'b100010011;
		expectedPolMemOutput_op_0_arg_1 [15] = 9'b100010101;
		//op=0 (polynomial), arg=2 (-1)
		expectedPolMemOutput_op_0_arg_2 [0] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_2 [1] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_2 [2] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_2 [3] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_2 [4] = 9'b000000011;
		expectedPolMemOutput_op_0_arg_2 [5] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_2 [6] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_2 [7] = 9'b000000011;
		expectedPolMemOutput_op_0_arg_2 [8] = 9'b100000011;
		expectedPolMemOutput_op_0_arg_2 [9] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_2 [10] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_2 [11] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_2 [12] = 9'b100000011;
		expectedPolMemOutput_op_0_arg_2 [13] = 9'b000000001;
		expectedPolMemOutput_op_0_arg_2 [14] = 9'b100000001;
		expectedPolMemOutput_op_0_arg_2 [15] = 9'b000000011;
		//op=0 (polynomial), arg=3 (-2)
		expectedPolMemOutput_op_0_arg_3 [0] = 9'b000001011;
		expectedPolMemOutput_op_0_arg_3 [1] = 9'b000001001;
		expectedPolMemOutput_op_0_arg_3 [2] = 9'b000000111;
		expectedPolMemOutput_op_0_arg_3 [3] = 9'b000000101;
		expectedPolMemOutput_op_0_arg_3 [4] = 9'b000011101;
		expectedPolMemOutput_op_0_arg_3 [5] = 9'b000010011;
		expectedPolMemOutput_op_0_arg_3 [6] = 9'b000010001;
		expectedPolMemOutput_op_0_arg_3 [7] = 9'b000010111;
		expectedPolMemOutput_op_0_arg_3 [8] = 9'b100001111;
		expectedPolMemOutput_op_0_arg_3 [9] = 9'b100001001;
		expectedPolMemOutput_op_0_arg_3 [10] = 9'b100001011;
		expectedPolMemOutput_op_0_arg_3 [11] = 9'b100010101;
		expectedPolMemOutput_op_0_arg_3 [12] = 9'b100011011;
		expectedPolMemOutput_op_0_arg_3 [13] = 9'b100000101;
		expectedPolMemOutput_op_0_arg_3 [14] = 9'b100000111;
		expectedPolMemOutput_op_0_arg_3 [15] = 9'b100000001;
		//op=1 (derivative), arg=0 (+1)
		expectedPolMemOutput_op_1_arg_0 [0] = 9'b000001010;
		expectedPolMemOutput_op_1_arg_0 [1] = 9'b000001010;
		expectedPolMemOutput_op_1_arg_0 [2] = 9'b000000100;
		expectedPolMemOutput_op_1_arg_0 [3] = 9'b000000100;
		expectedPolMemOutput_op_1_arg_0 [4] = 9'b000000010;
		expectedPolMemOutput_op_1_arg_0 [5] = 9'b000000000;
		expectedPolMemOutput_op_1_arg_0 [6] = 9'b000000000;
		expectedPolMemOutput_op_1_arg_0 [7] = 9'b100000010;
		expectedPolMemOutput_op_1_arg_0 [8] = 9'b100001000;
		expectedPolMemOutput_op_1_arg_0 [9] = 9'b100001010;
		expectedPolMemOutput_op_1_arg_0 [10] = 9'b100001010;
		expectedPolMemOutput_op_1_arg_0 [11] = 9'b000000010;
		expectedPolMemOutput_op_1_arg_0 [12] = 9'b100000100;
		expectedPolMemOutput_op_1_arg_0 [13] = 9'b100000100;
		expectedPolMemOutput_op_1_arg_0 [14] = 9'b100000100;
		expectedPolMemOutput_op_1_arg_0 [15] = 9'b100000110;
		//op=1 (derivative), arg=1 (+2)
		expectedPolMemOutput_op_1_arg_1 [0] = 9'b000110001;
		expectedPolMemOutput_op_1_arg_1 [1] = 9'b000110001;
		expectedPolMemOutput_op_1_arg_1 [2] = 9'b000100111;
		expectedPolMemOutput_op_1_arg_1 [3] = 9'b000100111;
		expectedPolMemOutput_op_1_arg_1 [4] = 9'b000010111;
		expectedPolMemOutput_op_1_arg_1 [5] = 9'b000010001;
		expectedPolMemOutput_op_1_arg_1 [6] = 9'b000010001;
		expectedPolMemOutput_op_1_arg_1 [7] = 9'b000001111;
		expectedPolMemOutput_op_1_arg_1 [8] = 9'b100101111;
		expectedPolMemOutput_op_1_arg_1 [9] = 9'b100110001;
		expectedPolMemOutput_op_1_arg_1 [10] = 9'b100110001;
		expectedPolMemOutput_op_1_arg_1 [11] = 9'b100001111;
		expectedPolMemOutput_op_1_arg_1 [12] = 9'b100011001;
		expectedPolMemOutput_op_1_arg_1 [13] = 9'b100100111;
		expectedPolMemOutput_op_1_arg_1 [14] = 9'b100100111;
		expectedPolMemOutput_op_1_arg_1 [15] = 9'b100101001;
		//op=1 (derivative), arg=2 (-1)
		expectedPolMemOutput_op_1_arg_2 [0] = 9'b100000010;
		expectedPolMemOutput_op_1_arg_2 [1] = 9'b100000010;
		expectedPolMemOutput_op_1_arg_2 [2] = 9'b000000000;
		expectedPolMemOutput_op_1_arg_2 [3] = 9'b000000000;
		expectedPolMemOutput_op_1_arg_2 [4] = 9'b100001010;
		expectedPolMemOutput_op_1_arg_2 [5] = 9'b100000100;
		expectedPolMemOutput_op_1_arg_2 [6] = 9'b100000100;
		expectedPolMemOutput_op_1_arg_2 [7] = 9'b100000110;
		expectedPolMemOutput_op_1_arg_2 [8] = 9'b000000100;
		expectedPolMemOutput_op_1_arg_2 [9] = 9'b000000010;
		expectedPolMemOutput_op_1_arg_2 [10] = 9'b000000010;
		expectedPolMemOutput_op_1_arg_2 [11] = 9'b000000110;
		expectedPolMemOutput_op_1_arg_2 [12] = 9'b000001000;
		expectedPolMemOutput_op_1_arg_2 [13] = 9'b000000000;
		expectedPolMemOutput_op_1_arg_2 [14] = 9'b000000000;
		expectedPolMemOutput_op_1_arg_2 [15] = 9'b100000010;
		//op=1 (derivative), arg=3 (-2)
		expectedPolMemOutput_op_1_arg_3 [0] = 9'b100010111;
		expectedPolMemOutput_op_1_arg_3 [1] = 9'b100010111;
		expectedPolMemOutput_op_1_arg_3 [2] = 9'b100010001;
		expectedPolMemOutput_op_1_arg_3 [3] = 9'b100010001;
		expectedPolMemOutput_op_1_arg_3 [4] = 9'b100110001;
		expectedPolMemOutput_op_1_arg_3 [5] = 9'b100100111;
		expectedPolMemOutput_op_1_arg_3 [6] = 9'b100100111;
		expectedPolMemOutput_op_1_arg_3 [7] = 9'b100101001;
		expectedPolMemOutput_op_1_arg_3 [8] = 9'b000011001;
		expectedPolMemOutput_op_1_arg_3 [9] = 9'b000010111;
		expectedPolMemOutput_op_1_arg_3 [10] = 9'b000010111;
		expectedPolMemOutput_op_1_arg_3 [11] = 9'b000101001;
		expectedPolMemOutput_op_1_arg_3 [12] = 9'b000101111;
		expectedPolMemOutput_op_1_arg_3 [13] = 9'b000010001;
		expectedPolMemOutput_op_1_arg_3 [14] = 9'b000010001;
		expectedPolMemOutput_op_1_arg_3 [15] = 9'b000001111;		
		
		mode=1'b0; //set the memory mode to read. 
		
		$display("Running lab4ROM tests..");
		for (i=0;i<=15;i=i+1)
		begin
			#1; 
			romAddr=i;
			#1;
			if (romOutput==expectedROM[i]) 
			begin
				result = result + 1;
				$display("PASSED: ROM Address %.2d <time:%3d>",i,$time);
			end
			else $display("FAILED!: ROM Address %.2d <time:%3d>",i,$time);		
		end
		
		$display("Running polMEM tests..");
		
		//initial values of ram cells should be 0.
		tmp=0;
		for (memAddrTmp=0;memAddrTmp<=15;memAddrTmp=memAddrTmp+1)
		begin
			memAddr = memAddrTmp;
			#0.5;
			if(memOutput == 0) begin end
			else tmp=1;
		end
		
		if(tmp==0) 
		begin
			result=result+10;
			$display("PASSED: The initial values of the memory cells are 0. <time:%3d>", $time);
		end
		else $display("FAILED: The initial values of the memory cells should be 0. <time:%3d>", $time);
		
		//ramOutput should retain the last read value when the module is in write mode.
		mode=1'b1;//write 
		op=1'b1;
		arg=2'b01;
		memAddr=7;
		#10;
		mode=0; //read
		#1;
		tmpOutput=memOutput;
		#1;
		mode=1'b1;//write 
		op=1'b0;
		arg=2'b11;
		memAddr=7;
		#10;
		if(tmpOutput==memOutput) 
		begin
			result=result+10;
			$display("PASSED: ramOutput retains the last read value when the module is in write mode. <time:%3d>", $time);
		end
		else $display("FAILED: ramOutput should retain the last read value when the module is in write mode. <time:%3d>", $time);
		
		
		//check all polynomials, derivatives
		for(opTmp=0;opTmp<=1;opTmp=opTmp+1)
		begin
			op=opTmp;
			for (argTmp=0;argTmp<=3;argTmp=argTmp+1)
			begin
				$display("op=%.2d, arg=%.2d",opTmp,argTmp);
				arg=argTmp;
				for (memAddrTmp=0; memAddrTmp<=15; memAddrTmp=memAddrTmp+1)
				begin
					//$display("op=%.2b, arg=%.2b, addr:%.2d",opTmp,argTmp,memAddrTmp);
					memAddr=memAddrTmp;
					#1;
					mode=1; //write
					#10;
					mode=0; //read
					#1;
					case({opTmp[0],argTmp[1:0]})
						3'b000: expectedPolMemOutput = expectedPolMemOutput_op_0_arg_0[memAddrTmp];
						3'b001: expectedPolMemOutput = expectedPolMemOutput_op_0_arg_1[memAddrTmp];
						3'b010: expectedPolMemOutput = expectedPolMemOutput_op_0_arg_2[memAddrTmp];
						3'b011: expectedPolMemOutput = expectedPolMemOutput_op_0_arg_3[memAddrTmp];
						3'b100: expectedPolMemOutput = expectedPolMemOutput_op_1_arg_0[memAddrTmp];
						3'b101: expectedPolMemOutput = expectedPolMemOutput_op_1_arg_1[memAddrTmp];
						3'b110: expectedPolMemOutput = expectedPolMemOutput_op_1_arg_2[memAddrTmp];
						3'b111: expectedPolMemOutput = expectedPolMemOutput_op_1_arg_3[memAddrTmp];
					endcase
					if (memOutput === expectedPolMemOutput) 
					begin
						$display("PASSED, memAddr:%.2d, memOutput:%b  <time:%3d>", memAddr,memOutput,$time);
						result=result+1;
					end else $display("FAILED, memAddr:%.2d, memOutput:%b, expected output:%b  <time:%3d>", memAddr,memOutput,expectedPolMemOutput,$time);
					#8;
				end
			end
		end
		
		
		$display("Result %.2f",result/164*100); //max 100 pts.	
		$display("Testbench was finished");	
		$finish;
	end
endmodule
