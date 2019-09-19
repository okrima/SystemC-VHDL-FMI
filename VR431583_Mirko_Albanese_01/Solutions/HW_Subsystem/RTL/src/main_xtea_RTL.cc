
#include <xtea_RTL.hh>
#include <xtea_RTL_testbench.hh>

int sc_main(int argc, char *argv[])
{

	sc_signal<sc_uint<32>>	in_1;
	sc_signal<sc_uint<32>>	in_2;
	sc_signal<bool>			in_ready;
	sc_signal<bool>			mode;
	sc_signal<bool>			clock;
	sc_signal<bool>			reset;
	sc_signal<sc_uint<32>>		k_0;
	sc_signal<sc_uint<32>>		k_1;
	sc_signal<sc_uint<32>>		k_2;
	sc_signal<sc_uint<32>>		k_3;
	sc_signal<sc_uint<32>>		res_1;
	sc_signal<sc_uint<32>>		res_2;
	sc_signal<bool>			res_ready;
	
	
	xtea_RTL				xtea("xtea");
	xtea_tb					tb("tb");
	
	xtea.in_1(in_1);
	xtea.in_2(in_2);
	xtea.in_ready(in_ready);
	xtea.mode(mode);
	xtea.clock(clock);
	xtea.reset(reset);
	xtea.k_0(k_0);
	xtea.k_1(k_1);
	xtea.k_2(k_2);
	xtea.k_3(k_3);
	xtea.res_1(res_1);
	xtea.res_2(res_2);
	xtea.res_ready(res_ready);
	
	tb.in_1(in_1);
	tb.in_2(in_2);
	tb.in_ready(in_ready);
	tb.mode(mode);
	tb.clock(clock);
	tb.reset(reset);
	tb.k_0(k_0);
	tb.k_1(k_1);
	tb.k_2(k_2);
	tb.k_3(k_3);
	tb.res_1(res_1);
	tb.res_2(res_2);
	tb.res_ready(res_ready);
	
	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("wave");
	sc_trace(fp,clock,"clock");
	sc_trace(fp,reset,"reset");
	sc_trace(fp,in_1,"in_1");
	sc_trace(fp,in_2,"in_2");
	sc_trace(fp,in_ready,"in_ready");
	sc_trace(fp,mode,"mode");
	sc_trace(fp,res_1,"res_1");
	sc_trace(fp,res_1,"res_2");
	sc_trace(fp,res_ready,"res_ready");

	sc_start();

	sc_close_vcd_trace_file(fp);
	
	return 0;
};
