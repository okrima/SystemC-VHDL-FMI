
#pragma once

#include<systemc.h>
#include<tlm.h>
#include <def_UT.hh>

class xtea_UT	: 	public sc_module,
					public virtual tlm::tlm_fw_transport_if<>
{
	public:
		
		//Creo l'interfaccia Target
		tlm::tlm_target_socket <> target_socket;

		//Creo la funzione che invocherà l'initiator
		virtual void b_transport(tlm::tlm_generic_payload& p_load, sc_time& tm);	
		//Dichiarazione funzione xtea
		void xteaEncDec();
		
		//Payload
		payloadStruct xtea_box;
		//Transizione
		tlm::tlm_generic_payload* pending_trans;
		//Temp_Var
		sc_int<32>	tmp_res_1;
		sc_int<32>	tmp_res_2;
		
		SC_HAS_PROCESS(xtea_UT);
		xtea_UT(sc_module_name name);
		
		
		
		virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);
  	 	virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t);
 		virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

};
