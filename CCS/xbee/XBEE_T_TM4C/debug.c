// Debug.c
// PG2 is HeartBeat LED
//
// Yen-Kai Huang
// 2013/2/22

#define LED                     (*((volatile unsigned long *)0x40026010))
#define PIN_LED                 0x04
#define GPIO_PORTG_DATA_R       (*((volatile unsigned long *)0x400263FC))
#define GPIO_PORTG_DIR_R        (*((volatile unsigned long *)0x40026400))
#define GPIO_PORTG_AFSEL_R      (*((volatile unsigned long *)0x40026420))
#define GPIO_PORTG_DEN_R        (*((volatile unsigned long *)0x4002651C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOG      0x00000040   // port G Clock Gating Control

void DisableInterrupts(void);
void EnableInterrupts(void);
void StartCritical(void);
void EndCritical(void);
void WaitForInterrupt(void);

//*********************** Debug_Init *******************************
//! Toggle LED
//******************************************************************
void Debug_Init(void) { volatile unsigned long delay;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
  delay = SYSCTL_RCGC2_R;			// Delay needed
  GPIO_PORTG_DIR_R |= PIN_LED;
  GPIO_PORTG_AFSEL_R &=~PIN_LED;
  GPIO_PORTG_DEN_R |= PIN_LED;
}

//********************* Debug_HeartBeat ****************************
//! Toggle LED
//******************************************************************
void Debug_HeartBeat(void) {
  LED = LED^PIN_LED;
}

void Debug_LEDOn(void) {
  LED = PIN_LED;
}

void Debug_LEDOff(void) {
  LED = 0;
}
