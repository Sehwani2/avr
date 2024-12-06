#include "btn.h"
#include "time.h"

// 전역 변수 정의
volatile uint8_t g_buttonLongPressFlag = 0;   // 외부 버튼 long press flag

volatile uint32_t g_interrupt0Time = 0;       // INT0 인터럽트 발생 시간
volatile uint32_t g_interrupt1Time = 0;       // INT1 인터럽트 발생 시간
volatile uint32_t g_interrupt2Time = 0;       // INT2 인터럽트 발생 시간
volatile uint32_t g_interrupt3Time = 0;       // INT3 인터럽트 발생 시간
volatile uint32_t g_interrupt4Time = 0;       // INT4 인터럽트 발생 시간
volatile uint32_t g_interrupt5Time = 0;       // INT5 인터럽트 발생 시간


volatile uint8_t g_button0Pressed = 0;        // 버튼0 눌림 상태
volatile uint8_t g_button1Pressed = 0;        // 버튼1 눌림 상태
volatile uint8_t g_button2Pressed = 0;        // 버튼2 눌림 상태
volatile uint8_t g_button3Pressed = 0;        // 버튼3 눌림 상태
volatile uint8_t g_button4Pressed = 0;        // 버튼4 눌림 상태
volatile uint8_t g_button5Pressed = 0;        // 버튼5 눌림 상태



// 버튼 초기화 함수
void buttonInit(BTN* button, volatile uint8_t* ddr, volatile uint8_t* pin,
               volatile uint8_t* port, uint8_t pinNumber)
{
    button->ddr = ddr;
    button->pin = pin;
    button->port = port;
    button->btnPin = pinNumber;
    
    // 입력 모드로 설정 및 풀업 저항 활성화
    *button->ddr &= ~(1 << button->btnPin);
    *button->port |= (1 << button->btnPin);
}

void INT0_Init(void) {
    DDRD &= ~(1 << PD0);
    PORTD |= (1 << PD0);
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);
}

void INT1_Init(void) {
    DDRD &= ~(1 << PD1);
    PORTD |= (1 << PD1);
    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);
    EIMSK |= (1 << INT1);
}

void INT2_Init(void) {
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);
    EICRA |= (1 << ISC21);
    EICRA &= ~(1 << ISC20);
    EIMSK |= (1 << INT2);
}

void INT3_Init(void) {
    DDRD &= ~(1 << PD3);
    PORTD |= (1 << PD3);
    EICRA |= (1 << ISC31);
    EICRA &= ~(1 << ISC30);
    EIMSK |= (1 << INT3);
}

void INT4_Init(void) {
    DDRE &= ~(1 << PE4);
    PORTE |= (1 << PE4);
    EICRB |= (1 << ISC41);
    EICRB &= ~(1 << ISC40);
    EIMSK |= (1 << INT4);
}

void INT5_Init(void) {
    DDRE &= ~(1 << PE5);
    PORTE |= (1 << PE5);
    EICRB |= (1 << ISC51);
    EICRB &= ~(1 << ISC50);
    EIMSK |= (1 << INT5);
}

ISR(INT0_vect) {
    uint32_t currentTime = millis();
    if (currentTime - g_interrupt0Time >= DEBOUNCE_TIME) {
        g_interrupt0Time = currentTime;
        g_button0Pressed = 1;
    }
}

ISR(INT1_vect) {
    uint32_t currentTime = millis();
    if (currentTime - g_interrupt1Time >= DEBOUNCE_TIME) {
        g_interrupt1Time = currentTime;
        g_button1Pressed = 1;
    }
}

ISR(INT2_vect) {
    uint32_t currentTime = millis();
    if (currentTime - g_interrupt2Time >= DEBOUNCE_TIME) {
        g_interrupt2Time = currentTime;
        g_button2Pressed = 1;
    }
}

ISR(INT3_vect) {
    uint32_t currentTime = millis();
    if (currentTime - g_interrupt3Time >= DEBOUNCE_TIME) {
        g_interrupt3Time = currentTime;
        g_button3Pressed = 1;
    }
}

ISR(INT4_vect) {
    uint32_t currentTime = millis();
    if (currentTime - g_interrupt4Time >= DEBOUNCE_TIME) {
        g_interrupt4Time = currentTime;
        g_button4Pressed = 1;
    }
}

ISR(INT5_vect) {
    uint32_t currentTime = millis();
    if (currentTime - g_interrupt5Time >= DEBOUNCE_TIME) {
        g_interrupt5Time = currentTime;
        g_button5Pressed = 1;
    }
}

// 버튼이 눌��는지 확인하는 함수
uint8_t isButtonPressed(const BTN* btn) {
    return !(*btn->pin & (1 << btn->btnPin));
}
