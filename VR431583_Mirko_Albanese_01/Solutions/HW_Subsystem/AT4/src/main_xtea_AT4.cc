
#include<xtea_AT4.hh>
#include<xtea_AT4_testbench.hh>

class xtea_main :	public sc_module
{
	private:
		xtea_AT4	target;
		xtea_AT4_testbench	initiator;
		
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
