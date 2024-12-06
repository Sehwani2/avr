#ifndef _ULTRASONIC_INT_H_
#define _ULTRASONIC_INT_H_

#include "def.h"

#define TRIGGER_DDR         DDRE
#define ECHO_DDR            DDRE
#define TRIGGER_PORT        PORTE
#define ECHO_PORT           PORTE
#define TRIGGER_PIN         0
#define ECHO_PIN            6

void ultrasonicInit();
void ultrasonicTrigger();
uint16_t ultrasonicDistance();
void initDistanceLED(void);
void updateDistanceLED(void);

#endif // _ULTRASONIC_INT_H_