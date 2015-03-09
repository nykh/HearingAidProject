// main.c
// This program implements the XBee transmitter end

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "Time.h"
#include "XBEE.h"
#include "DAC.h"
#include "debug.h"


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

typedef union frame_u {
	struct {
		char upper_four_bits;
		char odd_byte;
		char even_byte;
	} name;

	char array[3];
} frame;

typedef struct tuple_s {
	uint16_t odd;
	uint16_t even;
} tuple;

frame encode_frame(const uint16_t *odd, const uint16_t *even) {
	// magic: the TM4C architecture is Little endian and byte addressable
	// this allows to take the bytes of the sample without incurring shift
	register uint8_t *odd_seg = (uint8_t *) odd;
	register uint8_t *even_seg = (uint8_t *) even;

	frame f;
	f.name.odd_byte = *odd_seg;
	f.name.even_byte = *even_seg;
	f.name.upper_four_bits = (odd_seg[1] << 4) | even_seg[1];

	return f;
}

tuple decode_frame(frame f) {
	uint16_t upper_four_bits = f.name.upper_four_bits;
	tuple t;
	register uint8_t *odd_seg = (uint8_t *) &t.odd;
	register uint8_t *even_seg = (uint8_t *) &t.even;

	*odd_seg = f.name.odd_byte;
	*even_seg = f.name.even_byte;
	odd_seg[1] = upper_four_bits >> 4;
	even_seg[1] = upper_four_bits & 0xF;

	return t;
}

int main(void){
#define BUFFER_SIZE 10
	char buf[BUFFER_SIZE];

	// 50 MHz
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL
			     | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	Time_Init();
	_____debug_Init();
	XBEE_Init();
    DAC_Init(14000);

    EnableInterrupts();

    frame f; // received frame
    tuple t; //the decoded tuple

	for(;;){


#if NICK_STYLE
		XBEE_InString(buf);

		strncpy(f.array,buf,3);  //copy from buf to frame array
		t=decode_frame(f);       //decode

		//TODO does this work?
		DAC_Out(t.odd);
		Time_Wait(14000);
		DAC_Out(t.even);
#else
		uint16_t sample = XBEE_InChar();
		DAC_Out(sample << 4);
#endif
	}
}
