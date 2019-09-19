
#include <controllore.h>
	

void controllore::set_attributes()
{

	set_timestep(sc_core::sc_time(5, sc_core::SC_MS));
	//Per evitare loop permetto uno scheduling ritardando il livello dell'acqua, segnale  di ingresso al controllore
	in_c.set_delay(1);
	//Contatore iniziale
	i = 0;
	//Soglia iniziale del controllore
	soglia = 0.7;
}

void controllore::processing()
{
	double l_acqua = in_c.read();

	cout << "Livello Acqua: " << l_acqua << endl;
	
	if(i == 1000)
	{		
		if(l_acqua < 5)
		{
			soglia = soglia*1.1;
			out_flag.write(APERTO);
			out_soglia_c.write(soglia);
		}
		else if(l_acqua > 8.8)
		{
			soglia = soglia*0.7;
			out_flag.write(CHIUSO);
			out_soglia_c.write(soglia);
		}
		else
		{
			out_flag.write(INATTIVO);	
		}
		
		i = 0;
	}
	else
		i++;
}
