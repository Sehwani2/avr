#include "ap.h"


void apInit()
{    
    // pwm8Init();
    // pwm16Init();
    uart0Init();
    // uart1Init();
    LCD_Init();
    timerInit();
}

void apMain()
{
    // LED led;
    // led.port = &PORTF;
    // led.pin  = 0;
    // ledInit(&led);

    // BTN btnOn;
    // BTN btnOff;
    // BTN btnTog;
    // buttonInit(&btnOn,&BUTTON_DDR, &BUTTON_PIN,&BUTTON_PORT,BUTTON_ON);

    FILE OUTPUT = FDEV_SETUP_STREAM(uart0Transmit_wrapper, NULL, _FDEV_SETUP_WRITE); 
    stdout = &OUTPUT;

    extern char rxBuff[100];
    extern volatile uint8_t rxFlag;   


    // extern char receiveBuffer1[256];
    // extern volatile uint8_t rxFlag1;
    // extern FILE OUTPUT1; 
    //  stdout = &OUTPUT1;

    LCD_WriteStringXY(0, 0, "hello world"); 
    uint8_t distance;

    while(1)
    {
        triggerPin();
        distance = meanDistance();
        printf("distance : %d cm\r\n", distance);
        _delay_ms(500);

        if (rxFlag == 1)  // 새로운 데이터 수신 여부 체크
        {
            printf("Received: %s\n", rxBuff);  // 수신된 문자열 출력
            rxFlag = 0;  // 플래그 초기화
        }

        // if(rxFlag0 == 1)
        // {
        //     rxFlag0 =0;
        //     printf("%s\n",receiveBuffer0);
        // }
        // if(rxFlag1 == 1)
        // {
        //     rxFlag1 =0;
        //     printf("%s\n",receiveBuffer1);
        // }

        ///////////////////////////////////////////////
        // char received = uart0Receive();  // 데이터 수신

        // if(received == 'a')
        // {
        //     ledOn(&led);
            
        //     uart0TransmitString("LED_ON\n");

        //     OCR3A = 130;
        // }
        // else if(received == 'b')
        // {
        //     ledOff(&led);
            
        //     uart0TransmitString("LED_OFF\n");

        //     OCR3A = 620;     
        // }
        ////////////////////////////////////////
        // OCR3A = 130;
        // _delay_ms(1000);
        // OCR3A = 370;
        // _delay_ms(1000);     
        // OCR3A = 620;
        // _delay_ms(1000);

        // if(buttonGetState(&btnOn) == ACT_RELEASED)
        // {
        //     ledOn(&led);
        //     pwm8Run(250);
        // }
        // if(buttonGetState(&btnOff) == ACT_RELEASED)
        // {
        //     ledOff(&led);
        //     pwm8Run(125);
        // }
        // if(buttonGetState(&btnTog) == ACT_RELEASED)
        // {
        //     ledOff(&led);
        //     pwm8Run(0);
        // }
    }
}