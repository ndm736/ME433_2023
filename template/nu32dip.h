#ifndef NU32DIP__H__
#define NU32DIP__H__

#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>

#define NU32DIP_SYS_FREQ 48000000ul    // 48 million Hz

void NU32DIP_Startup(void);
void NU32DIP_ReadUART1(char * string, int maxLength);
void NU32DIP_WriteUART1(const char * string);

#define NU32DIP_DESIRED_BAUD 230400    // Baudrate for RS232
#define NU32DIP_GREEN LATBbits.LATB4
#define NU32DIP_YELLOW LATBbits.LATB5
#define NU32DIP_USER PORTAbits.RA4

#endif // NU32DIP__H__