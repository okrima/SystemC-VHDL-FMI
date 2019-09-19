#include <controllore_TLM.h>
#include <converter.h>

controllore_TLM::controllore_TLM(sc_module_name name)	:	sc_module(name)
{
	initiator_socket(*this);
	target_socket(*this);
		
	m_qk.set_global_quantum(sc_time(500, SC_MS));
	m_qk.reset();
	soglia = 0.7;	//Come da specifica
}

controllore_TLM::~controllore_TLM() {}

void controllore_TLM::run()
{
	payloadStruct	xtea_box;
	tlm::tlm_generic_payload payload;
		
	xtea_box.key_1 = 0x6a1d78c8;
	xtea_box.key_2 = 0x8c86d67f;
	xtea_box.key_3 = 0x2a65bfbe;
	xtea_box.key_4 = 0xb4bd6e46;
		
	//cout << "Watertank | Valve | Controller System & Xtea Algorithm\t[TLM | AMS | RTL]\n" << endl;
		
	payload.set_data_ptr((unsigned char*) &xtea_box);
	payload.set_write();	

	//init tempo
	sc_time local_time = m_qk.get_local_time();

	cout << "Livello Acqua: " << livello_acqua << endl;

	//Calcolo soglia
	if(livello_acqua < 5)
	{
		
		soglia = soglia*1.1;
		xteaEnc(APERTO);

		xtea_box.in_1 = in_1;
		xtea_box.in_2 = in_2;	
		
	}
	else if(livello_acqua > 8.8)
	{
		soglia = soglia *0.7;
		xteaEnc(CHIUSO);
			
		xtea_box.in_1 = in_1;
		xtea_box.in_2 = in_2;
	}
	else
	{
		xteaEnc(INATTIVO);
				
		xtea_box.in_1 = in_1;
		xtea_box.in_2 = in_2;
	}	
				
	xtea_box.soglia = soglia;
	initiator_socket -> b_transport(payload, local_time);
		
	//Aggiorno il quantum keeper
	m_qk.set(local_time);
	if(m_qk.need_sync())
		m_qk.sync();
}

void controllore_TLM::xteaEnc(int comando)
{	
	//Elaboro

	sc_uint<64> somma;
	sc_uint<32> i, v0, v1, temp;
	v0 = comando/2;
	v1 = comando%2;
	delta = 0x9e3779b9;
	somma = 0;
		
	for (i=0; i < 32; i++) {

    	if((somma & 3) == 0) 
		    temp = xtea_box.key_1;
		else if((somma & 3) == 1) 
		    temp = xtea_box.key_2;
		else if ((somma & 3) == 2)
		    temp = xtea_box.key_3; 
		else temp = xtea_box.key_4; 
			  
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (somma + temp);
	  
		somma += delta;

		if(((somma>>11) & 3) == 0) 
		    temp = xtea_box.key_1;
		else if(((somma>>11) & 3) == 1) 
		    temp = xtea_box.key_2;
		else if (((somma>>11) & 3) == 2)
		    temp = xtea_box.key_3; 	
		else temp = xtea_box.key_4; 
		  
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (somma + temp);		  
		
	}	
	in_1 = v0;
	in_2 = v1;	
}

void controllore_TLM::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
	livello_acqua = (*((watertankStruct *) trans.get_data_ptr())).livello_acqua;
	trans.set_response_status(tlm::TLM_OK_RESPONSE);
	run();
}

tlm::tlm_sync_enum controllore_TLM::nb_transport_bw( tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t) { return tlm::TLM_COMPLETED; }

tlm::tlm_sync_enum controllore_TLM::nb_transport_fw(tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t) {return tlm::TLM_COMPLETED; }

unsigned int controllore_TLM::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}

bool controllore_TLM::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return 0;
}

void controllore_TLM::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) {}
