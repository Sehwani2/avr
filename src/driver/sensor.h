#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "def.h"

// 핀 정의
#define PIR_SENSOR_PIN    PORTC0             // HC-SR501 PIR 센서 핀
#define LED_PIN           PORTC1             // LED 핀

// 함수 프로토타입
void sensorInit(void);
uint8_t isMotionDetected(void);
void turnOnLED(void);
void turnOffLED(void);
void handleMotionDetection(void);  // 새로운 함수 추가

#endif