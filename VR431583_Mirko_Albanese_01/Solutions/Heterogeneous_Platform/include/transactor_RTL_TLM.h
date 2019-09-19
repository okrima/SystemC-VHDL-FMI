#pragma once

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include <converter.h>

class transactor_RTL_TLM	:	public sc_module,
								public virtual	tlm::tlm_bw_transport_if <>
{
	public:
		tlm::tlm_initiator_socket<>	initiator_socket;
		
		 virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
        virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);
        
        SC_HAS_PROCESS(transactor_RTL_TLM);
        
        transactor_RTL_TLM(sc_module_name name);
        
        sc_in<double> livello_acqua_rtl;
        
	private:
 		tlm_utils::tlm_quantumkeeper m_qk;
 		
 		void	IOPROCESS();
 		void	Dec();
};  
