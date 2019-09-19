
#include "valvola.h"

void valvola::set_attributes()
{
	//set_timestep(sc_core::sc_time(1,sc_core::SC_MS));
	
	apertura = 0;
}

void valvola::processing()
{
		cout << in_flag.read();

		double delta = 0.25;
		// Se Inattivo è inattivo, mantiene il valore corrente
		if(in_flag.read() == APERTO)
		{
			if ((apertura + delta) >= in_soglia.read())
				a.write(in_soglia.read());
			else
				apertura = apertura + delta;
				a.write(apertura);
		}
		else if(in_flag.read() == CHIUSO)
		{
			if  (((apertura - delta) <= 0))
				a.write(0);
			else
				apertura = apertura - delta;
				a.write(apertura);
		}
		else
		{
			a.write(apertura);
		}
					
		
}
