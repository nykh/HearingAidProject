// XBEE.c
// Initializes UART1 to interface a XBee receiver.

#ifndef __XBEE_H__
#define __XBEE_H__

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

void XBEE_Init();
void XBEE_configure(unsigned char destination, unsigned char myaddr);
void XBee_CreateTxFrame(char* data);
void XBee_SendTxFrame(void);
unsigned char XBee_TxStatus(void);
unsigned char XBEE_ReceiveRxFrame(char *buf);
void XBEE_SendAcknoledgeFrame(unsigned char acknoledge);

#endif // __XBEE_H__
