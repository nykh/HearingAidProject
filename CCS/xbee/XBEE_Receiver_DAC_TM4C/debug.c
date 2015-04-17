/*
 * debug.c
 *
 *  Created on: Feb 13, 2015
 *      Author: nykh
 */
#include "debug.h"

#define TARGET_IS_BLIZZARD_RA1

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void _____debug_Init(void) {
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIO_PORTF_DATA_R &=~GPIO_PIN_1;
}

void _____debug_heartbeat(void) {
	GPIO_PORTF_DATA_R ^= GPIO_PIN_1;
}

void _____debug_blue(void) {
	GPIO_PORTF_DATA_R ^= GPIO_PIN_2;
}
