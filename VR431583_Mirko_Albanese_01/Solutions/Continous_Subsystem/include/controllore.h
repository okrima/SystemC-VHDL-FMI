#ifndef CONTROLLORE_H
#define CONTROLLORE_H

#include <systemc.h>
#include <systemc-ams.h>
#include <comandi.h>

SCA_TDF_MODULE(controllore)
{
	public:
	//INPUT
		sca_tdf::sca_in<double> in_c;	//Livello acqua
		
	//OUTPUT
		sca_tdf::sca_out<double> out_soglia_c;
		sca_tdf::sca_out<int> out_flag;	//Comando
		
		
		
		SCA_CTOR(controllore) :	in_c("in_c"),
								out_soglia_c("out_soglia_c"),
								out_flag("out_flag")
		{
		}
		//Impostazione parametri
		void set_attributes();
		//Esecuzione del modulo
		void processing();
	
	private:
		int i;	//Contatore
		
		double soglia;
		
};

#endif
