#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "FIFO.h"
#include "Timer0A.h"
#include "debug.h"

#define synchronous

void periodic_task(void);

AddIndexFifo(DAC, 64, uint16_t, 1, 0)

#define SSI2_BASE    SSI2_CR0_R   // use the fact that CR0 has offset 0x00
#define PB457   (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7)

void DAC_Init(uint32_t sampling_rate){
  //***for PB
  SYSCTL_RCGCSSI_R  |= SYSCTL_RCGCSSI_R2;       // activate SSI2
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;      // activate port B
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0){};// B CLK ready?

  GPIO_PORTB_AFSEL_R |= PB457;       // enable alt funct on PB4,5,7
  GPIO_PORTB_DEN_R   |= PB457;       // configure PB4,5,7 as SSI
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R
		  & ~(GPIO_PCTL_PB4_M | GPIO_PCTL_PB5_M | GPIO_PCTL_PB7_M))
		  | GPIO_PCTL_PB4_SSI2CLK | GPIO_PCTL_PB5_SSI2FSS | GPIO_PCTL_PB7_SSI2TX;
  GPIO_PORTB_AMSEL_R &= ~PB457;      // disable analog functionality on PB4,5,7

//  SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
//		  SSI_MODE_MASTER, 2000000, 16);
//
//  SSIEnable(SSI2_BASE);


  SSI2_CR1_R = 0;                  // disable SSI, master mode
  SSI2_CPSR_R = 0x02;              // 40 MHz SSIClk
  // SCR = 0, SPH = 0, SPO = 1, Freescale, DSS = 16-bit data
  SSI2_CR0_R &= ~(SSI_CR0_SCR_M | SSI_CR0_SPH | SSI_CR0_FRF_M);
  SSI2_CR0_R |= SSI_CR0_SPO | SSI_CR0_FRF_MOTO | SSI2_CR0_R | SSI_CR0_DSS_16;
  SSI2_DR_R = 0;
  SSI2_CR1_R |= SSI_CR1_SSE;       // enable SSI2

  Timer0A_Init(periodic_task, sampling_rate); // period here shoulld match the sampling rate
}

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t sample) {
	while((SSI2_SR_R & SSI_SR_TNF)==0);  // SSI Transmit FIFO Not Full
	SSI2_DR_R = sample;                  // data out, no reply
}

#if defined(synchronous)
void DAC_Put(uint16_t sample) {
	if(DACFifo_Put(sample) == 0) {
		// _____debug_heartbeat();
		while(DACFifo_Put(sample) == 0);
	}
}

void periodic_task(void) {
	static uint16_t sample;
	if(DACFifo_Get(&sample) == 0) {
		_____debug_blue();
		sample = 0;
	}
	while((SSI2_SR_R & SSI_SR_TNF)==0);  // SSI Transmit FIFO Not Full
	SSI2_DR_R = sample;                  // data out, no reply
}
#endif
