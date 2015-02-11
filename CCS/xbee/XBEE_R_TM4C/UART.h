// UART.c
// Implements a UART channel to communicate with PC

#ifndef __UART__H__
#define __UART__H__

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F


void UART_Init(void);
void UART_OutString(char *pt);
void UART_InString(char *bufPt, unsigned short max);
void UART_NewLine(void);

#endif //__UART__H__
