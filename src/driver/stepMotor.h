#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include "def.h"

// 모터 상태 열거형 추가
typedef enum {
    MOTOR_IDLE,
    MOTOR_RUNNING,
    MOTOR_STOPPED
} MotorStatus;

// 스텝 모터 제어 핀 정의
#define MOTOR_PIN1  PORTB0
#define MOTOR_PIN2  PORTB1
#define MOTOR_PIN3  PORTB2
#define MOTOR_PIN4  PORTB3

// 모터 상태 구조체
typedef struct {
    uint16_t stepsRemaining;    // 남은 스텝 수
    uint8_t currentStep;        // 현재 스텝 위치
    uint8_t direction;          // 회전 방향 (1: 시계방향, 0: 반시계방향)
    uint32_t lastStepTime;      // 마지막 스텝 시간
} MotorControl;

void motorInit(void);
void motorStep(uint8_t step);
void motorStart(uint16_t steps, uint8_t clockwise);
void motorUpdate(void);
void motorStop(void);  // 모터 정지 함수 

extern volatile uint16_t motorStepsRemaining;
extern volatile uint8_t motorDirection;
#endif
