// Debug.c
// PG2 is HeartBeat LED
//
// Yen-Kai Huang
// 2013/2/22

#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"

#define PIN_LED                 0x08
#define LED                     HWREGBITW(GPIO_PORTF_DATA_R, 3)

void DisableInterrupts(void);
void EnableInterrupts(void);
void StartCritical(void);
void EndCritical(void);
void WaitForInterrupt(void);

//*********************** Debug_Init *******************************
//! Toggle LED
//******************************************************************
void Debug_Init(void) { volatile unsigned long delay;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
  delay = SYSCTL_RCGC2_R;			// Delay needed
  GPIO_PORTF_DIR_R   |= PIN_LED;
  GPIO_PORTF_AFSEL_R &=~PIN_LED;
  GPIO_PORTF_DEN_R   |= PIN_LED;
}

//********************* Debug_HeartBeat ****************************
//! Toggle LED
//******************************************************************
void Debug_HeartBeat(void) {
	LED ^= PIN_LED;
}

void Debug_LEDOn(void) {
	LED = PIN_LED;
}

void Debug_LEDOff(void) {
	LED = 0;
}
