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

void XBEE_OutString(const char* buf);
void XBEE_InString(char* buf);

#endif // __XBEE_H__
