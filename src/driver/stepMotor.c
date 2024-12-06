#include "stepMotor.h"
#include "time.h"
#include "ap.h"
volatile uint16_t motorStepsRemaining = 0; // 남은 스텝 수
volatile uint8_t motorStepIndex = 0;       // 현재 스텝 인덱스
volatile uint8_t motorDirection = 1;       // 1: 시계 방향, 0: 반시계 방향
volatile uint32_t lastStepTime = 0;        // 마지막 스텝 변경 시간

void motorInit(void)
{
    // 모터 제어 핀을 출력으로 설정
    DDRB |= (1 << MOTOR_PIN1) | (1 << MOTOR_PIN2) | (1 << MOTOR_PIN3) | (1 << MOTOR_PIN4);
}

void motorStep(uint8_t step)
{
    // 스텝별로 핀 설정
    switch (step) {
        case 0:
            PORTB = (1 << MOTOR_PIN1);
            break;
        case 1:
            PORTB = (1 << MOTOR_PIN2);
            break;
        case 2:
            PORTB = (1 << MOTOR_PIN3);
            break;
        case 3:
            PORTB = (1 << MOTOR_PIN4);
            break;
        default:
            PORTB = 0; // 모든 핀 OFF
            break;
    }
}

void motorStart(uint16_t steps, uint8_t clockwise)
{
    motorStepsRemaining = steps;          // 설정된 스텝 수
    motorDirection = clockwise ? 1 : 0;  // 방향 설정
    motorStepIndex = 0;                   // 시작 인덱스 설정
    lastStepTime = millis();              // 시작 시간 초기화
}

void motorUpdate(void)
{
    if (motorStepsRemaining == 0) 
    {
        return; // 작업 완료 상태
    }

    // 10ms마다 스텝 업데이트
    if (millis() - lastStepTime >= 10)
    {
        motorStep(motorStepIndex);  // 현재 스텝 실행
        lastStepTime = millis();    // 시간 갱신

        // 스텝 인덱스 업데이트
        if (motorDirection) {
            motorStepIndex = (motorStepIndex + 1) % 4; // 시계 방향
        } else {
            motorStepIndex = (motorStepIndex + 3) % 4; // 반시계 방향
        }

        motorStepsRemaining--; // 남은 스텝 감소
    }
}
void motorStop(void) {
    motorStepsRemaining = 0;
}