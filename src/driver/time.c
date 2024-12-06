#include "time.h"

volatile uint32_t systemTime = 0;

void timeInit(void) {
    // Timer0 설정
    TCCR0 = (1 << CS01) | (1 << CS00);  // 프리스케일러 64
    TIMSK = (1 << TOIE0);               // 오버플로우 인터럽트 활성화
    TCNT0 = 0;                          // 타이머 카운터 초기화
}

ISR(TIMER0_OVF_vect)
{
    systemTime++;  // 1ms마다 systemTime 증가
}

int millis(void)
{
    return systemTime;  // 시스템 경과 시간 반환
}
