library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.ALL;

package xtea_helper is
	subtype data_64   			is UNSIGNED (63 downto 0);
	subtype data_word		is UNSIGNED (31 downto 0);	
	subtype command_word 	is STD_LOGIC_VECTOR (1 downto 0);
	--subtype vector			is BIT_VECTOR (31 downto 0);
end package;

use work.xtea_helper.all;

entity xtea is
    Port ( 
        clock          : in BIT;
        reset          : in BIT;
        -- input
        in1            : in data_word;
        in2            : in data_word;
        command        : in BIT;
        input_ready    : in BIT;
        -- output
        res1        : out data_word;
        res2        : out data_word;
        res_ready   : out BIT := '0'
    );
end xtea;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.ALL;

architecture Behavioral_Xtea of xtea is

	-- stati del componente
    	type state is (RST, CONFIG_1, CONFIG_2, S_T, S_T02, S_01, S_02, S_03, S_04, S_05, S_06, FINAL);
    
    	constant DELTA	: data_word := "10011110001101110111100110111001";
	constant ZEROS	: data_word := "00000000000000000000000000000000";
    	constant ONE		: data_word := "00000000000000000000000000000001";
	constant TWO		: data_word := "00000000000000000000000000000010";
	constant THREE	: data_word := "00000000000000000000000000000011";

	--costante 64
	constant ZEROS_64	: data_64 := "0000000000000000000000000000000000000000000000000000000000000000";

    	-- definizione delle iterazioni
    	subtype iteration_range is integer range 0 to 32;
    	constant ITERATION_NUMBER : iteration_range := 31;
    	signal count : iteration_range;
    
    	-- variabili di mantenimento
    	signal current_state    				: state := RST;
    	signal next_state       				: state := RST;
    	signal stored_in1       				: data_word;
    	signal stored_in2       				: data_word;
    	signal temp, temp_in1, temp_in2   	: data_word;
	signal sum						: data_64;
    	signal res_1, res_2           			: data_word;
    	signal key_0 						: data_word;
    	signal key_1 						: data_word;
    	signal key_2 						: data_word;
    	signal key_3 						: data_word;
    
begin
--FSM
fsm: process(input_ready, command, current_state)	--Sensitivity List
begin
 	next_state <= current_state;
	case current_state is
		when RST =>
   			if input_ready = '1' then
	  			next_state<=CONFIG_1;
	   		else 
	   			next_state<=RST;
			end if;
	   	when CONFIG_1 =>
	   		if input_ready = '1' then
	   			next_state<=CONFIG_2;
	   		else 
	   			next_state<=CONFIG_1;
			end if;
	   	when CONFIG_2 =>
	   		if input_ready = '1' then
	   			next_state<=S_T;
	   		else 
	   			next_state<=CONFIG_2;
			end if;
	   	when S_T =>
	   		if (input_ready = '1') then
				if(command = '0') then
					--Ramo Codifica
					next_state <= S_01;
				else
					--Ramo decodifica
					next_state <= S_T02;
				end if;
			else
				next_state <= S_T;
			end if;
		when S_T02 =>
			next_state <= S_02;
		when S_01 =>
			if (command = '0') then --CODIFICA
				next_state <= S_03;
			else
				next_state <= S_06;
			end if;
		when S_02 =>
			if (command = '1') then --DECODIFICA
				next_state <= S_04;
			else
				next_state <= S_05;
			end if;
		when S_03 =>
			next_state <= S_02;
	   	when S_04 =>
	   		next_state <= S_01;
		when S_05 =>
			if (count < ITERATION_NUMBER) then
				next_state <= S_01;
			else
				next_state <= FINAL;
			end if;
		when S_06 =>
			if (count < ITERATION_NUMBER) then
				next_state <= S_02;
			else
				next_state <= FINAL;
			end if;
		when FINAL =>
			next_state <= RST;
		when others =>
			next_state <= current_state;
	end case;
end process;
	
datapath:process(clock, reset)
begin
	if (reset = '1') then
		current_state <= RST;
	elsif (clock'event and clock='1') then 
		current_state<=next_state; 
		case current_state is
			when RST =>
				--res_1<= ZEROS;
				--res_2<= ZEROS;
				res_ready<= '0';
				sum <= ZEROS_64;
				temp <= ZEROS;
				count <=  0;
			when CONFIG_1 =>
					if (key_0 = ZEROS) then
						key_0 <= in1;
						key_1 <= in2;	
					end if;			
			when CONFIG_2 =>
					if (key_2 = ZEROS) then
						key_2 <= in1;
						key_3 <= in2;
					end if;
			when S_T =>
				res_1<=ZEROS;
				res_2<=ZEROS;
				res_ready<='0';
				sum <= ZEROS_64;
				temp <= ZEROS;
				count <= 0;
				temp_in1 <= in1;
				temp_in2 <= in2;
			when S_T02 =>
				sum <= "0000000000000000000000000001001111000110111011110011011100100000";
			when S_01 =>
				case (sum(31 downto 0) and THREE) is
					when ZEROS =>
						temp <= key_0;        			
					when ONE =>
						temp <= key_1;
					when TWO =>
						temp <= key_2; 
					when others =>
						temp <= key_3;
				end case;
			when S_02 =>
				case ((sum(31 downto 0) srl 11) and THREE) is
					when ZEROS =>
						temp <= key_0;
					when ONE =>
						temp <= key_1;
					when TWO =>
						temp <= key_2; 
					when others =>
						temp <= key_3; 
				end case;
			when S_03 =>
				temp_in1 <= temp_in1 + ((((temp_in2 sll 4) xor (temp_in2 srl 5)) + temp_in2) xor (sum(31 downto 0) + temp));
     				sum <= sum + DELTA;
     			when S_04 =>
     				temp_in2 <= temp_in2 - ((((temp_in1 sll 4) xor (temp_in1 srl 5)) + temp_in1) xor (sum(31 downto 0) + temp));
      				sum <= sum - DELTA;
      			when S_05 =>
      				temp_in2 <= temp_in2 + ((((temp_in1 sll 4) xor (temp_in1 srl 5)) + temp_in1) xor (sum(31 downto 0) + temp));
				count <= count + 1;
			when S_06 =>
				temp_in1 <= temp_in1 - ((((temp_in2 sll 4) xor (temp_in2 srl 5)) + temp_in2) xor (sum(31 downto 0)+ temp));
				count <= count + 1;
			when FINAL =>
				res1<=temp_in1; 
  				res2<=temp_in2;
  				res_ready <= '1';
			when others =>
				res1 <= ZEROS;
				res2 <= ZEROS;
				res_1 <= ZEROS;
				res_2 <= ZEROS;
  		end case;
	end if;
  end process;

end Behavioral_Xtea;
