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


void EnableInterrupts(void);  // Enable interrupts

int main(void) { volatile unsigned long dummy;
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |
	               SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    dummy = SYSCTL_RCGC2_R;

    GPIO_PORTF_DIR_R |= 0x04;
	GPIO_PORTF_DEN_R |= 0x04;

	/***debug******/ GPIO_PORTF_DATA_R &=~ 0x04;
	Time_Init();
	XBEE_Init();
	EnableInterrupts();
	XBEE_Reset();
	/***debug******/ GPIO_PORTF_DATA_R |= 0x04;

	for(;;);
}
