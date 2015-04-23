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
#include "filter.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts



int main(void){
#define BUFFER_SIZE 10
	// 50 MHz
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL
			     | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	Time_Init();
	_____debug_Init();
	XBEE_Init();
    DAC_Init(6250);

    EnableInterrupts();

	for(;;){
		uint16_t sample = XBEE_InChar();
		DAC_Put(sample);
	}
}
