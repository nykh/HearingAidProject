#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.h"

#define PB457   (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7)

void DAC_Init(uint16_t data){
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
		
  SSI2_CR1_R = 0;                  // disable SSI, master mode
  SSI2_CPSR_R = 0x02;              // 40 MHz SSIClk
  // SCR = 0, SPH = 0, SPO = 1, Freescale, DSS = 16-bit data
  SSI2_CR0_R &= ~(SSI_CR0_SCR_M | SSI_CR0_SPH | SSI_CR0_FRF_M);
  SSI2_CR0_R |= SSI_CR0_SPO | SSI_CR0_FRF_MOTO | SSI2_CR0_R | SSI_CR0_DSS_16;
  SSI2_DR_R = data;                // load 'data' into transmit FIFO
  SSI2_CR1_R |= SSI_CR1_SSE;       // enable SSI2
}

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t code) {
  while((SSI2_SR_R&0x00000002)==0);  // SSI Transmit FIFO Not Full
  SSI2_DR_R = code;                  // data out, no reply
}
