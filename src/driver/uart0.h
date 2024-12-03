#ifndef _UART0_H_
#define _UART0_H_

#include "def.h"


void uart0Init();
void uart0Transmit(char data);
unsigned uart0Receive(void);
int uart0Transmit_wrapper(char c, FILE *stream);
void uart0Print(const char *str);

#endif // _UART0_H