`timescale 1ns / 1ps 



module lab3_2(
			input[4:0] smartCode, // 5-bit
			input CLK, 
			input lab, //0:Digital, 1:Mera
			input [1:0] mode, //00:exit, 01:enter, 1x: idle 
			output reg [5:0] numOfStuInMera,
			output reg [5:0] numOfStuInDigital,
			output reg restrictionWarnMera,//1:show warning, 0:do not show warning
			output reg isFullMera, //1:full, 0:not full
			output reg isEmptyMera, //1: empty, 0:not empty
			output reg unlockMera,	//1:door is open, 0:closed
			output reg restrictionWarnDigital,//1:show warning, 0:do not show warning
			output reg isFullDigital, //1:full, 0:not full
			output reg isEmptyDigital, //1: empty, 0:not empty
			output reg unlockDigital //1:door is open, 0:closed
			
	);
	
	
	// You may declare your variables below
	integer count_ones;
	integer j;
	
	initial begin
			
			numOfStuInMera=0;
			numOfStuInDigital=0;
			restrictionWarnMera=0; // -
			isFullMera=0;
			isEmptyMera=1'b1; // warning 
			unlockMera=0;		
			restrictionWarnDigital=0; // -
			isFullDigital=0;
			isEmptyDigital=1'b1; // warning 
			unlockDigital=0;
			
			
			
	end
	always@(posedge CLK)
	begin
		unlockDigital = 0;
		unlockMera = 0;
		restrictionWarnDigital = 0;
		restrictionWarnMera = 0;
		
		if(mode == 01)
		begin
			if (lab == 0) // digital lab 
			begin
				if (numOfStuInDigital==30) 
				begin
				    isFullDigital = 1;
				end
				else if ( 15<=numOfStuInDigital && numOfStuInDigital<30 )
				begin
				    	count_ones = 0;  // initialize count_ones variable at 0.
		            	    	for(j=0;j<5;j=j+1)   //for loop for count 1's
                        	    	count_ones = count_ones + smartCode[j]; 

					if (count_ones%2==0) // if smart code  has even # of 1's PERMISSION DENIED
					begin 
						restrictionWarnDigital = 1;
					end
					else  //if smart code has odd # of 1's  ACCESS GRANTED
					begin	
						unlockDigital = 1;
						numOfStuInDigital = numOfStuInDigital + 1;
						if (numOfStuInDigital==30)
						begin
						    isFullDigital = 1;
						end
						
					end
				end
				else 
				begin
					unlockDigital = 1;
					numOfStuInDigital = numOfStuInDigital + 1;
					if (numOfStuInDigital==1)
					begin
					    isEmptyDigital = 0;
					end
				
				end
			
			end
			else if (lab == 1)  // Mera Lab
			begin
				if (numOfStuInMera==30) 
				begin
				    isFullMera = 1;
				end
				else if (15<=numOfStuInMera && numOfStuInMera<30)
				begin
				    
				    count_ones = 0;  //initialize count variable at 0.
				    
		            		for(j=0;j<5;j=j+1)   //for loop for count 1's
                    			count_ones = count_ones + smartCode[j]; 
                    
					if (count_ones%2==1) // if smart code has odd # of 1's PERMISSION DENIED
					begin 
						restrictionWarnMera = 1;
					end
					else  // if smart code has even # of 1's  ACCESS GRANTED
					begin
						unlockMera = 1;
						numOfStuInMera = numOfStuInMera + 1;
						
						if (numOfStuInMera==30)
						begin
						    isFullMera = 1;
						end
					end
				end
				else 
				begin
					unlockMera = 1;
					numOfStuInMera = numOfStuInMera + 1;
					
					if (numOfStuInMera==1)
					begin
					    isEmptyMera = 0;
					end
				
				end
			
			end
		//
		end
		else if (mode == 00)
		begin
			if (lab==0 && numOfStuInDigital!=0) 
			begin 
				unlockDigital = 1;
				isFullDigital = 0;
				numOfStuInDigital = numOfStuInDigital -1; // EXIT from Digital lab
				if (numOfStuInDigital==0)
				begin
				    isEmptyDigital = 1;
				end
			end
			else if (lab==1 && numOfStuInMera!=0) 
			begin 
				unlockMera = 1;
				isFullMera = 0;
				numOfStuInMera = numOfStuInMera -1; // EXIT from Mera lab
				
				if (numOfStuInMera==0)
				begin
				    isEmptyMera = 1;
				end
			end
		end
		else
		begin
		    unlockDigital = 0;
		    unlockMera = 0;                 // for idle operations
		    restrictionWarnDigital = 0;
		    restrictionWarnMera = 0;
		end
	
	end
	
	

endmodule
