#include "ultrasonic.h"




void timerInit()
{
    
    //트리거핀
    DDRD |= (1<<PORTD6);    

    //에코핀
    DDRD &= ~(1<<PORTD7);

    //1024분주 세팅
    TCCR1B |= (1<<CS12) | (1<<CS10);

}


void triggerPin()
{
    PORTD &= ~(1<<PORTD6);  //LOW만들기
    _delay_us(1);
    PORTD |= (1<<PORTD6);   //High만들기
    _delay_us(10);
    PORTD &= ~(1<<PORTD6);  //LOW만들기
}


uint8_t meanDistance()
{
    //타이머 카운터
    TCNT1 = 0;

    //high가 될때까지 대기하다가 high되면 
    while(!(PIND & (1<<PORTD7)))
    {
        if(TCNT1 >65000)
        {
            return 0;
        }
    }

    TCNT1 = 0 ;
    while(PIND & (1<<PORTD7))
    {
        if(TCNT1 > 65000)
        {
            TCNT1 = 0;
            break;
        }
    }
    double pulseWidth = 1000000.0 * TCNT1 * 1024/16000000;

    return pulseWidth / 58;

}