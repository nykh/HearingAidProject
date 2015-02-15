// main.c
// This program implements the XBee transmitter end

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "Time.h"
#include "XBEE.h"
#include "debug.h"


void EnableInterrupts(void);  // Enable interrupts

int main(void) { volatile unsigned long dummy;
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |
	               SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	_____debug_Init();
	_____debug_heartbeat(); // on
	Time_Init();
	XBEE_Init();
	_____debug_heartbeat(); // off
	EnableInterrupts();
	XBEE_Reset();
	_____debug_heartbeat(); // on


	for(;;);
}
