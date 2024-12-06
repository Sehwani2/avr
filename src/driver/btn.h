#ifndef _BTN_H_
#define _BTN_H_

#include "def.h"

// 버튼 관련 포트 및 설정값 정의
#define BUTTON_DDR      DDRD
#define BUTTON_PIN      PIND
#define BUTTON_PORT     PORTD

#define LONG_PRESS_TIME 3000
#define DEBOUNCE_TIME   50

// 버튼 상태 열거형
typedef enum {
    BUTTON_IDLE,
    BUTTON_PRESSED,
    BUTTON_RELEASED
} ButtonState;

// 버튼 구조체
typedef struct BTN {
    volatile uint8_t *ddr;
    volatile uint8_t *pin;
    volatile uint8_t *port;
    uint8_t btnPin;
} BTN;

// 전역 변수 선언
extern volatile uint8_t g_buttonLongPressFlag;

extern volatile uint32_t g_interrupt0Time;
extern volatile uint32_t g_interrupt1Time;
extern volatile uint32_t g_interrupt2Time;
extern volatile uint32_t g_interrupt3Time;
extern volatile uint32_t g_interrupt4Time;
extern volatile uint32_t g_interrupt5Time;

extern volatile uint8_t g_button0Pressed;
extern volatile uint8_t g_button1Pressed;
extern volatile uint8_t g_button2Pressed;
extern volatile uint8_t g_button3Pressed;
extern volatile uint8_t g_button4Pressed;
extern volatile uint8_t g_button5Pressed;

// 버튼 상태 확인을 위한 매크로
#define IS_BUTTON_PRESSED(btn) (!(*((btn)->pin) & (1 << (btn)->btnPin)))
#define SET_BUTTON_PULLUP(btn) (*((btn)->port) |= (1 << (btn)->btnPin))

// 버튼 상태 확인 및 설정을 위한 함수 선언
uint8_t isButtonPressed(const BTN* btn);
void setButtonPullup(BTN* btn);

// 함수 선언
void buttonInit(BTN* button, volatile uint8_t* ddr, volatile uint8_t* pin, 
               volatile uint8_t* port, uint8_t pinNumber);
void INT0_Init(void);
void INT1_Init(void);
void INT2_Init(void);
void INT3_Init(void);
void INT4_Init(void);
void INT5_Init(void);
uint8_t isButtonPressed(const BTN* btn);
#endif