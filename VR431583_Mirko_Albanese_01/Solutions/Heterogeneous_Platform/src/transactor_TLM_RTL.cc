#include <transactor_TLM_RTL.h>

#define	PERIODO	40

transactor_TLM_RTL::transactor_TLM_RTL(sc_module_name name)	:	sc_module(name),
																target_socket("target_socket")
{
	target_socket(*this);
	
	SC_THREAD(trans);
	sensitive << clock.pos();
	
	SC_THREAD(clock_sg);
}

void transactor_TLM_RTL::clock_sg()
{
	while(true)
	{
		clock.write(1);
		wait(PERIODO / 2, sc_core::SC_US);
		clock.write(0);
		wait(PERIODO / 2, sc_core::SC_US);
	}
}

void transactor_TLM_RTL::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
	packet = *((payloadStruct *) trans.get_data_ptr());
	decodifica.notify();
	wait(fine_dec);
}

void transactor_TLM_RTL::trans()
{
	while(true)
	{
		//cout << "\n\tRTL - Attendo il turno di decodifica" << endl;
		wait(decodifica);
		//cout << "\n\tRTL - Partito" << endl;
		//Resetto		
		reset.write(0);
		wait();
		//cout << "\n\tRTL - Resettato" << endl;
		//Avvio
		reset.write(1);
		wait();
		//cout << "\n\tRTL - Avvio" << endl;
		mode.write(1);
		key1.write(packet.key_1);
		key2.write(packet.key_2);
		key3.write(packet.key_3);
		key4.write(packet.key_4);
		W_0.write(packet.in_1);
		W_1.write(packet.in_2);
		din_rdy.write(1);
		wait();
		//cout << "\n\tEseguito..." << endl;
		din_rdy.write(0);
		fine_dec.notify();
		soglia.write(packet.soglia);
		wait();
		
	}
}

bool transactor_TLM_RTL::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return false;
}

tlm::tlm_sync_enum transactor_TLM_RTL::nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

unsigned int transactor_TLM_RTL::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}
