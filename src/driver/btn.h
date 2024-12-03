#ifndef _BTN_H_
#define _BTN_H_

#include "def.h"

#define BUTTON_DDR      DDRD
#define BUTTON_PIN      PIND
#define BUTTON_PORT     PORTD
#define BUTTON_ON       0
#define BUTTON_OFF      1
#define BUTTON_TOGGLE   2

enum {PUSHED, RELEASED};
enum {NO_ACT, ACT_PUSH, ACT_RELEASED};

typedef struct BTN
{
    volatile uint8_t *ddr;
    volatile uint8_t *pin;
    volatile uint8_t *port;
    uint8_t btnPin;
    uint8_t prevState;
}BTN;

void buttonInit(BTN* button, volatile uint8_t* ddr, volatile uint8_t*pin,volatile uint8_t* port,uint8_t pinNumber);
uint8_t buttonGetState(BTN *button);

#endif