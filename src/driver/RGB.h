#ifndef _RGB_H_
#define _RGB_H_

#include "def.h"

#define LED_DDR     DDRA
#define LED_PORT    PORTA

#define RED_PIN    1
#define GREEN_PIN  2
#define BLUE_PIN   3

typedef enum {
    RED,
    GREEN,
    BLUE,
} RGB_Color;

typedef struct {
    volatile uint8_t *port;
    uint8_t pin;
} LED;

void RGBInit(void);
void RGBOn(RGB_Color color);
void RGBOff(RGB_Color color);
void RGBOffAll(void);

#endif