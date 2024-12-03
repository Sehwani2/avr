#ifndef _LED_H_
#define _LED_H_

#include "def.h"

#define LED_DDR     DDRF
#define LED_PORT    PORTF

typedef struct LED
{
    volatile uint8_t *port;
    uint8_t          pin;
}LED;



void ledInit();
void ledOn();
void ledOff();

#endif //_LED_H