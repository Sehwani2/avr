#ifndef _TIME_H_
#define _TIME_H_

#include "def.h"

extern volatile uint32_t systemTime;

void timeInit(void);
int millis(void);

#endif
