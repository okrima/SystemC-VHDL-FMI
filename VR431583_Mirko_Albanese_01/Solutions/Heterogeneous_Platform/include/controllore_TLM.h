#pragma once

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include <comandi.h>
#include <converter.h>

class controllore_TLM	:	public sc_module,
							virtual public tlm::tlm_bw_transport_if<>,
							tlm::tlm_fw_transport_if<>
{
	private:
		
		//Metodi non implementati virtuali	
		virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t);
		virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t);
		virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);
		virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data);
		virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
		
		void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);
		
		tlm_utils::tlm_quantumkeeper m_qk;
		
		//Metodi implementazione
		void run();
		
		payloadStruct xtea_box;
		
		double soglia;
		double livello_acqua;
		
		void xteaEnc(int comando);
		
	private:
		sc_uint<32> in_1;
		sc_uint<32> in_2;
        sc_uint<32> delta;
        
	public:
	
		tlm::tlm_initiator_socket<> initiator_socket;
		tlm::tlm_target_socket<> target_socket;
		
		SC_HAS_PROCESS(controllore_TLM);
		
		//Costruttore
		controllore_TLM(sc_module_name nome);
		~controllore_TLM();
};

