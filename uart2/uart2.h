#ifndef UART2__H__
#define UART2__H__

#include <xc.h> // processor SFR definitions
#include <sys/attribs.h> // __ISR macro

#include "NU32DIP.h"

void UART2_Startup();
void WriteUART2(const char * string);
int get_uart2_flag();
void set_uart2_flag();
int get_uart2_value();

#endif // UART2__H__
