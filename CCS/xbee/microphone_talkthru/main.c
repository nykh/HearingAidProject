// main.c
// This program implements the XBee transmitter end

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "Time.h"
#include "DAC.h"
#include "debug.h"

#include "ADCT0ATrigger.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#if not_used
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
#endif

int main(void){
	uint16_t sample;

	// 50 MHz
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL
			     | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	Time_Init();
	_____debug_Init();
	ADC0_InitTimer0ATriggerSeq3PD3(16000);
	DAC_Init(0);
	_____debug_heartbeat(); // on

	EnableInterrupts();

	while(1){
		ADC_Get(&sample);
		DAC_Out(sample);
	}
}
