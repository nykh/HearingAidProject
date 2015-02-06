// main.c
// This program implements the UART0 receiver end

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
/*
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"

*/
#include "Time.h"
#include "XBEE.h"


#include "debug.h"

int main(void) {
	char buf[50];
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
	Time_Init();
	Debug_Init();	
	XBEE_Init(0x4E);
	Debug_LEDOn();
	printf("Receiver Log\r\n");
	for(;;){
		XBEE_ReceiveRxFrame(buf);
		
		//if(1){
		// if(0 == result){  // success
      printf("%s\r\n", buf);
    //}
    
    //XBEE_SendAcknoledgeFrame(result);
	}
}
