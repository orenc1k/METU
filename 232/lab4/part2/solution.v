`timescale 1ns / 1ps

module lab4_2(// INPUTS
              input wire      mode,  // 0:load 1:execute
              input wire[2:0] opCode,  // 011,111 not used
              input wire[3:0] value,  // 4-bit value (v)
              input clk,
              input reset,
              // OUTPUTS
              output reg[9:0] result,
              output reg cacheFull,
              output reg invalidOp,
              output reg overflow);

    integer i;
    reg [9:0] tempo_last;
    reg [6:0] index_current;
    reg [6:0] init_inst;
    reg [9:0] first_p; 
    reg [9:0] second_p; 
    reg index1;
	reg index2;
	reg index3;
    reg [6:0] opt_counter;
    reg tempo;
    reg [2:0]memory[0:31];  	
    reg [3:0]mem_val[0:31]; 
    
    //11-51
    initial begin

    cacheFull = 0;
    invalidOp = 0;
	overflow = 0;
	first_p = 0;
	second_p = 0;
    tempo_last = 0;
	result = 0; 
	opt_counter = 0;  
	index_current = 0;
	init_inst = 7'b1111111;
    for(i = 1;i<33;i = i+1)memory[i-1]=3'b111;
    end

    	always @(posedge clk or posedge reset) begin
	
		if (reset==0)begin

        invalidOp = 0;
			casex (opCode)
			3'b0xx : index1 = 0;
			3'b1xx : index1 = 1;
			endcase
			casex (opCode)
			3'bx0x : index2 = 0;
			3'bx1x : index2 = 1;
			endcase
			casex (opCode)
			3'bxx0 : index3 = 0;
			3'bxx1 : index3 = 1;
			endcase

        if (mode==1'b0) begin  
			
			if ((index1==1 && index2==1 && index3==1)||(index1==0 && index2==1 && index3==1))invalidOp = 1;
            		else if (opt_counter==32)cacheFull = 1;
	    		else if (opt_counter<32)
	    		begin
	    			memory[opt_counter] = opCode;
	    			mem_val[opt_counter] = value;
	    			opt_counter = opt_counter+1;
	    		end
    	end
        else begin  
            casex (memory[index_current])
			3'b0xx : index1 = 0;
			3'b1xx : index1 = 1;
			endcase
			casex (memory[index_current])
			3'bx0x : index2 = 0;
			3'bx1x : index2 = 1;
			endcase
			casex (memory[index_current])
			3'bxx0 : index3 = 0;
			3'bxx1 : index3 = 1;
			endcase
            	invalidOp = 0; 
    		overflow = 0;

            if (index1==0 && index2==1 && index3==1) begin    ///
			if (init_inst!=-1)index_current = init_inst;
			else index_current = 0;
		    end
            
            else if (index1==1 && index2==0 && index3==0) begin ///
			tempo_last = 0;
			for(i=1;i<11;i=i+1) begin
        				if(first_p[i-1] == 1'b1)
            			tempo_last = tempo_last + 1;
            			end
            		result = tempo_last;
			second_p = first_p;
    			first_p = result;
		    end

            else if (index1==0 && index2==0 && index3==1) begin ///
			tempo_last = mem_val[index_current] + first_p + second_p;
    			if (tempo_last<(mem_val[index_current]+first_p) || tempo_last<(mem_val[index_current]+second_p) || tempo_last<(first_p+second_p)) 
    			overflow = 1;
    			result = tempo_last;
    			second_p = first_p;
    			first_p = result;
		    end

            else if (index1==1 && index2==1 && index3==1) begin   ///
			if (init_inst!=-1)index_current = init_inst;
			else index_current = 0;
		    end

            else if (index1==1 && index2==0 && index3==1) begin ///
			tempo_last = first_p;
    			for (i=1;i<6;i=i+1)
    			begin
    				tempo = first_p[i-1];
    				first_p[i-1] = first_p[10-i];
    				first_p[10-i] = tempo;
    			end
    			
    			result = first_p;
    			second_p = tempo_last;
		    end
    		
            else if (index1==0 && index2==0 && index3==0) begin /// 
			tempo_last = first_p + mem_val[index_current];
    			if ( tempo_last<first_p || tempo_last<mem_val[index_current] ) 
    			
    			result = tempo_last;
    			overflow = 1;
    			second_p = first_p;
    			first_p = result;
    			
		    end


            else if (index1==1 && index2==1 && index3==0) begin  ///
            		index_current = mem_val[index_current];
			init_inst = mem_val[index_current];
    			index_current = index_current-1;
		    end

            else if (index1==0 && index2==1 && index3==0) begin ///
			tempo_last = mem_val[index_current]+(first_p*second_p);
    			if (tempo_last<first_p*second_p ||tempo_last<mem_val[index_current]) 
    			
    			result = tempo_last;
    			second_p = first_p;
    			overflow = 1;
    			first_p = result;
		    end

            else begin end


            	index_current = index_current+1;
    		if (init_inst==7'b1111111&&index_current == 32) index_current = 0;
    		else if (init_inst!=7'b1111111  && index_current == 32) index_current = init_inst;
    		else if (init_inst==7'b1111111 && memory[index_current]==3'b111) index_current = 0;
            	
    		else if (init_inst!=7'b1111111 &&  memory[index_current]==3'b111) index_current = init_inst;
    		end


    		
		end

        else begin

        	for(i=1;i<33;i=i+1) memory[i-1]=3'b111;
	for(i=1;i<33;i=i+1) mem_val[i-1]=4'b0000;
        	overflow = 0;
    	tempo = 0;
    	second_p = 0;
    	cacheFull = 0;
    	invalidOp = 0;
        	index_current = 0;
    	init_inst = 7'b1111111;
        	tempo_last = 0;
    	opt_counter = 0;
    	result = 0;
        	first_p = 0;
        end
    end
endmodule
