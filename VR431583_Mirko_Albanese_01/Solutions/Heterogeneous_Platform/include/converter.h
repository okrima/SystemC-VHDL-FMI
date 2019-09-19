#pragma once

#include<systemc.h>
#include<systemc-ams.h>

//Definisco quello che sarà la struttura del mio payload

struct payloadStruct 
{
	int soglia;
	sc_uint<32>	in_1;	//Input 1
	sc_uint<32>	in_2;	//Input 2
	sc_uint<32>	key_1 = 0x6a1d78c8;	//Key 1
	sc_uint<32>	key_2 = 0x8c86d67f;	//Key 2
	sc_uint<32>	key_3 = 0x2a65bfbe;	//Key 3
	sc_uint<32>	key_4 = 0xb4bd6e46;	//Key 4
	sc_uint<32>	out_1;	//Out 1
	sc_uint<32>	out_2;	//Out 2
	bool		mode;	//Mode
};

struct watertankStruct
{
	double livello_acqua;
};

/*
uint64_t double_to_uint(double doubl);

double uint_to_double(uint64_t uint);

double uints_to_double(uint32_t uint_1, uint32_t uint_2);

double sc_uints_to_double(sc_uint<32> uints_1, sc_uint<32> uints_2);
*/
