#include "sensor.h"
#include "time.h"

static uint32_t motionStartTime = 0;    // 동작 감지 시작 시간
static uint8_t motionDetected = 0;      // 동작 감지 상태

void sensorInit(void) {
    // PIR 센서 핀 입력 설정
    DDRC &= ~(1 << PIR_SENSOR_PIN);    // PORTA5를 입력으로
    PORTC |= (1 << PIR_SENSOR_PIN);    // 풀업 저항 활성화 (테스트용)

    // LED 핀 출력 설정
    DDRC |= (1 << LED_PIN);            // PORTA4를 출력으로
    PORTC &= ~(1 << LED_PIN);          // LED 초기 상태 꺼짐
}

uint8_t isMotionDetected(void) {
    return (PINC & (1 << PIR_SENSOR_PIN));
}

void turnOnLED(void) {
    PORTC |= (1 << LED_PIN);
}

void turnOffLED(void) {
    PORTC &= ~(1 << LED_PIN);
}

void handleMotionDetection(void) {
    uint32_t currentTime = millis();
    
    if (isMotionDetected()) {
        // 동작이 감지되면 타이머 리셋하고 LED 켜기
        motionStartTime = currentTime;
        motionDetected = 1;
        turnOnLED();
    } 
    else if (motionDetected) {
        // 동작이 멈추고 5초가 지났는지 확인
        if (currentTime - motionStartTime >= 5000) {
            motionDetected = 0;
            turnOffLED();
        }
    }
}                                