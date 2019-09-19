#ifndef VALVOLA_HH
#define VALVOLA_HH

#include <systemc.h>
#include <systemc-ams.h>
#include <converter.h>

SCA_TDF_MODULE(valvola)
{
	public:
	//INPUT
		sca_tdf::sca_in<sc_uint<32>> in_flag;
		sca_tdf::sca_in<double> in_soglia;
		
	//OUTPUT
		sca_tdf::sca_out<double> a;
		
		SCA_CTOR(valvola) :	in_flag("in_flag"),
							in_soglia("in_soglia"),
							a("a")
	{
	}
	
	payloadStruct	xtea_box;
	
	//Esecuzione del modulo
	void processing();
	
	void set_attributes();
	
	private:
		double apertura;
	
};

#endif
