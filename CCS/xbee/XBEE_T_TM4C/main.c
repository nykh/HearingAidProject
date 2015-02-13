// main.c
// This program implements the XBee transmitter end

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "Time.h"
#include "UART.h"
#include "XBEE.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#define BUFFER_SIZE 30
char static buf[BUFFER_SIZE];

int main(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |
	               SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	Time_Init();
	UART_Init();
	XBEE_Init(0x69);


	for(;;){
		UART_OutString("Instring: ");
		UART_InString(buf, BUFFER_SIZE);
		UART_NewLine(); 
		
		XBee_CreateTxFrame(buf);
		XBee_SendTxFrame();
	}
}
