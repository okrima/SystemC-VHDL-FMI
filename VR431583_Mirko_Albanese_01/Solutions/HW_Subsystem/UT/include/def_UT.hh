
#pragma once

#include <systemc.h>

//Definisco quello che sarà la struttura del mio payload

struct payloadStruct 
{
	sc_int<32>	in_1;	//Input 1
	sc_int<32>	in_2;	//Input 2
	sc_int<32>	key_1;	//Key 1
	sc_int<32>	key_2;	//Key 2
	sc_int<32>	key_3;	//Key 3
	sc_int<32>	key_4;	//Key 4
	sc_int<32>	out_1;	//Out 1
	sc_int<32>	out_2;	//Out 2
	sc_int<32>	mode;	//Mode
};
