#ifndef SERBATOIO_HH
#define SERBATOIO_HH

#include <systemc.h>
#include <systemc-ams.h>

SC_MODULE(serbatoio)
{
	public:
	//INPUT
		sca_lsf::sca_tdf::sca_source tdf_lsf;	//Conversione TDF-LSF
		sca_tdf::sca_in<double> in_port;		//Porta di Input TDF
		
	//OUTPUT
		sca_lsf::sca_tdf::sca_sink lsf_tdf;	//Conversione LSF-TDF
		sca_tdf::sca_out<double> out_port; 	//Porta di output TDF
		
	//Dichiarazione Locale
		//Sommatore
		sca_lsf::sca_add add;
		//Integratore
		sca_lsf::sca_integ integratore;
		//Guadagno in ingresso
		sca_lsf::sca_gain gain1;
		//guadagno in retroazione
		sca_lsf::sca_gain gain2;
	
			
		serbatoio(sc_core::sc_module_name);
		~serbatoio();
		
	private:
		//Collegamento tra i componenti
		sca_lsf::sca_signal in_g1, g1_add, add_int, int_out, add_g2;
};

#endif

