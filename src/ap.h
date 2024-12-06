#ifndef _AP_H_
#define _AP_H_

#include "time.h"
#include "btn.h"
#include "uart1.h"
#include "buzz.h"
#include "stepMotor.h"
#include "RGB.h"
#include "sensor.h"
#include "ultrasonic_int.h"

// 문 상태
typedef enum {
    DOOR_CLOSED,     // 문이 닫힌 상태
    DOOR_OPENING,    // 문이 열리는 중
    DOOR_OPENED,     // 문이 열린 상태
    DOOR_CLOSING     // 문이 닫히는 중
} DoorState;

// 알람 모드
typedef enum {
    ALARM_NONE,      // 알람 없음
    ALARM_OPENING,   // 열림 알람
    ALARM_CLOSING,   // 닫힘 알람
    ALARM_PARKING    // 주차 완료 알람
} AlarmMode;

// 시스템 시퀀스 상태
typedef enum {
    SEQ_WAITING_EXTERNAL,    // 외부 버튼 대기 상태
    SEQ_ENTERING,           // 진입 중 상태
    SEQ_INSIDE_WAITING,     // 내부 대기 상태
    SEQ_EXITING            // 퇴출 중 상태
} SequenceState;

// 알람 제어 구조체
typedef struct {
    uint32_t startTime;      // 알람 시작 시간
    uint32_t lastLedToggle;  // 마지막 LED 토글 시간
    uint8_t isActive;        // 알람 활성화 상태
    uint8_t ledState;        // LED 상태
    AlarmMode mode;          // 현재 알람 모드
} AlarmControl;

// 시스템 설정값
typedef struct {
    uint32_t alarmDuration;      // 알람 지속 시간
    uint32_t ledBlinkInterval;   // LED 깜빡임 간격
    uint8_t buzzerDuty;         // 일반 부저 듀티비
    uint8_t parkingBuzzerDuty;  // 주차 완료 부저 듀티비
    uint16_t motorSteps;        // 모터 스텝 수
    uint8_t motorSpeed;         // 모터 속도
    uint32_t buttonLongPressTime; // 버튼 long press 시간
    uint32_t parkingBuzzerTime;  // 주차 완료 부저 시간
    uint32_t insideWaitTime;     // 내부 대기 시간
} SystemConfig;

// 시스템 상태 구조체
typedef struct {
    DoorState doorState;        // 문 상태
    AlarmControl alarmControl;  // 알람 제어
    MotorStatus motorStatus;    // 모터 상태
    ButtonState buttonStatus;   // 버튼 상태
    SequenceState seqState;     // 시퀀스 상태
    uint32_t buttonPressTime;   // 버튼 누름 시작 시간
    uint32_t insideTimer;       // 내부 체류 시간 타이머
} SystemStatus;

// 함수 선언
void apInit(void);   // 시스템 초기화
void apMain(void);   // 메인 루프

#endif