#ifndef _UART1_H_
#define _UART1_H_

#include "def.h"

void    uart1Init();
int uart1Transmit(char c, FILE *stream);
char    uart1Receive();

#endif // _UART1_H