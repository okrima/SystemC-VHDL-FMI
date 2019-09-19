
#include <controllore.h>
#include <valvola.h>
#include <serbatoio.h>

int sc_main(int arg, char*argv[])
{
//Risoluzione temporale simulazione
 //sc_core::sc_set_time_resolution(1.0, sc_core::SC_MS);
 
	sca_tdf::sca_signal<double> apert;	//Apertura
	sca_tdf::sca_signal<double> x;		//Livello Acqua
	sca_tdf::sca_signal<double> out_soglia;
	sca_tdf::sca_signal<int> out_flag;	//Comando
	
	//Serbatoio
	serbatoio Serbatoio("serbatoio");
	Serbatoio.in_port(apert);
	Serbatoio.out_port(x);
	
	//Controllore
	controllore Controllore("controllore");
	Controllore.in_c(x);
	Controllore.out_soglia_c(out_soglia);
	Controllore.out_flag(out_flag);
	
	//Valvola
	valvola Valvola("valvola");
	Valvola.in_flag(out_flag);
	Valvola.in_soglia(out_soglia);
	Valvola.a(apert);

	//trace_file
  sca_util::sca_trace_file *trf = sca_util::sca_create_vcd_trace_file("trf.vcd");
  sca_util::sca_trace(trf, apert, "apert");
  sca_util::sca_trace(trf, x, "x");
  sca_util::sca_trace(trf, out_soglia, "treshold");
  sca_util::sca_trace(trf, out_flag, "flag");
  
  sc_core::sc_start(1000, sc_core::SC_SEC);

  sca_util::sca_close_vcd_trace_file(trf);

  return 0;


}
