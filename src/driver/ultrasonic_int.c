#include "ultrasonic_int.h"
#include "time.h"
volatile uint16_t startCount;
volatile uint16_t endCount;
volatile uint16_t usTcnt;


ISR(INT6_vect)
{
    if(PINE & (1<< ECHO_PIN))  // echo핀이 rising 이면
    {
        startCount = TCNT1;         // startCount에 현재의 값 저장

        EICRB &= ~(1 << ISC60);     // falling edge로 변경 
        EICRB |=  (1 << ISC61);     
    }
    else
    {
        endCount = TCNT1;    
        usTcnt  = endCount - startCount;

        EICRB       |=  (1 << ISC61) | (1 << ISC60);    // Rising Edge Interrupt
    }
}

void ultrasonicInit()
{
    TRIGGER_DDR |=  (1 << TRIGGER_PIN);  // 트리거 핀을 출력으로 설정
    ECHO_DDR    &= ~(1 << ECHO_PIN);     // 에코 핀을 입력으로 설정
    ECHO_PORT   |=  (1 << ECHO_PIN);     // 에코 핀 풀업 저항 활성화

    // INT6 인터럽트 설정
    EICRB |= (1 << ISC61) | (1 << ISC60);    // Rising Edge Interrupt
    EIMSK |= (1 << INT6);                     // INT6 인터럽트 활성화

    // 타이머1 설정
    TCCR1B = 0;                               // 타이머1 초기화
    TCCR1B |= (1 << CS11) | (1 << CS10);     // 64분주 (16MHz/64 = 250kHz)
    
    // 변수 초기화
    startCount = 0;
    endCount = 0;
    usTcnt = 0;
}

void ultrasonicTrigger()
{
    PORTE &= ~(1<<TRIGGER_PIN);  //LOW
    _delay_us(1);
    PORTE |= (1<<TRIGGER_PIN);   //High
    _delay_us(10);
    PORTE &= ~(1<<TRIGGER_PIN);  //LOW
}

uint16_t ultrasonicDistance()
{
    // 타이머 값이 0이면 유효하지 않은 측정으로 간주
    if (usTcnt == 0) {
        return 0xFFFF;  // 유효하지 않은 거리 값 반환
    }
    uint16_t distance = (uint16_t)(usTcnt * 0.000004 * 34000) / 2;
    return distance;
}

// LED 제어를 위한 함수 추가
void initDistanceLED(void) {
    DDRE |= (1 << PORTE1) | (1 << PORTE2);    // PE1, PE2를 출력으로 설정
    PORTE &= ~((1 << PORTE1) | (1 << PORTE2)); // LED 초기 상태는 모두 꺼짐
}

void updateDistanceLED(void) {
    static uint32_t lastMeasureTime = 0;
    static uint32_t ledOnTime = 0;
    static bool ledState = false;
    uint32_t currentTime = millis();
    
    // 100ms마다 거리 측정
    if (currentTime - lastMeasureTime >= 100) {
        ultrasonicTrigger();
        uint16_t distance = ultrasonicDistance();
        
        // 유효한 거리 값일 때만 LED 제어
        if (distance != 0xFFFF) {
            if (distance < 30) {
                PORTE |= (1 << PORTE1) | (1 << PORTE2);   // LED1, LED2 ON
                ledState = true;
                ledOnTime = currentTime;   // LED가 켜진 시간 기록
            }
        } else {
            PORTE &= ~((1 << PORTE1) | (1 << PORTE2));  // 유효하지 않은 측정일 경우 LED OFF
        }
        
        lastMeasureTime = currentTime;
    }
    
    // LED가 켜진 상태이고 5초가 지났다면 LED를 끔
    if (ledState && (currentTime - ledOnTime >= 5000)) {
        PORTE &= ~((1 << PORTE1) | (1 << PORTE2));  // LED OFF
        ledState = false;
    }
}
