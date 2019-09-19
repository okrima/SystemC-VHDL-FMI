#pragma once

#include <systemc.h>
#include <tlm.h>
#include <converter.h>

class transactor_TLM_RTL	:	public sc_module,
								public virtual tlm::tlm_fw_transport_if<>
{
	public:
		tlm::tlm_target_socket<>	target_socket;
		
		virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& t );
        //metodi non usati
        virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi & dmi_data );
        virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,tlm::tlm_phase& phase,sc_time& t);
        virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
        
        sc_event decodifica, fine_dec;
        
        transactor_TLM_RTL(sc_module_name name);
        
        sc_out<bool> clock;
        sc_out<double> soglia;
        sc_out<sc_uint<32> > W_0;
        sc_out<sc_uint<32> > W_1;
        sc_out<sc_uint<32> > key1;
        sc_out<sc_uint<32> > key2;
        sc_out<sc_uint<32> > key3;
        sc_out<sc_uint<32> > key4;
        sc_out<bool> mode;
        sc_out<bool> din_rdy;
        sc_out<bool> reset;
        
        void trans();
        void clock_sg();
        SC_HAS_PROCESS(transactor_TLM_RTL);

        payloadStruct	packet;
};
