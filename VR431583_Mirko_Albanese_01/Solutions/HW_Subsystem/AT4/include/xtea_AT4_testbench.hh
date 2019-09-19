
#pragma once

#include <systemc.h>
#include <tlm.h>
#include <def_AT4.hh>
#include <tlm_utils/tlm_quantumkeeper.h>

class xtea_AT4_testbench	:	public sc_module,
								public virtual tlm::tlm_bw_transport_if<>
{
	private:
		SC_HAS_PROCESS(xtea_AT4_testbench);
		
		//Dichiarazione del Thread
		void run();
		
		sc_event	risposta;
		bool resp_pend;
		
		virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
				
  		virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);
		
	public:
		//Creo l'interfaccia dell'initiator
		tlm::tlm_initiator_socket<> initiator_socket;
		
		//Costruttore
		xtea_AT4_testbench(sc_module_name name);
};
