
#include <serbatoio.h>

serbatoio::serbatoio(sc_core::sc_module_name _name) :	sc_core::sc_module(_name),
														tdf_lsf("tdf_lsf"),
														lsf_tdf("lsf_tdf"),
														in_port("in_port"),
														out_port("out_port"),
														add("add"),
														integratore("integratore"),
														gain1("gain1", 0.6),
														gain2("gain2", -0.03),
														in_g1("in_g1"),
														g1_add("g1_add"),
														add_g2("add_g2"),
														add_int("add_int"),
														int_out("int_out")														
{
	//Realizzazione del modulo [schema a blocchi]
	
	//TDF-LSF
	tdf_lsf.inp(in_port);
	tdf_lsf.y(in_g1);
	
	//GAIN_1
	gain1.x(in_g1);
	gain1.y(g1_add);
	
	//ADDER
	add.x1(g1_add);
	add.x2(add_g2);
	add.y(add_int);
	
	//INT
	integratore.x(add_int);
	integratore.y(int_out);
	
	//GAIN_2
	gain2.x(int_out);
	gain2.y(add_g2);
	
	//LSF-TDF
	lsf_tdf.x(int_out);
	lsf_tdf.outp(out_port);
}
	
serbatoio::~serbatoio()	{}
																						
