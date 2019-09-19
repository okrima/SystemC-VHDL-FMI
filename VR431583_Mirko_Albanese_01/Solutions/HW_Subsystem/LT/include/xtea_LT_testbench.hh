
#pragma once

#include <systemc.h>
#include <tlm.h>
#include <def_LT.hh>
#include <tlm_utils/tlm_quantumkeeper.h>

class xtea_LT_testbench	:	public sc_module,
							public virtual tlm::tlm_bw_transport_if<>
{
	private:
		SC_HAS_PROCESS(xtea_LT_testbench);
		
		//Dichiarazione del Thread
		void run();
		
		//Gestione del tempo a livello globale
		tlm_utils::tlm_quantumkeeper	quantum;
				
		virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
  		virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);
		
	public:
		//Creo l'interfaccia dell'initiator
		tlm::tlm_initiator_socket<> initiator_socket;
		
		//Costruttore
		xtea_LT_testbench(sc_module_name name);
};
