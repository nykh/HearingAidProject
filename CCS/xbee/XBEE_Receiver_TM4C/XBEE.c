// Initializes UART1 to interface a XBee receiver.
#include "XBEE.h"
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "FIFO.h"
#include "Time.h"

#define TXFIFOSIZE  16
#define RXFIFOSIZE  8
#define FIFOSUCCESS 1         // return value on success
#define FIFOFAIL    0         // return value on failure
                              // create index implementation FIFO (see FIFO.h)
AddIndexFifo(XBEERx, RXFIFOSIZE, char, FIFOSUCCESS, FIFOFAIL)
AddIndexFifo(XBEETx, TXFIFOSIZE, char, FIFOSUCCESS, FIFOFAIL)

void EnableInterrupts(void);  // Enable interrupts
#define SHORT_WAIT() \
	do{ Time_Wait10ms(50); XBEE_WaitForResponse(); }  \
	while(0)                                          \

// copy from hardware RX FIFO to software RX FIFO
// stop when hardware RX FIFO is empty or software RX FIFO is full
void static copyHardwareToSoftware(void){
  char letter;
  while(((UART1_FR_R&UART_FR_RXFE) == 0) && (XBEERxFifo_Size() < (RXFIFOSIZE - 1))){
    letter = UART1_DR_R;
    XBEERxFifo_Put(letter);
  }
}

// copy from software TX FIFO to hardware TX FIFO
// stop when software TX FIFO is empty or hardware TX FIFO is full
void static copySoftwareToHardware(void){
  char letter;
  while(((UART1_FR_R&UART_FR_TXFF) == 0) && (XBEETxFifo_Size() > 0)){
	XBEETxFifo_Get(&letter);
    UART1_DR_R = letter;
  }
}

// input ASCII character from UART
// spin if RxFifo is empty
unsigned char static XBEE_InChar(void){
  char letter;
  while(XBEERxFifo_Get(&letter) == FIFOFAIL){};
  return(letter);
}

// output ASCII character to UART
// spin if TxFifo is full
void static XBEE_OutChar(unsigned char data){
  while(XBEETxFifo_Put(data) == FIFOFAIL){};
  UART1_IM_R &= ~UART_IM_TXIM;          // disable TX FIFO interrupt
  copySoftwareToHardware();
  UART1_IM_R |= UART_IM_TXIM;           // enable TX FIFO interrupt
}

// at least one of three things has happened:
// hardware TX FIFO goes from 3 to 2 or less items
// hardware RX FIFO goes from 1 to 2 or more items
// UART receiver has timed out
void UART1_Handler(void){

  if(UART1_RIS_R&UART_RIS_TXRIS){       // hardware TX FIFO <= 2 items
    UART1_ICR_R = UART_ICR_TXIC;        // acknowledge TX FIFO
    // copy from software TX FIFO to hardware TX FIFO
    copySoftwareToHardware();
    if(XBEETxFifo_Size() == 0){             // software TX FIFO is empty
      UART1_IM_R &= ~UART_IM_TXIM;      // disable TX FIFO interrupt
    }
  }
  if(UART1_RIS_R&UART_RIS_RXRIS){       // hardware RX FIFO >= 2 items
    UART1_ICR_R = UART_ICR_RXIC;        // acknowledge RX FIFO
    // copy from hardware RX FIFO to software RX FIFO
    copyHardwareToSoftware();
  }
  if(UART1_RIS_R&UART_RIS_RTRIS){       // receiver timed out
    UART1_ICR_R = UART_ICR_RTIC;        // acknowledge receiver time out
    // copy from hardware RX FIFO to software RX FIFO
    copyHardwareToSoftware();
  }
}


//------------XBEE_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void XBEE_OutString(const char *buf){
  while(*buf){
    XBEE_OutChar(*buf++);
  }
  XBEE_OutChar('\r');
}

void XBEE_InString(char *buf) {
	unsigned char c;
	while((c = XBEE_InChar()) != '\r')
		*buf++ = c;
	*buf = '\0';
}


void static XBEE_WaitForXBeeOK(void) {
	char letter;
	while(XBEERxFifo_Get(&letter) == FIFOFAIL && letter != 'O');
	while(XBEERxFifo_Get(&letter) == FIFOFAIL && letter != 'K');
	while(XBEERxFifo_Get(&letter) == FIFOFAIL && letter != CR);
}

void static XBEE_command(const char *cmd) {
	XBEE_OutChar('A');
	XBEE_OutChar('T');
	XBEE_OutString(cmd);
	Time_Wait10ms(50);
	XBEE_WaitForXBeeOK();
}

void static XBEE_enter_command_mode(void) {
	// X, wait 1.1s, +++, wait 1.1s, WFR
	XBEE_OutChar('X');
	Time_Wait10ms(150);
	XBEE_OutChar('+'); XBEE_OutChar('+'); XBEE_OutChar('+');
	Time_Wait10ms(150);
	XBEE_WaitForXBeeOK();
}

void XBEE_Init(void){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; // activate UART1
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; // activate port B
	XBEERxFifo_Init();                        // initialize empty FIFOs
	XBEETxFifo_Init();
	UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
	UART1_IBRD_R = 27;                   // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
	UART1_FBRD_R =8;                    // FBRD = int(0.1267 * 64 + 0.5) = 8
										// 8 bit word length (no parity bits, one stop bit, FIFOs)
	UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
	UART1_IFLS_R &= ~0x3F;                // clear TX and RX interrupt FIFO level fields
										// configure interrupt for TX FIFO <= 1/8 full
										// configure interrupt for RX FIFO >= 1/8 full
	UART1_IFLS_R += (UART_IFLS_TX1_8|UART_IFLS_RX1_8);
										// enable TX and RX FIFO interrupts and RX time-out interrupt
	UART1_IM_R |= (UART_IM_RXIM|UART_IM_TXIM|UART_IM_RTIM);
	UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
	GPIO_PORTB_AFSEL_R |= 0x03;           // enable alt funct on PB0-1
	GPIO_PORTB_DEN_R |= 0x03;             // enable digital I/O on PB0-1
										// UART1=priority 2

	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;  // config B1-0 as UART
	GPIO_PORTB_AMSEL_R &= ~0x03;                                    // disable analog function on B1-0

	NVIC_PRI1_R = (NVIC_PRI1_R&0xFF00FFFF)|0x00400000; // bits 23-21
	NVIC_EN0_R |= (1<<6);          // enable interrupt 6 in NVIC
}

void XBEE_configure(unsigned char destination, unsigned char myaddr) {
    char destination_low[5] = "DL00";
    char my_address[5]      = "MY00";

    // FIXME: bug when nibble is 0xA-0xF
	destination_low[2] += destination >> 4;
	destination_low[3] += (destination & 0xF);
	my_address[2] += myaddr >> 4;
	my_address[3] += (myaddr & 0xF);

	XBEE_enter_command_mode();
	XBEE_command(destination_low); // DLxx
	XBEE_command("DH0");
	XBEE_command(my_address);      // MYxx
	XBEE_command("AP0");
	XBEE_command("CN");
}
