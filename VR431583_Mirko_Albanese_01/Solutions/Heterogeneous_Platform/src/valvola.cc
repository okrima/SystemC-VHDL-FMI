#include <valvola.h>
#include <comandi.h>

void valvola::set_attributes()
{	
	//in_flag.set_timestep(5, SC_MS);
	//in_flag.set_delay(1);
	//in_soglia.set_delay(1);

	apertura = 0;
	
}

void valvola::processing()
{			
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
