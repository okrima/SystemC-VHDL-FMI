
#include<xtea_RTL.hh>

xtea_RTL::xtea_RTL(sc_core::sc_module_name module_name) :
	sc_module(module_name),
	in_ready("in_ready"),
	in_1("in_1"),
	in_2("in_2"),
	k_0("k_0"),
	k_1("k_1"),
	k_2("k_2"),
	k_3("k_3"),
	mode("mode"),
	clock("clock"),
	reset("reset"),
	res_ready("res1_ready"),
	res_1("res_1"),
	res_2("res_2")

{
	SC_METHOD(datapath);
		sensitive << clock.pos() << reset;
		
	SC_METHOD(fsm);
		sensitive << in_ready << mode << stato;
//		sensitive << count << sum;
}


//DATAPATH

void xtea_RTL::datapath(void)
{
	if(reset.read() == 0)
	{	
		stato = RST;
		res_1.write(0);
		res_2.write(0);
		res_ready.write(0);
		sum = 0;
		temp = 0;
		count = 0;
	}
	else if (clock.read() == 1)
	{	
		stato = nuovo_stato;
		
		switch (stato)
		{			
			case RST:
				break;	
				
			case S_T:
				temp_in_1 = in_1.read();
				temp_in_2 = in_2.read();
				delta = 0x9e3779b9;
				break;
			
			case S_T02:
				delta = 0x9e3779b9; 
    			sum = delta*32;     
				break;
			
			case S_01:
				if((sum & 3) == 0) 
        			temp = k_0.read();
      			else if((sum & 3) == 1) 
        			temp = k_1.read();
     			else if ((sum & 3) == 2)
        			temp = k_2.read(); 
      			else 
      				temp = k_3.read();
      			break;
      		
      		case S_02:
      			if(((sum>>11) & 3) == 0) 
        			temp = k_0.read();
     	 		else if(((sum>>11) & 3) == 1) 
        			temp = k_1.read();
      			else if (((sum>>11) & 3) == 2)
        			temp = k_2.read(); 
      			else 
      				temp = k_3.read(); 
      			break;
      			
      		case S_03:
      			 temp_in_1 += (((temp_in_2 << 4) ^ (temp_in_2 >> 5)) + temp_in_2) ^ (sum + temp);
     			 sum += delta;
     			 break;
     			 
     		case S_04:
     			temp_in_2 -= (((temp_in_1 << 4) ^ (temp_in_1 >> 5)) + temp_in_1) ^ (sum + temp);
      			sum -= delta; 
				break;
				
			case S_05:
				temp_in_2 += (((temp_in_1 << 4) ^ (temp_in_1 >> 5)) + temp_in_1) ^ (sum + temp);
				count++;
				break;
				
			case S_06:
				temp_in_1 -= (((temp_in_2 << 4) ^ (temp_in_2 >> 5)) + temp_in_2) ^ (sum + temp);
				count++;
				break;
				
			case FINAL:
				res_1.write(temp_in_1); 
  				res_2.write(temp_in_2);
  				res_ready.write(1);
		}
	}
}

//FSM

void xtea_RTL::fsm(void)
{
	nuovo_stato = stato;
		
	switch(stato)
	{
		case RST:
			nuovo_stato = S_T;
			break;
		
		case S_T:
			if (in_ready == 1)
				{
					if(mode == 0)
					{	//Ramo Codifica
						nuovo_stato = S_01;
					}
					else
					{	//Ramo decodifica
						nuovo_stato = S_T02;
					}	
				}
			else
				nuovo_stato = S_T;			
			break;	
			
		case S_T02:
			nuovo_stato = S_02;
			break;
		
		case S_01:
			if (mode == 0)
				nuovo_stato = S_03;
			else
				nuovo_stato = S_06;
			break;
			
		case S_02:
			if (mode == 1)
				nuovo_stato = S_04;
			else
				nuovo_stato = S_05;
			break;
		
		case S_03:
			nuovo_stato = S_02;
			break;
			
		case S_04:
			nuovo_stato = S_01;
			break;
		
		case S_05:
			if (count < 31)
				nuovo_stato = S_01;
			else
				nuovo_stato = FINAL;
			break;
		
		case S_06:
			if (count < 31)
				nuovo_stato = S_02;
			else
				nuovo_stato = FINAL;
			break;
		
		case FINAL:
			nuovo_stato = RST;
			break;
	}
}	
