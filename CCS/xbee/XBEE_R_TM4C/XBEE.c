// XBEE.c
// Initializes UART1 to interface a XBee receiver.

#include "XBEE.h"
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "FIFO.h"
#include "Time.h"

// XBee characteristics
#define FRAME_START      0x7E

char static acknowledge_frame[7] = {0x7E, 0, 3, 0x89, 0, 0, 0};
#define ID            acknowledge_frame[4]
#define RESULT        acknowledge_frame[5]
#define CHECKSUM      acknowledge_frame[6]
#define BASE_CHKSUM   0x78    // = 0xFF - 0x89

#define SHORT_WAIT() {                            \
	Time_Wait10ms(50); XBEE_WaitForResponse();    \
}                                                 \
														
void EnableInterrupts(void);  // Enable interrupts
	
// copy from hardware RX FIFO to software RX FIFO
// stop when hardware RX FIFO is empty or software RX FIFO is full
void static copyHardwareToSoftware(void){
  char letter;
  while(((UART1_FR_R&UART_FR_RXFE) == 0) && (RxFifo_Size() < (RXFIFOSIZE - 1))){
    letter = UART1_DR_R;
    RxFifo_Put(letter);
  }
}

// copy from software TX FIFO to hardware TX FIFO
// stop when software TX FIFO is empty or hardware TX FIFO is full
void static copySoftwareToHardware(void){
  char letter;
  while(((UART1_FR_R&UART_FR_TXFF) == 0) && (TxFifo_Size() > 0)){
    TxFifo_Get(&letter);
    UART1_DR_R = letter;
  }
}

void static XBEE_WaitForResponse(void){
	char letter;
	while(RxFifo_Get(&letter) == RXFIFOFAIL && letter != 'O');
	while(RxFifo_Get(&letter) == RXFIFOFAIL && letter != 'K');
	while(RxFifo_Get(&letter) == RXFIFOFAIL && letter != CR);
}

// input ASCII character from UART
// spin if RxFifo is empty
unsigned char static XBEE_InChar(void){
	char letter;
	while(RxFifo_Get(&letter) == RXFIFOFAIL);
	return(letter);
}

// output ASCII character to UART
// spin if TxFifo is full
void static XBEE_OutChar(unsigned char data){
	while(TxFifo_Put(data) == TXFIFOFAIL);
	UART1_IM_R &= ~UART_IM_TXIM;          // disable TX FIFO interrupt
	copySoftwareToHardware();
	UART1_IM_R |= UART_IM_TXIM;           // enable TX FIFO interrupt
}

// at least one of three things has happened:
// hardware TX FIFO goes from 3 to 2 or less items
// hardware RX FIFO goes from 1 to 2 or more items
// UART receiver has timed out
void UART1_Handler(void){
	if(UART1_RIS_R&UART_RIS_TXRIS){         // hardware TX FIFO <= 2 items
		UART1_ICR_R = UART_ICR_TXIC;        // acknowledge TX FIFO
	// copy from software TX FIFO to hardware TX FIFO
		copySoftwareToHardware();
		if(TxFifo_Size() == 0){             // software TX FIFO is empty
			UART1_IM_R &= ~UART_IM_TXIM;    // disable TX FIFO interrupt
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
void static XBEE_OutString(char *pt){
	while(*pt){
		XBEE_OutChar(*pt);
		pt++;
	}
	XBEE_OutChar(CR);
}


void XBEE_Init(unsigned char dest){
	unsigned char i;
	const char convert[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char dest_cmd[7] = "ATDL00";
	
	// UART initialization
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port A
	RxFifo_Init();                        // initialize empty FIFOs
	TxFifo_Init();
	UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
	UART1_IBRD_R = 325;                   // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
	UART1_FBRD_R = 34;                    // FBRD = int(0.1267 * 64 + 0.5) = 8
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

	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;  // config B1-0 as UART
	GPIO_PORTB_AMSEL_R &= ~0x03;                                    // disable analog function on B1-0

	// TODO: double check if it's the right interrupt
	// UART1=priority 2
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFF00FFFF)|0x00400000; // bits 23-21
	NVIC_EN0_R |= (1<<6);          // enable interrupt 6 in NVIC

	
	// XBee Initialization
	// calculate and store destination address
	dest_cmd[4] = convert[dest >> 4];
	dest_cmd[5] = convert[(dest & 0x0F)];
	
	EnableInterrupts();

	// X, wait 1.1s, +++, wait 1.1s, WFR
	XBEE_OutChar('X');
	Time_Wait10ms(150);
	for(i=3; i != 0; --i){
		XBEE_OutChar('+');
	}
	Time_Wait10ms(150);
	XBEE_WaitForResponse();
	// Set Destination, wait 20ms, WFR
	XBEE_OutString(dest_cmd);
	SHORT_WAIT();
	// Sets destination high addr, wait 20 ms, WFR
	XBEE_OutString("ATDH0");
	SHORT_WAIT();
	// Sets my address, wait 20 ms, WFR
	XBEE_OutString("ATMY" MYADDR);
	SHORT_WAIT();
	// API 0, wait 20 ms, WFR
	XBEE_OutString("ATAP1");
	SHORT_WAIT();
	//Ends command mode, wait 20 ms, WFR
	XBEE_OutString("ATCN");
	SHORT_WAIT();
}

// return 0 if successful transmission; 1 if the checksum is incorrect
unsigned char XBEE_ReceiveRxFrame(char *data){
	char character;
	unsigned short length;
	unsigned char sum = 0;
	unsigned short i;
	
	// Header
	while(XBEE_InChar() != FRAME_START); // Wait until a proper head start

							  // length
	length = (XBEE_InChar())<<8;
	length += (XBEE_InChar()) - 4;

	// API, ID, Destination information are ignored
	for(i=4; i != 0; --i) {
		sum += XBEE_InChar();
	}
	
	character = XBEE_InChar();  // optional 0x00 does not affect sum
	length -= 1;
	if(character != 0x00){
		*data = character;
		++data;
		sum += character;
	}
	
	while(length > 0){          // data
		character = XBEE_InChar();
		sum += character;
		--length;

		*data = character;
		++data;
	}
								// Checksum
	if(sum + XBEE_InChar() != 0xFF){
		*data = 'X';
		++data;
	}
	
	*data = 0;                  // null terminate
	return 1;
}

void XBEE_SendAcknoledgeFrame(unsigned char acknoledge){
	static char id = 0x01;
	unsigned char i;
	ID = id;
	RESULT = acknoledge;
	CHECKSUM = BASE_CHKSUM - id - acknoledge;

	for(i = 0; i < 7; i++){
		XBEE_OutChar(acknowledge_frame[i]);
	}
}
