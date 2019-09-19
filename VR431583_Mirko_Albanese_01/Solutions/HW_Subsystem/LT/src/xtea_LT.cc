
#include <xtea_LT.hh>

//Costruttore
xtea_LT::xtea_LT(sc_module_name name_)	:	sc_module(name_),
											target_socket("target_socket"),
											pending_trans(NULL)
{
	target_socket(*this);
}

void xtea_LT::b_transport(tlm::tlm_generic_payload& p_load, sc_time& tm)
{
	time_ann = SC_ZERO_TIME;
	//Nella funzione invocata dal master
	xtea_box = *((payloadStruct*) p_load.get_data_ptr());	//Ritorna il valore in cui il risultato è memorizzato
	
	if(p_load.is_write())
	{
		//cout << "Primitiva ricevuta - Scrittura" << endl;
		
		//Inizio del controllo [Codifica/Decodifica] della modalità e della successiva elaborazione
			
			//Invocazione funzione algo
			xteaEncDec();
			
			xtea_box.out_1 = tmp_res_1;
			xtea_box.out_2 = tmp_res_2;
			
			*((payloadStruct*) p_load.get_data_ptr()) = xtea_box;	//Carico il valore nel payload
			
			p_load.set_response_status(tlm::TLM_OK_RESPONSE);
	}
	
	tm += time_ann;
}

void xtea_LT::xteaEncDec()
{
	sc_int<64>	sum = 0;
	sc_int<32>	i, v0, v1, temp, delta = 0x9e3779b9;;
	
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
     
     tmp_res_1 = v0;
     tmp_res_2 = v1;
     
     //Aggiorno info temporale
     time_ann += sc_time(100, SC_NS);
}

/*
void xtea_LT::endElab()
{

}
void xtea_LT::reset()
{

}
*/


bool xtea_LT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum xtea_LT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int xtea_LT::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}
