#include <stdint.h>
#include "tm4c123gh6pm.h"

void DAC_Init(uint16_t data){
	//***init change to PB 4--clk,5--Fss,7--Tx of SSI2***
	//***for PF
	SYSCTL_RCGCGPIO_R |= 0x20;  // activate port F
  while((SYSCTL_PRGPIO_R&0x20) == 0){};// F CLK ready?	
  GPIO_PORTF_DIR_R |= 0x04;   // make PF2 output (PF2 built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x04;// disable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;   // enable digital I/O on PF2
                              // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF
	//***for PB	
  SYSCTL_RCGCSSI_R |= 0x04;       // activate SSI2
  SYSCTL_RCGCGPIO_R |= 0x02;      // activate port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){};// B CLK ready?
  GPIO_PORTB_AFSEL_R |= 0xB0;     // enable alt funct on PB4,5,7
  GPIO_PORTB_DEN_R |= 0xB0;       // configure PB4,5,7 as SSI
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0x0F00FFFF)+0x20220000;
  GPIO_PORTB_AMSEL_R &= ~0xB0;         // disable analog functionality on PB4,5,7	
		
  SSI2_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI2_CPSR_R = 0x02;             // 40 MHz SSIClk-----40MHz
  SSI2_CR0_R &= ~(0x0000FFB0);    // SCR = 0, SPH = 0, SPO = 1 Freescale
  SSI2_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI2_DR_R = data;               // load 'data' into transmit FIFO
  SSI2_CR1_R |= 0x00000002;       // enable SSI2
/***original init***/
/*
	SYSCTL_RCGCSSI_R |= 0x01;       // activate SSI0
  SYSCTL_RCGCGPIO_R |= 0x01;      // activate port A
  while((SYSCTL_PRGPIO_R&0x01) == 0){};// ready?
  GPIO_PORTA_AFSEL_R |= 0x2C;     // enable alt funct on PA2,3,5
  GPIO_PORTA_DEN_R |= 0x2C;       // configure PA2,3,5 as SSI
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
  GPIO_PORTA_AMSEL_R = 0;         // disable analog functionality on PA
  SSI0_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI0_CPSR_R = 0x02;             // 8 MHz SSIClk 
  SSI0_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 1 Freescale
  SSI0_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI0_DR_R = data;               // load 'data' into transmit FIFO
  SSI0_CR1_R |= 0x00000002;       // enable SSI		
*/
}

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t code){   
  while((SSI2_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI2_DR_R = code; }                // data out, no reply
  
//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: reply is returned
// send the 16-bit code to the SSI, return a reply
uint16_t DAC_Out2(uint16_t code){   uint16_t receive;
  while((SSI2_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI2_DR_R = code;                  // data out
  while((SSI2_SR_R&0x00000004)==0){};// SSI Receive FIFO Not Empty
  receive = SSI2_DR_R;               // acknowledge response
  return receive;
}

