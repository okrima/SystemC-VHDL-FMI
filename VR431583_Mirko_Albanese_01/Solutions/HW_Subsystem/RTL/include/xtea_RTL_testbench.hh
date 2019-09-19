
#include<systemc.h>

#define PERIODO 50

class xtea_tb : public sc_core::sc_module
{
	public:
		

		sc_out<sc_uint<32>>	in_1;
		sc_out<sc_uint<32>>	in_2;
		
		sc_out<bool>			in_ready;
		
		//modalità
		sc_out<bool>			mode;
		
		//clock
		sc_out<bool>			clock;
		
		//reset
		sc_out<bool>			reset;
		
		sc_out<sc_uint<32>>	k_0;
		sc_out<sc_uint<32>> k_1;
		sc_out<sc_uint<32>>	k_2;
		sc_out<sc_uint<32>>	k_3;
		
		//Risultato
		sc_in<sc_uint<32>>	res_1;
		sc_in<sc_uint<32>>	res_2;	
		
		sc_in<bool>		res_ready;
		
		SC_HAS_PROCESS(xtea_tb);
		
		xtea_tb(sc_module_name name);
		
		private:
			
			void clk_sg();
			void run_tb();
};


