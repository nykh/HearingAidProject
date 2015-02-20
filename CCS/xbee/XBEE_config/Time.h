// Time.h
// Initialize SysTick and set up related periodic interrupt handler.
// The system runs in 12MHz frequency
// Yen-Kai Huang
// 2013/2/8

#ifndef __TIME_H__
#define __TIME_H__

#define Time_Default_Period   0

#define Time_Bus_Frequency    50000000
#define Time_1ms			        Time_Bus_Frequency/1000
#define Time_10ms             Time_1ms*10
#define Time_100ms            Time_1ms*100
#define Time_1SEC             Time_Bus_Frequency

//****************** Time_Init ***********************
//************* Time_Init_Initerrupt *****************
//! Initialize SysTick or Interrupt
//! The interrupt will run at every period time
//! \input period determines the period of interrrupt
//!        periodic task is the task to be performed by periodic interrupt
//! Default period is 1 sec.
//****************************************************
void Time_Init(void);
void Time_Init_Interrupt(unsigned long period);

//****************** Time_Wait ***********************
//! Wait for delay cycles
//!
//! \input delay is the number of cycle to wait for
//****************************************************
void Time_Wait(unsigned long delay);

//**************** Time_Wait10ms *********************
//! Wait for delay * 10ms
//!
//! \input delay is the number of 10ms to wait for
//****************************************************
void Time_Wait10ms(unsigned long delay);

#endif
