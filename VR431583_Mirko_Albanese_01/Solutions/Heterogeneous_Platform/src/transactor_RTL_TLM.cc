#include <transactor_RTL_TLM.h>

transactor_RTL_TLM::transactor_RTL_TLM(sc_module_name name)	:	sc_module(name)
{
	initiator_socket(*this);
	m_qk.set_global_quantum(sc_time(500, SC_NS));
    m_qk.reset();
    
    SC_THREAD(IOPROCESS);
}

void transactor_RTL_TLM::IOPROCESS()
{	
	while(true)
	{
		wait(4, SC_SEC);

		//cout << "\n\tCONTROLLORE - Decodifico..." << endl;
		Dec();	
	}
}

void transactor_RTL_TLM::Dec()
{	
	watertankStruct pack;
	tlm::tlm_generic_payload payload; //creazione del payload
    sc_time local_time = m_qk.get_local_time();
    payload.set_data_ptr((unsigned char *)&pack);
    
    payload.set_write();
    
    pack.livello_acqua = livello_acqua_rtl.read();
      
    initiator_socket -> b_transport(payload, local_time);
}

void transactor_RTL_TLM::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{}
tlm::tlm_sync_enum transactor_RTL_TLM::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
    return tlm::TLM_ACCEPTED;
}
