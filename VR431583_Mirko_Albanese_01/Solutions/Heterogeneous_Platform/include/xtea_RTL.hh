
#include <systemc.h>

class xtea_RTL : public sc_core::sc_module
{
	public:
	
	//INPUT
		
		//prima parola
		sc_in<sc_uint<32>>	in_1;
				
		//seconda parola
		sc_in<sc_uint<32>>	in_2;
		
		sc_in<bool>			in_ready;
		
		//modalità
		sc_in<bool>			mode;
		
		//clock
		sc_in<bool>			clock;
		
		//reset
		sc_in<bool>			reset;
		
		
		//prima chiave
		sc_in<sc_uint<32>>	k_0;
		
		//seconda chiave
		sc_in<sc_uint<32>>	k_1;
		
		//terza chiave
		sc_in<sc_uint<32>>	k_2;
		
		//quarta chiave
		sc_in<sc_uint<32>>	k_3;
		
				
	//OUTPUT
		
		//Risultato
		sc_out<sc_uint<32>>	res_1;
		sc_out<sc_uint<32>>	res_2;
		
		sc_out<bool>		res_ready;
	
		SC_HAS_PROCESS(xtea_RTL);
		
		xtea_RTL(sc_core::sc_module_name module_name);
	
	protected:		
		typedef enum {RST, S_T, S_T02, S_01, S_02, S_03, S_04, S_05, S_06, FINAL}	STATI;
						
		sc_signal<STATI>	stato, nuovo_stato;
		sc_uint<32>			sum;
		sc_uint<32>			temp;
		sc_uint<32>			delta;
		
		sc_uint<32>			count;
		sc_uint<32>			temp_in_1;
		sc_uint<32>			temp_in_2;
				
		void datapath();
		void fsm();
		
};

