
#include "xtea_RTL_testbench.hh"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

xtea_tb::xtea_tb(sc_module_name name) : sc_module(name)
{	
	SC_THREAD(clk_sg);
	
	SC_THREAD(run_tb);
		sensitive << res_ready;
}

void xtea_tb::clk_sg()
{
	while(true)
	{
		clock.write(1);
		wait(PERIODO / 2, sc_core::SC_NS);
		clock.write(0);
		wait(PERIODO / 2, sc_core::SC_NS);
	}
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

void xtea_tb::run_tb()
{
	sc_uint<32> parola_1, parola_2, out_1 = 0, out_2 = 0, ky_0, ky_1, ky_2, ky_3, tmp_1, tmp_2;
		
	//cout << "XTEA algorithm."<< endl;
	
	logo();
	
	
	//Chiavi
	ky_0 = 0x6a1d78c8;
	ky_1 = 0x8c86d67f;
	ky_2 = 0x2a65bfbe;
	ky_3 = 0xb4bd6e46;
	
	k_0.write(ky_0);
	k_1.write(ky_1);
	k_2.write(ky_2);
	k_3.write(ky_3);
		
		
	for ( int i = 1; i <= 100000; i++)
	{		
		//Parole
		parola_1 = rand() % 0xffffffff;
		parola_2 = rand() % 0xffffffff;
		
		//parola_1 = 0x12345678;
		//parola_2 = 0x9abcdeff;
		
		
		tmp_1 = parola_1;
		tmp_2 = parola_2;
		
		in_1.write(parola_1);
		in_2.write(parola_2);
			
		//Abilito il reset
		reset.write(1);
		
		wait(1, sc_core::SC_NS);
		//Encoding
		mode.write(0);
		//Abilit gli ingressi
		in_ready.write(1);
		
		wait();
		
		while(res_ready.read() == 0) wait();
		
		out_1 = res_1.read();
		out_2 = res_2.read();
		
		cout << sc_time_stamp() << " - tb: Test n° :\t" << i << endl;
		
		cout << "Prima invocazione" << endl;
		cout << "Codifica di due parole " << parola_1 << " e " << parola_2 << "." << endl;
		cout << "con chiavi " << ky_0 << ky_1 << ky_2 << ky_3 << "." << endl;
		cout << "è la seguente : "<< out_1 << " " << out_2 << "." << endl;
		
		/////////////////////////////////////////////////////////////////////////////////////
		
		reset.write(0);
		in_ready.write(0);
		
		wait(1, sc_core::SC_NS);
		
		reset.write(1);
		
		wait(1, sc_core::SC_NS);
			
		parola_1 = out_1;
		parola_2 = out_2;
		
		in_1.write(parola_1);
		in_2.write(parola_2);
		
		mode.write(1);
		in_ready.write(1);
		
		wait();
		
		while(res_ready.read() == 0) wait();
		
		out_1 = res_1.read();
		out_2 = res_2.read();
		
		cout << "Seconda invocazione" << endl;
		cout << "Decodifica di due parole " << parola_1 << " e " << parola_2 << "." << endl;
		cout << "con chiavi " << ky_0 << ky_1 << ky_2 << ky_3 << "." << endl;
		cout << "è la seguente : " << out_1 << " e " << out_2 << "." << endl;
		
		cout << endl;
		
		if (out_1 != tmp_1 || out_2 != tmp_2)
		{
			cout << "Risultato ERRATO!" << endl;
			cout << endl;
		}
		
		cout << sc_time_stamp() << " - tb: DONE!\n" << endl;

		
		
		reset.write(0);
		in_ready.write(0);
		wait(1, sc_core::SC_NS);
	}
	
	in_1.write(0);
	in_2.write(0);
	
	sc_stop();
}
