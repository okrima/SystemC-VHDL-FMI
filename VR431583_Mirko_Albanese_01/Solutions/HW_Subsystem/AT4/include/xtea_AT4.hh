
#pragma once

#include<systemc.h>
#include<tlm.h>
#include <def_AT4.hh>

class xtea_AT4	: 	public sc_module,
					public virtual tlm::tlm_fw_transport_if<>
{
	public:
		
		//Creo l'interfaccia Target
		tlm::tlm_target_socket <> target_socket;
			
		void IOPROCESS();
		
		//Dichiarazione funzione xtea
		void xteaEncDec();
		
		//Payload
		payloadStruct xtea_box;
		//Transizione
		tlm::tlm_generic_payload* pending_trans;
		//Temp_Var
		sc_int<32>	tmp_res_1;
		sc_int<32>	tmp_res_2;
		
		sc_event event;
		
		SC_HAS_PROCESS(xtea_AT4);
		xtea_AT4(sc_module_name name);
		
		virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t);
		
		
		virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);
		
		virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data); 	
 		virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

};
