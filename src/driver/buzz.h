#ifndef _BUZZ_H_
#define _BUZZ_H_

#include "def.h"

// 부저 관련 설정
#define BUZZER_PIN  PB7         // 부저 연결 핀 (PORTB7)
#define BUZZER_DDR  DDRB        // 부저 데이터 방향 레지스터
#define BUZZER_PORT PORTB       // 부저 포트

// 함수 선언
void buzzInit(void);
void buzzRun(uint8_t duty);     // 부저 동작 (듀티비 설정)
void buzzStop(void);

#endif
                                                                                    