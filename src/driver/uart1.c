#include "uart1.h"

//출력 스트림 설정 <stdio.h> 에 있는 표준 입출력임
FILE OUTPUT1 = FDEV_SETUP_STREAM(uart1Transmit, NULL, _FDEV_SETUP_WRITE);

char receiveBuffer1[256];
uint8_t volatile rxFlag1 = 0;

ISR(USART1_RX_vect)     // 수신 인터럽트 핸들러
{
    static uint8_t rxHead = 0; 
    uint8_t rxData = UDR1;

    if(rxData == '\n' || rxData == '\r')
    {
        receiveBuffer1[rxHead] = '\0';
        rxHead = 0;
        rxFlag1 = 1;
    }
    else
    {
        receiveBuffer1[rxHead++] = rxData;
    }

}

void    uart1Init()
{
    //2배속 모드
    UCSR1A |= (1 << U2X1);

    // Baud Rate 설정 (9600bps)
    UBRR1H = 0;          // UBRR0의 상위 8비트
    UBRR1L = 207;        // UBRR0의 하위 8비트

    // 송신(TXEN1), 수신(RXEN1) 활성화
    UCSR1B |= (1 << TXEN1) | (1 << RXEN1);
    // 8비트 데이터,1비트 스탑,비패리티 모드
    UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10);

    //기존의 polling 방식에서 인터럽트 방식으로 추가한 코드 
    UCSR1B |= (1 << RXCIE1); // 수신 인터럽트 활성화
}

// void    uart0Transmit(char data)
// {
//     // 송신 버퍼가 비어질 때까지 대기
//     while (!(UCSR0A & (1 << UDRE0)));
//     // 데이터 전송
//     UDR0 = data;
// }

int uart1Transmit(char c, FILE *stream)
{
    if (c == '\n') { // 개행 문자 처리
        uart1Transmit('\r', stream);
    }

    // 송신 버퍼가 비어질 때까지 대기
    while (!(UCSR1A & (1 << UDRE1)));
    // 데이터 전송
    UDR1 = c;
    return 0; // 항상 성공 반환
}


char uart1Receive()
{
     // 데이터가 수신될 때까지 대기
    while (!(UCSR1A & (1 << RXC1)));
    // 수신된 데이터 반환
    return UDR1;
}