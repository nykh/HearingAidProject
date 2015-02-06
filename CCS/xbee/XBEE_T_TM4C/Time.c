// Time.c
// Initialize SysTick and set up related periodic interrupt handler.
// The system runs in 12MHz frequency
// Yen-Kai Huang
// 2013/2/10

#include "Time.h"
#include "inc/tm4c123gh6pm.h"

#define NVIC_SYS_PRI3_SCPRI     0x20000000  // Priority 1

void DisableInterrupts(void);
void EnableInterrupts(void);
void StartCritical(void);
void EndCritical(void);
void WaitForInterrupt(void);

void Time_Init(void){
	// Disable SysTick during setup
  NVIC_ST_CTRL_R &=~NVIC_ST_CTRL_ENABLE;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC + NVIC_ST_CTRL_ENABLE;
}

void Time_Init_Interrupt(unsigned long period){
  // Disable SysTick during setup
  NVIC_ST_CTRL_R &=~NVIC_ST_CTRL_ENABLE;
  if(period != Time_Default_Period){
    NVIC_ST_RELOAD_R = period;
	}else {NVIC_ST_RELOAD_R=Time_100ms;}   // Periodic interrupt every 0.1 sec.
	
  NVIC_ST_CURRENT_R = 0;
	
  // Enable SysTick and Interrupt
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC + NVIC_ST_CTRL_INTEN + NVIC_ST_CTRL_ENABLE;
  
  NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_SCPRI; // Periodic interrupt runs at priority 1
}

void Time_Wait(unsigned long delay){
  unsigned long start = NVIC_ST_CURRENT_R;
  volatile unsigned long elapsed;
  do{
    elapsed = (start - NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }while(elapsed <= delay);
}

void Time_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i = 0; i < delay; i++){
    Time_Wait(Time_10ms);
  }
}
  

  
  
  
