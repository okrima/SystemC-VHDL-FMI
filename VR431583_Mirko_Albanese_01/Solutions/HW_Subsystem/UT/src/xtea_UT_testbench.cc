
#include <xtea_UT_testbench.hh>

//Costruttore
xtea_UT_testbench::xtea_UT_testbench(sc_module_name name)	: sc_module(name)
{
	initiator_socket(*this);
	SC_THREAD(run);
}

void logo()
{
	printf("\n     (((       \n");
  printf("     ((((     XTEA - eXtended Tiny Encryption Algorithm\n");
  printf("     ))))       * Design of Embedded Systems Course\n");
  printf("  _ .----.      * 2018-2019\n");
  printf("  ( |`---'|     \n");
  printf("    |     |\n");
  printf("   : .___, :\n");
  printf("    `-----'\n\n\n");
}

void xtea_UT_testbench::run()
{
	sc_int<32> check_1, check_2;

	payloadStruct	xtea_box;
	tlm::tlm_generic_payload payload;
	
	sc_time	time;
	
	logo();

	//Assegnamento Chiavi
	xtea_box.key_1 = 0x6a1d78c8;
	xtea_box.key_2 = 0x8c86d67f;
	xtea_box.key_3 = 0x2a65bfbe;
	xtea_box.key_4 = 0xb4bd6e46;
	
	for( int i = 1; i <= 100000; i++) 
	{
		//Assegnamento parole
		xtea_box.in_1 = (rand() % 0xffffffff);
		xtea_box.in_2 = (rand() % 0xffffffff);
		
		check_1 = xtea_box.in_1;
		check_2 = xtea_box.in_2;
		
		//Assegnamento modalià [Encoding]
		xtea_box.mode = 0;
		
		cout << sc_time_stamp() << " - tb: Test n° :\t" << i << endl;
		cout << "Calcolo la codifica Xtea dei numeri : " << xtea_box.in_1 << " e " << xtea_box.in_2 << "." << endl;
		
		payload.set_data_ptr((unsigned char*) &xtea_box);
		payload.set_address(0);
		payload.set_write();
			
		//Invocazione della primitiva di comunicazione
		initiator_socket->b_transport(payload, time);
		
		if(payload.get_response_status() == tlm::TLM_OK_RESPONSE)
		{
			cout << "Il protocollo è andato a buon fine, codifica avvenuta con successo" << endl;
			cout << "Il risultato della codifica è:" << xtea_box.out_1 << " e " << xtea_box.out_2 << "." << endl;	
		}
		
		cout << endl;
		
		cout << "Calcolo della decodifica Xtea dei numeri: " << xtea_box.out_1 << " e " << xtea_box.out_2 << "." << endl;
		
		xtea_box.in_1 = xtea_box.out_1;
		xtea_box.in_2 = xtea_box.out_2;
		
		//Assegnamento modalità [Decoding]
		xtea_box.mode = 1;
		
		initiator_socket->b_transport(payload, time);
		
		if(payload.get_response_status() == tlm::TLM_OK_RESPONSE)
		{
			cout << "Il protocollo è andato a buon fine, decodifica avvenuta con successo" << endl;
			cout << "Il risultato della decodifica è: " << xtea_box.out_1 << " e " << xtea_box.out_2 << "." << endl;
		}
		
		if(check_1 == xtea_box.out_1 && check_2 == xtea_box.out_2)
			cout << "DONE!\n" << endl;
		else
		{
			cout << "ERROR!" << endl;
			sc_stop();
		}
	cout << "Total simulation time: " << sc_time_stamp() << endl;
	}
	sc_stop();
		
}


void xtea_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) // Da mettere per forza elemento vuoto
{
  
}

tlm::tlm_sync_enum xtea_UT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  
  return tlm::TLM_COMPLETED; //TLM completato e andato a buon fine
}
