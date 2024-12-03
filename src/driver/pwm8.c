#include "pwm8.h"

void pwm8Init()
{
    DDRB |= (1<<PORTB4);

    TCCR0 |= (1<<WGM01) | (1<<WGM00); 
    TCCR0 |= (1<<COM01);               
    TCCR0 |= (0<<CS01) | (1<<CS00);   
}

void pwm8Run(uint8_t duty)
{
    OCR0 = duty;
}