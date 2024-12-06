#include "ap.h"

// 외부 버튼들
static BTN extButtons[3];  // 외부 버튼 배열
// 내부 버튼들
static BTN intButtons[3];  // 내부 버튼 배열

// 시스템 설정값 초기화
static const SystemConfig sysConfig = {
    .alarmDuration = 10000,        // 10초 동안 알람 지속
    .ledBlinkInterval = 300,      // LED 깜빡임 간격
    .buzzerDuty = 180,           // 일반 부저  
    .parkingBuzzerDuty = 240,    // 주차 완료 부저  
    .motorSteps = 2100,          // 모터 회전 스텝 수
    .motorSpeed = 1,             // 모터 스텝 간격 (ms)
    .buttonLongPressTime = 3000, // 버튼 long press (3초)
    .parkingBuzzerTime = 1000,   // 주차 완료 부저 시간
    .insideWaitTime = 3000       // 내부 대기 시간 (3초)
};

// 시스템 상태 초기화
static SystemStatus systemStatus = {
    .doorState = DOOR_CLOSED,      
    .alarmControl = {0},           
    .motorStatus = MOTOR_IDLE,     
    .buttonStatus = BUTTON_IDLE,
    .seqState = SEQ_WAITING_EXTERNAL,
    .buttonPressTime = 0,
    .insideTimer = 0
};


// 알람 시작 함수
static void startAlarm(AlarmMode mode) {
    AlarmControl* alarm = &systemStatus.alarmControl;
    alarm->startTime = millis();
    alarm->isActive = 1;
    alarm->mode = mode;
    alarm->ledState = 0;
    alarm->lastLedToggle = millis();
    buzzInit();  // 부저 초기화 추가
    buzzStop();
    RGBOffAll();
}

// LED 상태 업데이트
static void updateLedState(void) {
    uint32_t currentTime = millis();
    AlarmControl* alarm = &systemStatus.alarmControl;
    
    // 먼저 모든 LED 끄기
    RGBOffAll();
    
    if (alarm->isActive) {
        if (currentTime - alarm->lastLedToggle >= sysConfig.ledBlinkInterval) 
        {
            alarm->lastLedToggle = currentTime;
            
            if (!alarm->ledState) {  // LED가 꺼져있을 때만 켜기
                switch (alarm->mode) 
                {
                    case ALARM_OPENING:  // 문이 열릴 때는 빨간색
                    case ALARM_CLOSING:  // 문이 닫힐 때도 빨간색
                        RGBOn(RED);
                        buzzInit();
                        buzzRun(sysConfig.buzzerDuty);
                        break;
                    case ALARM_PARKING:  // 주차 완료 알람
                        buzzInit();
                        buzzRun(sysConfig.parkingBuzzerDuty);
                        break;
                    case ALARM_NONE:     // 알람이 없는 상태
                    default:
                        buzzStop();
                        break;
                }
            }
            alarm->ledState = !alarm->ledState;  // LED 상태 토글
        }
        
        // 알람 종료 처리
        uint32_t alarmDuration = (alarm->mode == ALARM_PARKING) ? 
                                sysConfig.parkingBuzzerTime : sysConfig.alarmDuration;
        
        if (currentTime - alarm->startTime >= alarmDuration) 
        {
            alarm->isActive = 0;
            buzzStop();
        }
    }
    
    // 기본 LED 상태 설정
    if (!alarm->isActive || alarm->ledState == 0) {
        if (systemStatus.doorState == DOOR_CLOSED) {
            RGBOn(BLUE);        // 기본 상태는 파란색
        }
        else if (systemStatus.doorState == DOOR_OPENING || 
                systemStatus.doorState == DOOR_CLOSING) {
            RGBOn(RED);         // 문이 움직일 때는 빨간색
        }
        else if (systemStatus.doorState == DOOR_OPENED) {
            RGBOn(GREEN);       // 문이 열려있을 때는 초록색
        }
    }
}

// 버튼 상태 업데이트
static void updateButtonStatus(void) {
    uint32_t currentTime = millis();
    static uint8_t extBothPressed = 0;
    static uint8_t intBothPressed = 0;
    
    // 외부 버튼 상태 확인
    uint8_t extCurrentlyPressed = isButtonPressed(&extButtons[0]) && isButtonPressed(&extButtons[1]);
    uint8_t intCurrentlyPressed = isButtonPressed(&intButtons[0]) && isButtonPressed(&intButtons[1]);
    
    switch(systemStatus.seqState) {
        case SEQ_WAITING_EXTERNAL:
            if (extCurrentlyPressed && !extBothPressed) {
                systemStatus.buttonPressTime = currentTime;
                extBothPressed = 1;
            }
            else if (extCurrentlyPressed && extBothPressed) {
                if (currentTime - systemStatus.buttonPressTime >= sysConfig.buttonLongPressTime) {
                    motorStart(sysConfig.motorSteps, 1);  // 문 열기
                    systemStatus.doorState = DOOR_OPENING;
                    startAlarm(ALARM_OPENING);
                    systemStatus.seqState = SEQ_ENTERING;
                }
            }
            else {
                extBothPressed = 0;
            }
            break;
            
        case SEQ_ENTERING:
            if (systemStatus.doorState == DOOR_OPENED) {
                if (intCurrentlyPressed && !intBothPressed) {
                    systemStatus.buttonPressTime = currentTime;
                    intBothPressed = 1;
                    systemStatus.seqState = SEQ_INSIDE_WAITING;
                }
            }
            break;
            
        case SEQ_INSIDE_WAITING:
            if (intCurrentlyPressed) {
                if (currentTime - systemStatus.buttonPressTime >= sysConfig.insideWaitTime) {
                    motorStart(sysConfig.motorSteps, 0);  // 문 닫기
                    systemStatus.doorState = DOOR_CLOSING;
                    startAlarm(ALARM_CLOSING);
                    systemStatus.seqState = SEQ_EXITING;
                }
            }
            else {
                intBothPressed = 0;
                systemStatus.buttonPressTime = currentTime;
            }
            break;
            
        case SEQ_EXITING:
            if (!intCurrentlyPressed && systemStatus.doorState == DOOR_CLOSED) {
                motorStart(sysConfig.motorSteps, 1);  // 문 열기
                systemStatus.doorState = DOOR_OPENING;
                startAlarm(ALARM_OPENING);
            }
            else if (extCurrentlyPressed && systemStatus.doorState == DOOR_OPENED) {
                motorStart(sysConfig.motorSteps, 0);  // 문 닫기
                systemStatus.doorState = DOOR_CLOSING;
                startAlarm(ALARM_CLOSING);
                systemStatus.seqState = SEQ_WAITING_EXTERNAL;  // 시퀀스 완료
            }
            break;
    }
    
    // 버튼 상태 초기화
    if (!extCurrentlyPressed) {
        if (PIND & (1 << PD0)) g_button0Pressed = 0;
        if (PIND & (1 << PD1)) g_button1Pressed = 0;
    }
    if (!intCurrentlyPressed) {
        if (PIND & (1 << PD2)) g_button2Pressed = 0;
        if (PIND & (1 << PD3)) g_button3Pressed = 0;
    }
}

// 수동 버튼 처리 함수
static void updateManualButtons(void) {
    uint32_t currentTime = millis();
    static uint32_t lastPressTime = 0;
    
    // 수동 버튼 짧게 누름 처리
    if (isButtonPressed(&extButtons[2]) || isButtonPressed(&intButtons[2])) {
        if (currentTime - lastPressTime >= 200) {  // 디바운스
            if (systemStatus.motorStatus == MOTOR_IDLE) {
                // 문이 닫혀있으면 열기, 열려있으면 닫기
                if (systemStatus.doorState == DOOR_CLOSED) {
                    motorStart(sysConfig.motorSteps, 1);  // 열기
                    systemStatus.doorState = DOOR_OPENING;
                    startAlarm(ALARM_OPENING);
                    // 시퀀스 상태 초기화
                    systemStatus.seqState = SEQ_WAITING_EXTERNAL;
                } else if (systemStatus.doorState == DOOR_OPENED) {
                    motorStart(sysConfig.motorSteps, 0);  // 닫기
                    systemStatus.doorState = DOOR_CLOSING;
                    startAlarm(ALARM_CLOSING);
                    // 시퀀스 상태 초기화
                    systemStatus.seqState = SEQ_WAITING_EXTERNAL;
                }
            }
            lastPressTime = currentTime;
        }
    }
}

void apInit(void)
{
    // 하드웨어 초기화
    motorInit();   
    timeInit();    
    sensorInit();  
    INT0_Init();   
    INT1_Init();   
    INT2_Init();   
    INT3_Init();   
    INT4_Init();   
    INT5_Init();   
    RGBInit();     
    buzzInit();    
    
    // 버튼 초기화
    buttonInit(&extButtons[0], &DDRD, &PIND, &PORTD, PD0);  // INT0
    buttonInit(&extButtons[1], &DDRD, &PIND, &PORTD, PD1);  // INT1
    buttonInit(&intButtons[0], &DDRD, &PIND, &PORTD, PD2);  // INT2
    buttonInit(&intButtons[1], &DDRD, &PIND, &PORTD, PD3);  // INT3
    buttonInit(&extButtons[2], &DDRE, &PINE, &PORTE, PE4);  // INT4로 수정
    buttonInit(&intButtons[2], &DDRE, &PINE, &PORTE, PE5);  // INT5로 수정
    
    initDistanceLED();     // LED 초기화
    ultrasonicInit();      // 초음파 센서 초기화
    
    sei();  // 전역 인터럽트 활성화
}

void apMain(void)
{
    while (1) {
        // 버튼 상태 업데이트
        updateButtonStatus();
        updateManualButtons();
        updateDistanceLED();
        handleMotionDetection();
        
        // 모터 동작 완료 체크
        if (motorStepsRemaining == 1) {
            if (systemStatus.doorState == DOOR_OPENING) {
                systemStatus.doorState = DOOR_OPENED;
                startAlarm(ALARM_PARKING);
            } 
            else if (systemStatus.doorState == DOOR_CLOSING) {
                systemStatus.doorState = DOOR_CLOSED;
                startAlarm(ALARM_PARKING);
            }
        }
        
        updateLedState();
        motorUpdate();
    }
}

