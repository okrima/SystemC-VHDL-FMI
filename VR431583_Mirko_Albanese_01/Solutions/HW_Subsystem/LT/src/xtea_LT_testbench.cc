
#include <xtea_LT_testbench.hh>

//Costruttore
xtea_LT_testbench::xtea_LT_testbench(sc_module_name name)	: sc_module(name)
{
	initiator_socket(*this);
	SC_THREAD(run);
	
	quantum.set_global_quantum(sc_time(500, SC_NS));
	quantum.reset();
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

void xtea_LT_testbench::run()
{
	//Stampo valore temporle e il riferimento dello starter
	cout << sc_time_stamp() << " - " << name() << " - run" << endl;
	
	sc_time localTime = quantum.get_local_time();
	
	sc_int<32> check_1, check_2;

	payloadStruct	xtea_box;
	tlm::tlm_generic_payload payload;
	
	logo();

	//Assegnamento Chiavi
	xtea_box.key_1 = 0x6a1d78c8;
	xtea_box.key_2 = 0x8c86d67f;
	xtea_box.key_3 = 0x2a65bfbe;
	xtea_box.key_4 = 0xb4bd6e46;
	
	for(int i = 1; i <= 100000; i++)
	{
		
		//Assegnamento parole
		xtea_box.in_1 = (rand() % 0xffffffff);
		xtea_box.in_2 = (rand() % 0xffffffff);
		
		check_1 = xtea_box.in_1;
		check_2 = xtea_box.in_2;
		
		//Assegnamento modalià [Encoding]
		xtea_box.mode = 0;
		
		cout << endl;
		cout << "--------------------------------" << endl;
		cout << sc_time_stamp() << " - tb: Test n° :\t" << i << endl;
		cout << "Calcolo la codifica Xtea dei numeri : " << xtea_box.in_1 << " e " << xtea_box.in_2 << "." << endl;
		
		payload.set_data_ptr((unsigned char*) &xtea_box);
		payload.set_address(0);
		payload.set_write();
		
		//Aggiorno l'informazione temporale
		localTime = quantum.get_local_time();
			
		//Invocazione della primitiva di comunicazione
		initiator_socket->b_transport(payload, localTime);
		
		if(payload.get_response_status() == tlm::TLM_OK_RESPONSE)
		{
			//cout << "Il protocollo è andato a buon fine, codifica avvenuta con successo" << endl;
			cout << "Il risultato della codifica è:" << xtea_box.out_1 << " e " << xtea_box.out_2 << "." << endl;	
		}
		
		cout << endl;
		
		cout << "Calcolo della decodifica Xtea dei numeri: " << xtea_box.out_1 << " e " << xtea_box.out_2 << "." << endl;
		
		xtea_box.in_1 = xtea_box.out_1;
		xtea_box.in_2 = xtea_box.out_2;
		
		//Assegnamento modalità [Decoding]
		xtea_box.mode = 1;
		
		initiator_socket->b_transport(payload, localTime);
		
		if(payload.get_response_status() == tlm::TLM_OK_RESPONSE)
		{
			//cout << "Il protocollo è andato a buon fine, decodifica avvenuta con successo" << endl;
			cout << "Il risultato della decodifica è: " << xtea_box.out_1 << " e " << xtea_box.out_2 << "." << endl;
		}
		
		if(check_1 == xtea_box.out_1 && check_2 == xtea_box.out_2)
			cout << "DONE!" << endl;
		else
		{
			cout << "ERROR!" << endl;
			sc_stop();
		}
		
		//Controlliamo se abbiamo bisogno di sincronizzare l'initiator e il target [Temporal Decoupling]
		cout << "Time: " << sc_time_stamp() << " + " << localTime << endl;
		quantum.set(localTime);
		if(quantum.need_sync())
		{
			cout << "Sync..." << endl;
			quantum.sync();
			cout << "##############" << endl;
		}
	}
	sc_stop();
		
}


void xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) // Da mettere per forza elemento vuoto
{
  
}

tlm::tlm_sync_enum xtea_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  
  return tlm::TLM_COMPLETED; //TLM completato e andato a buon fine
}
