#pragma once

#include <systemc-ams.h>

//Modulo di interfacciamento XTEA (RTL) e valvola (AMS)

SCA_TDF_MODULE(transactor_RTL_AMS)
{
	public:
		//INPUT RTL
		sca_tdf::sca_de::sca_in<bool>	dout;		
		sca_tdf::sca_de::sca_in<double>	soglia_rtl;	
		sca_tdf::sca_de::sca_in<sc_uint<32> > res1_rtl;
 		sca_tdf::sca_de::sca_in<sc_uint<32> > res2_rtl;
			
		sca_tdf::sca_out<double>	soglia_ams;
		sca_tdf::sca_out<sc_uint<32>>	comando_ams;
		
		//Costruttore
		transactor_RTL_AMS(sc_core::sc_module_name);
		
		//Parametri iniziali
		void set_attributes();
		//implementazione
		void processing();

};
