
#include <xtea_AT4.hh>

//Costruttore
xtea_AT4::xtea_AT4(sc_module_name name_)	:	sc_module(name_),
											target_socket("target_socket"),
											pending_trans(NULL)
{
	target_socket(*this);
	SC_THREAD(IOPROCESS);
}

void xtea_AT4::xteaEncDec()
{
	sc_int<64>	sum = 0;
	sc_int<32>	i, v0, v1, temp, delta = 0x9e3779b9;
	
	v0 = xtea_box.in_1;
	v1 = xtea_box.in_2;
	
	if(xtea_box.mode == 0)
	{
		for (i=0; i < 32; i++)       
   		{
		  if((sum & 3) == 0) 
		    temp = xtea_box.key_1;
		  else if((sum & 3) == 1) 
		    temp = xtea_box.key_2;
		  else if ((sum & 3) == 2)
		    temp = xtea_box.key_3; 
		  else temp = xtea_box.key_4; 
			  
		  v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
	  
		  sum += delta;

		  if(((sum>>11) & 3) == 0) 
		    temp = xtea_box.key_1;
		  else if(((sum>>11) & 3) == 1) 
		    temp = xtea_box.key_2;
		  else if (((sum>>11) & 3) == 2)
		    temp = xtea_box.key_3; 	
		  else temp = xtea_box.key_4; 
		  
		  v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
    	} 
    }	
    else
    {
    	sum = delta*32;     
    	for (i=0; i<32; i++) 
    	{
      	if(((sum>>11) & 3) == 0) 
      	  temp = xtea_box.key_1;
      	else if(((sum>>11) & 3) == 1) 
     	   temp = xtea_box.key_2;
     	 else if (((sum>>11) & 3) == 2)
     	   temp = xtea_box.key_3; 
     	 else temp = xtea_box.key_4;  
      
     	 v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
      
     	 sum -= delta;                         
      
     	 if((sum & 3) == 0) 
     	   temp = xtea_box.key_1;
     	 else if((sum & 3) == 1) 
     	   temp = xtea_box.key_2;
     	 else if ((sum & 3) == 2)
     	   temp = xtea_box.key_3; 
     	 else temp = xtea_box.key_4; 
      
     	 v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
     	}
     }
     
     xtea_box.out_1 = v0;
     xtea_box.out_2 = v1;
    
}

void xtea_AT4::IOPROCESS()
{
	sc_time timing_annotation;
	
	while(true)
	{
		wait(event);
		
		wait(100, SC_NS);
		
		if(pending_trans->is_write())
		//Richiesta di scrittura - write
		{
			//cout << "Invocazione Xtea Alglorithm" << endl;
			
			xtea_box.mode = 0;
			
			//cout << "[Xtea:] Calcolo la codifica Xtea dei numeri : " << xtea_box.in_1 << " e " << xtea_box.in_2 << "." << endl;
			
			
			xteaEncDec();
			
			//cout << "[Xtea:] Calcolo della decodifica Xtea dei numeri: " << xtea_box.out_1 << " e " << xtea_box.out_2 << "." << endl;
		
			xtea_box.mode = 1;
			
			xtea_box.in_1 = xtea_box.out_1;
			xtea_box.in_2 = xtea_box.out_2;
			
			xteaEncDec();		 
		
		}
		
		else	//Richiesta di lettura e stampo risultati - read
		{
			cout << "[Xtea:] Risultato decodifica: " << xtea_box.out_1 << " e " << xtea_box.out_2 << endl;				
		}
					
		//Transazione eseguita con successo
		pending_trans->set_response_status(tlm::TLM_OK_RESPONSE);
		
		//Aggiorna i dati
		*((payloadStruct*) pending_trans->get_data_ptr()) = xtea_box;
		//Aggiorna la fase
		tlm::tlm_phase phase = tlm::BEGIN_RESP;
		
		target_socket->nb_transport_bw(*pending_trans, phase, timing_annotation);	//Transazione finiale dal master.
		
		pending_trans = NULL;	//Fine protocollo AT4	
	}
}

tlm::tlm_sync_enum xtea_AT4::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
	//Se vi è già una transizione, ovvero è già partita una transazione tra master e slave, allora ritorna errore
	if(pending_trans != NULL)
	{
		//cout << "Pendiing_Trans != NULL" << endl;
		trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
		return tlm::TLM_COMPLETED;
	}
	//La transizione essendo nb_transport_fw deve avere fase BEGIN_REQ, controlliamo se non lo è settando la risposta come errore
	if(phase != tlm::BEGIN_REQ)
	{
		trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
		return tlm::TLM_COMPLETED;
	}
	
	//cout << "\t[nb_transport_fw] - Inizio" << endl;
	pending_trans = &trans;	//Occupo la transazione scaricando il pacchetto
	xtea_box = *((payloadStruct*) trans.get_data_ptr());	//Ottiene il dato
	
	phase = tlm::END_REQ;	//Modifico la fase - END_REQ
	
	event.notify(); //Sveglio il processo dormiente [IOPROCESS]
	
	//cout << "\t[nb_transport_fw] . Fine" << endl;
	
	return tlm::TLM_UPDATED;
	
}

void xtea_AT4::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
  
}

unsigned int xtea_AT4::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}
bool xtea_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

