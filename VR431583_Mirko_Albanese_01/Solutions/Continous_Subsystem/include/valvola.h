#ifndef VALVOLA_HH
#define VALVOLA_HH

#include <systemc.h>
#include <systemc-ams.h>
#include <comandi.h>

SCA_TDF_MODULE(valvola)
{
	public:
	//INPUT
		sca_tdf::sca_in<int> in_flag;
		sca_tdf::sca_in<double> in_soglia;
		
	//OUTPUT
		sca_tdf::sca_out<double> a;
		
		SCA_CTOR(valvola) :	in_flag("in_flag"),
							in_soglia("in_soglia"),
							a("a")
	{
	}
	
	//Esecuzione del modulo
	void processing();
	
	void set_attributes();
	
	private:
		double apertura;
	
};

#endif
