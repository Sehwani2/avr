#include "buzz.h"

void buzzInit(void) {
    // 부저 핀을 출력으로 설정
    BUZZER_DDR |= (1 << BUZZER_PIN);
    BUZZER_PORT &= ~(1 << BUZZER_PIN);  // 초기 출력은 LOW
    
    // Timer2 초기 설정
    TCCR2 = (1 << WGM21) | (1 << WGM20);  // Fast PWM 모드
    TCCR2 |= (1 << CS22);                  // 프리스케일러 64
    
    // 초기 상태는 부저 정지
    buzzStop();
}

void buzzStop(void) {
    // PWM 출력 비활성화 (OC2 연결 해제)
    TCCR2 &= ~((1 << COM21) | (1 << COM20));
    OCR2 = 0;     // 비교 레지스터 값 0으로 설정
    
    // 출력 핀을 LOW로 설정
    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

void buzzRun(uint8_t duty) {
    OCR2 = duty;  // 듀티비 설정
    
    // PWM 출력 활성화 (비반전 모드)
    TCCR2 |= (1 << COM21) | (1 << COM20);
}