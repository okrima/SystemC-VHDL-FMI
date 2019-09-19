#pragma once

//Interfaccia Serbatoio (AMS-RTL)

#include<systemc-ams.h>

SCA_TDF_MODULE(transactor_AMS_RTL)
{
	public:
		//INPUT
		sca_tdf::sca_in<double>				x_ams;	//Livello Acqua AMS
		//OUTPUT
		sca_tdf::sca_de::sca_out<double>	x_rtl;	///Livello Acqua RTL
		
		//Costruttore
		transactor_AMS_RTL(sc_core::sc_module_name);
		
		 ~transactor_AMS_RTL();
		
		//Metodi implementazione
		void set_attributes();
		void processing();
		
};

