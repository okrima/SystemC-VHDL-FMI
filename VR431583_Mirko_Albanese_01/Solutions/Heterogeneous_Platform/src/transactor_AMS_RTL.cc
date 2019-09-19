#include <transactor_AMS_RTL.h>

transactor_AMS_RTL::transactor_AMS_RTL(sc_core::sc_module_name)	:	x_rtl("x_rtl"),
																			x_ams("x_ams")
{
}

transactor_AMS_RTL::~transactor_AMS_RTL()
{
}

void transactor_AMS_RTL::set_attributes() {}

void transactor_AMS_RTL::processing()
{
	x_rtl.write(x_ams.read());	 
}
