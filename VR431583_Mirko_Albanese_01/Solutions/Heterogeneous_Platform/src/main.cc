#include <valvola.h>
#include <serbatoio.h>
#include <converter.h>
#include <controllore_TLM.h>
#include <transactor_RTL_AMS.h>
#include <transactor_AMS_RTL.h>
#include <transactor_RTL_TLM.h>
#include <transactor_TLM_RTL.h>
#include <xtea_RTL.hh>


int sc_main(int arg, char*argv[])
{ 
	controllore_TLM Controllore_TLM("controllore_TLM");
	transactor_RTL_AMS rtl_ams("valvola_interfaccia");
	transactor_AMS_RTL ams_rtl("serbatoio_interfaccia");
	transactor_TLM_RTL tlm_rtl("tlm_rtl");;
	transactor_RTL_TLM rtl_tlm("rtl_tlm");
	xtea_RTL xt("xtea");
	serbatoio Serbatoio("serbatoio");
	valvola Valvola("valvola");
	
	sc_signal<sc_uint<32> > parola_1_dec_rtl;
  sc_signal<sc_uint<32> > parola_2_dec_rtl;
  sca_tdf::sca_signal<double> soglia_ams;
  sca_tdf::sca_signal<sc_uint<32>> comando_ams;
  sca_tdf::sca_signal<double> apertura;
  sca_tdf::sca_signal<double> livello_acqua_ams;
  sc_signal<double> livello_acqua_rtl;
    
	sc_signal<double> soglia_rtl;
	sc_signal<sc_uint<32>>	parola_1_rtl;
	sc_signal<sc_uint<32>>	parola_2_rtl;
	sc_signal<sc_uint<32> > key1;
  sc_signal<sc_uint<32> > key2;
  sc_signal<sc_uint<32> > key3;
  sc_signal<sc_uint<32> > key4;
  sc_signal<bool> mode;
  sc_signal<bool> reset;
  sc_signal<bool> din;
  sc_signal<bool> dout;
  sc_signal<bool> clock; 
	
	//Controllore <--> transattore TLM-RTL
	Controllore_TLM.initiator_socket(tlm_rtl.target_socket);
	tlm_rtl.W_0(parola_1_rtl);
	tlm_rtl.W_1(parola_2_rtl);
	tlm_rtl.key1(key1);
	tlm_rtl.key2(key2);
	tlm_rtl.key3(key3);
	tlm_rtl.key4(key4);
	tlm_rtl.mode(mode);
	tlm_rtl.din_rdy(din);
	tlm_rtl.reset(reset);
	tlm_rtl.clock(clock);
	tlm_rtl.soglia(soglia_rtl);
	
	//Transattore TLM-RTL <--> Xtea
	xt.in_1(parola_1_rtl);
	xt.in_2(parola_2_rtl);
	xt.in_ready(din);
	xt.mode(mode);
	xt.clock(clock);
	xt.reset(reset);
	xt.k_0(key1);
	xt.k_1(key2);
	xt.k_2(key3);
	xt.k_3(key4);
	xt.res_1(parola_1_dec_rtl);
	xt.res_2(parola_2_dec_rtl);
	xt.res_ready(dout);
	
	//Transattore TLM-RTL <--> Transattore RTL-AMS
	rtl_ams.dout(dout);
	rtl_ams.soglia_rtl(soglia_rtl);
	rtl_ams.res1_rtl(parola_1_dec_rtl);
	rtl_ams.res2_rtl(parola_2_dec_rtl);
	rtl_ams.soglia_ams(soglia_ams);
	rtl_ams.comando_ams(comando_ams);
	
	//Transattore RTL-AMS <--> Valvola
	Valvola.in_flag(comando_ams);
	Valvola.in_soglia(soglia_ams);
	Valvola.a(apertura);
	
	//Valvola <--> Serbatoio
	Serbatoio.in_port(apertura);
	Serbatoio.out_port(livello_acqua_ams);
	
	//Serbatorio <--> Transattore AMS-RTL
	ams_rtl.x_ams(livello_acqua_ams);
	ams_rtl.x_rtl(livello_acqua_rtl);
	
	//Transattore AMS-RTL <--> Transattore RTL-TLM
	rtl_tlm.initiator_socket(Controllore_TLM.target_socket);
	rtl_tlm.livello_acqua_rtl(livello_acqua_rtl);
		
	//trace_file
  sc_trace_file *rtl_trace = sc_create_vcd_trace_file("rtl_trace");
  sc_trace(rtl_trace, parola_1_rtl, "word_0");
  sc_trace(rtl_trace, parola_2_rtl, "word_1");
  sc_trace(rtl_trace, din, "din");
  sc_trace(rtl_trace, parola_1_dec_rtl, "out_0");
	sc_trace(rtl_trace, parola_2_dec_rtl, "Out_1");

	sca_util::sca_trace_file *trf = sca_util::sca_create_vcd_trace_file("trf.vcd");
  sca_util::sca_trace(trf, apertura, "apert");
  sca_util::sca_trace(trf, livello_acqua_ams, "acqua");
  sca_util::sca_trace(trf, soglia_ams, "treshold_ams");
  sca_util::sca_trace(trf, comando_ams, "flag");
  
  sc_core::sc_start(1200, SC_SEC);

  sca_util::sca_close_vcd_trace_file(trf);
  sc_close_vcd_trace_file(rtl_trace);

  return 0;

}
