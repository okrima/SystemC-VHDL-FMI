
#include<xtea_UT.hh>
#include<xtea_UT_testbench.hh>

class xtea_main :	public sc_module
{
	private:
		xtea_UT	target;
		xtea_UT_testbench	initiator;
		
	public:
		xtea_main(sc_module_name name)	:	sc_module(name),
											target("target"),
											initiator("initiator")
		{
			initiator.initiator_socket(target.target_socket);	//Binding
		}

};

int main (int argc, char* argv[])
{
	xtea_main top("xtea_top");
	sc_start();
	
	return 0;
}
