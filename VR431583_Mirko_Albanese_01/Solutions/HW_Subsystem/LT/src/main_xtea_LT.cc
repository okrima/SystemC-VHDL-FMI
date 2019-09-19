
#include<xtea_LT.hh>
#include<xtea_LT_testbench.hh>

class xtea_main :	public sc_module
{
	private:
		xtea_LT	target;
		xtea_LT_testbench	initiator;
		
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
