#include "uart0.h"



char rxBuff[100] = {0}; // 수신 버퍼
volatile uint8_t rxFlag = 0;



ISR(USART0_RX_vect) // 수신 인터럽트 핸들러
{
    static uint8_t rxHead = 0; // 수신된 데이터의 인덱스
    uint8_t rxData = UDR0;
    if (rxData == '\n' || rxData == '\r') // 개행이나 리턴문자이면
    {
        rxBuff[rxHead] = '\0'; // 수신된 문자열 마지막에 널문자 추가
        rxHead = 0;            // 인덱스 초기화
        rxFlag = 1;            // 문자 받았다고 깃발 세움
    }
    else if(rxHead < sizeof(rxBuff) - 1)
    {
        rxBuff[rxHead++] = rxData; // 버퍼에 계속 데이터 추가
        //rxHead++;                // 인덱스 증가
    }
}

void uart0Init()
{
    // 통신속도 9600 bps
    UBRR0H = 0;
    UBRR0L = 0xcf; // 207;

    // 2배속 모드
    UCSR0A |= (1 << U2X0);

    // 비동기, 8비트, 패리티없음, 1비트 stop
    // UCSR0C|= () -> 안해도 기본값으로 가능
    UCSR0B |= (1 << RXEN0); // 수신 가능
    UCSR0B |= (1 << TXEN0); // 송신 가능

    // 기존의 polling 방식에서 인터럽트 방식으로 추가한 코드
    UCSR0B |= (1 << RXCIE0); // 수신인터럽트 인에이블

    sei();
}

void uart0Transmit(char data)
{
    while (!(UCSR0A & (1 << UDRE0))); // 송신 가능 대기, UDR이 비어 있는지?

    UDR0 = data;
}

int uart0Transmit_wrapper(char c, FILE *stream)
{
    uart0Transmit(c);
    return 0;
}


unsigned uart0Receive(void)
{
    while (!(UCSR0A & (1 << RXC0))); // 수신 대기 !!!

    return UDR0;
}

void uart0Print(const char *str)
{
    while (*str)
    {
        uart0Transmit(*str++);
    }    
}