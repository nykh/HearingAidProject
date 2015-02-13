// main.c
// This program implements the UART0 receiver end

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"

#include "Time.h"
#include "UART.h"
#include "XBEE.h"

int main(void) {
#define BUFFER_SIZE 50
	char buf[BUFFER_SIZE];
<<<<<<< HEAD
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
=======

	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
	// TODO: = 80 MHz / 4 = 20 MHz

>>>>>>> afb5b307a7485c00239ee7fc13db0405541c7361
	Time_Init();
	UART_Init();
	UART_OutString("uart initialization complete...\n\r");

	XBEE_Init(0x4E);
	puts("Receiver Log");
	for(;;){
		while(XBEE_ReceiveRxFrame(buf));
		UART_OutString(buf);
		UART_NewLine();
	}
#undef BUFFER_SIZE
}
