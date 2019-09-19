
#include <xtea_AT4_testbench.hh>

//Costruttore
xtea_AT4_testbench::xtea_AT4_testbench(sc_module_name name)	:	sc_module(name),
																resp_pend(false)
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

void xtea_AT4_testbench::run()
{	
	sc_time localTime = SC_ZERO_TIME;
	
	sc_int<32> check_1, check_2;

	payloadStruct	xtea_box;
	tlm::tlm_generic_payload payload;
	
	logo();
	
	cout << "Xtea Algorithm\t\t[TLM - AT4]\n" << endl;

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
		
		payload.set_data_ptr((unsigned char*) &xtea_box);
		payload.set_address(0);
		payload.set_write();
		
		//Dopo aver impostato il pacchetto per la transazione AT4, inizializzo la prima fase dell'Initiator
		tlm::tlm_phase phase = tlm::BEGIN_REQ;	//Prima fase
		
		cout << endl;
		cout << "--------------------------------" << endl;
		cout << sc_time_stamp() << " - tb: Test n° :\t" << i << endl;
		cout << "Calcolo la codifica Xtea dei numeri : " << xtea_box.in_1 << " e " << xtea_box.in_2 << "." << endl;	
		
		//Invocazione della primitiva di comunicazione chiamando la nb_transport_fw
		tlm::tlm_sync_enum result = initiator_socket->nb_transport_fw(payload, phase, localTime);
		
		if(result == tlm::TLM_COMPLETED)
		{	
			//In questo caso se il target completa immediatamente la trasizione, vuol dire che è avvenuto un errore, in questo caso stoppiamo la simulazione.
			
			cout << "[ERROR:] Errore nella transazione nb_transport_fw. Simulazione terminata." << endl;
			
			sc_stop();
		}
		
		if(phase != tlm::END_REQ)
		{
			//In questo caso la fase deve essere quella finale [END_REQ], quindi se così non è, la simulazione viene terminata.
			
			cout << "[ERROR:] Fase del protocollo inaspettata. Simulazione terminata" << endl;
			
			sc_stop();
		}
		
		resp_pend = true;	//Abbiamo una trasnsizione in sospeso
		wait(risposta);	//Si mette in attesa fin quando il target/slave non esprime una notify per svegliare il thread
		
		//Il target ha invocato la nb_transport_bw. Una volta risvegliato QUESTO thread non ho più risposte in attesa, quindi:
		resp_pend = false;
		
		//Ricevuto il pacchetto re-inizializzo il payload specificando la lettura
		phase = tlm::BEGIN_REQ;
		
		payload.set_data_ptr((unsigned char*) &xtea_box);
		payload.set_address(0);
		payload.set_read();
		
		//Invocazione della primitiva di comunicazione chiamando la nb_transport_fw
		result = initiator_socket->nb_transport_fw(payload, phase, localTime);
		
		if(result == tlm::TLM_COMPLETED)
		{
			cout << "[ERROR:] Errore nella transazione. Simulazione terminata." << endl;
			sc_stop();
		}
		
		if(phase != tlm::END_REQ)
		{
			cout << "[ERROR:] Dichiarazione della fase inaspettata. Simulazione forzata." << endl;
			
			sc_stop();
		}
		
		resp_pend = true;
		wait(risposta);
		
		resp_pend = false;
		
		if(check_1 == xtea_box.out_1 && check_2 == xtea_box.out_2)
			cout << "DONE!" << endl;
		else
			cout << "ERROR!" << endl;
	}	
	sc_stop();
		
}

tlm::tlm_sync_enum xtea_AT4_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{

	if(!resp_pend)	//La transazione deve rispondere al master, quindi non ci deve essere una transizione in attesa
	{
		trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
		return tlm::TLM_COMPLETED; //TLM completato e andato a buon fine
	}
	
	if(phase !=tlm::BEGIN_RESP)	//Controllare che la fase della transizione sia diversa di BEGIN_RES in modo da segnalare errore
	{
		trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
		return tlm::TLM_COMPLETED;
	}
	
	risposta.notify();	//Svegliare il processo dormiente
	
	phase = tlm::END_RESP;
	
	return tlm::TLM_UPDATED;	
	
}

void xtea_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
  
}
