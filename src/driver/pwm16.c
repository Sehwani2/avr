#include "pwm16.h"

void pwm16Init()
{
    DDRE |= (1 << PORTE3);     // OC3A 핀(PORTE3)을 출력으로 설정

    // Fast PWM 모드, TOP 값 = ICR3
    TCCR3A |= (1<<COM3A1) | (1<<WGM31);
    TCCR3B |= (1<<WGM33) | (1<<WGM32) | (1<<CS31) | (1<<CS30);

    ICR3 = 4999; // 50Hz PWM 주파수 설정 (TOP 값)   
}

void pwm16Run(uint8_t duty)
{
   
}
