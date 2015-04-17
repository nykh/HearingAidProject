/*
 * filter.c
 *
 *  Created on: Apr 4, 2015
 *      Author: nykh
 */

#include "filter.h"

#define FILTER_LENGTH  16
int16_t macq_mem[ 2*FILTER_LENGTH ];
int16_t *MACQ = &macq_mem[FILTER_LENGTH];
uint8_t  n = 0;

#define dc_offset       128
int16_t Rxx9, Rxx8, Rxx7;

/// not thread safe
uint16_t filter(uint16_t in) {

	MACQ[n] = MACQ[n-16] = ((int16_t) in)-dc_offset;
	n = (n+1) & 0xF;

	int16_t macq_6 = MACQ[n-6];
	Rxx7 = (31*Rxx7 + (macq_6/32*MACQ[n-7]/32))/32;
	Rxx7 = (31*Rxx8 + (macq_6/32*MACQ[n-8]/32))/32;
	Rxx7 = (31*Rxx9 + (macq_6/32*MACQ[n-9]/32))/32;
	return ( Rxx7*MACQ[n-7] + Rxx8*MACQ[n-8] + Rxx9*MACQ[n-9] )/32 + dc_offset;
}

