// XBEE.c
// Initializes UART1 to interface a XBee receiver.

#ifndef __XBEE_H__
#define __XBEE_H__

#define MYADDR   "69"

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F


void XBEE_Init(unsigned char dest);
unsigned char XBEE_ReceiveRxFrame(char* data);
void XBEE_SendAcknoledgeFrame(unsigned char acknoledge);

#endif // __XBEE_H__
