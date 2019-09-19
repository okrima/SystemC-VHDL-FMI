#include <transactor_RTL_AMS.h>

transactor_RTL_AMS::transactor_RTL_AMS(sc_core::sc_module_name)	:	dout("dout"),
																	soglia_rtl("soglia_rtl"),
																	res1_rtl("res1_rtl"),
																	res2_rtl("res2_rtl"),
																	soglia_ams("soglia_ams"),
																	comando_ams("comando_ams")
{}

void transactor_RTL_AMS::set_attributes() {}

void transactor_RTL_AMS::processing()
{
	// Interfaccia Valvola Da RTL a AMS

	comando_ams.write(res1_rtl.read()*2 + res2_rtl.read());
		
	soglia_ams.write(soglia_rtl.read());
}
