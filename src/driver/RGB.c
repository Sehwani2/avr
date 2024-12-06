#include "RGB.h"

void RGBInit(void)
{
    // RGB LED 핀을 출력으로 설정
    LED_DDR |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN);
    
    // 초기 상태를 모두 OFF로 설정
    RGBOffAll();
}

void RGBOn(RGB_Color color)
{
    // 선택된 색상의 LED를 켬
    switch (color)
    {
        case RED:
            LED_PORT |= (1 << RED_PIN);
            break;
        case GREEN:
            LED_PORT |= (1 << GREEN_PIN);
            break;
        case BLUE:
            LED_PORT |= (1 << BLUE_PIN);
            break;
    }
}

void RGBOff(RGB_Color color)
{
    // 선택된 색상의 LED를 끔
    switch (color)
    {
        case RED:
            LED_PORT &= ~(1 << RED_PIN);
            break;
        case GREEN:
            LED_PORT &= ~(1 << GREEN_PIN);
            break;
        case BLUE:
            LED_PORT &= ~(1 << BLUE_PIN);
            break;
    }
}

void RGBOffAll(void)
{
    // 모든 LED를 끔
    LED_PORT &= ~((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN));
}