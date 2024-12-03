#ifndef _AP_H
#define _AP_H

#include "def.h"
#include "led.h"
#include "btn.h"
#include "pwm8.h"
#include "pwm16.h"
#include "uart0.h"
#include "uart1.h"
#include "i2c_lcd.h"
#include "ultrasonic.h"

void apInit();
void apMain();

#endif // _AP_H