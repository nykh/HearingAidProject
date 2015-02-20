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
#include "debug.h"

int main(void) {
#define BUFFER_SIZE 50
	char buf[BUFFER_SIZE];
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	_____debug_Init();
	Time_Init();
	UART_Init();
	UART_OutString("UART initialization complete...\n\r");

	XBEE_Init();

	UART_OutString("XBEE initialization complete...\n\r");
	_____debug_heartbeat();

	for(;;){
		XBEE_InString(buf);
		UART_OutString(buf);
		UART_NewLine();
	}
#undef BUFFER_SIZE
}
