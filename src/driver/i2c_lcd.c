#include "i2c_lcd.h"

uint8_t I2C_LCD_DATA;

void LCD_Data4bit(uint8_t data)
{
    I2C_LCD_DATA = (I2C_LCD_DATA & 0x0f) | (data & 0xf0);   // 상위 4비트
    LCD_EnablePin();
    I2C_LCD_DATA = (I2C_LCD_DATA & 0x0f) | ((data & 0x0f)<<4);  // 하위 4비트
    LCD_EnablePin();
}

void LCD_EnablePin()
{
    I2C_LCD_DATA &= ~(1<<LCD_E);
    i2cTxByte(LCD_DEV_ADDR, I2C_LCD_DATA);

    I2C_LCD_DATA |= (1<<LCD_E);
    i2cTxByte(LCD_DEV_ADDR, I2C_LCD_DATA);

    I2C_LCD_DATA &= ~(1<<LCD_E);
    i2cTxByte(LCD_DEV_ADDR, I2C_LCD_DATA);

    _delay_us(1600);
}

void LCD_WriteCommand(uint8_t commandData)
{
    I2C_LCD_DATA &= ~(1<<LCD_RS);
    I2C_LCD_DATA &= ~(1<<LCD_RW);
    LCD_Data4bit(commandData);
}

void LCD_WriteData(uint8_t charData)
{
    I2C_LCD_DATA |= (1<<LCD_RS);
    I2C_LCD_DATA &= ~(1<<LCD_RW);
    LCD_Data4bit(charData);
}

void LCD_BackLightOn()
{
    I2C_LCD_DATA |= (1<<LCD_BACKLIGHT);
    i2cTxByte(LCD_DEV_ADDR, I2C_LCD_DATA);
}

void LCD_GotoXY(uint8_t row, uint8_t col)
{
    col %= 16;
    row %= 2;
    uint8_t address = (0x40 * row) + col;
    uint8_t command = (0x80) + address;
    LCD_WriteCommand(command);
}

void LCD_WriteString(char *string)
{
    for(uint8_t i = 0; string[i]; i++)
    {
        LCD_WriteData(string[i]);
    }
}

void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
    LCD_GotoXY(row, col);
    LCD_WriteString(string);
}

void LCD_Init()
{
    i2cInit();

    _delay_ms(20);
    LCD_WriteCommand(0x03);
    _delay_ms(10);
    LCD_WriteCommand(0x03);
    _delay_ms(1);
    LCD_WriteCommand(0x03);
    
    LCD_WriteCommand(0x02);
    LCD_WriteCommand(COMMAND_4_BIT_MODE);
    LCD_WriteCommand(COMMAND_DISPLAY_OFF);
    LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
    LCD_WriteCommand(COMMAND_ENTRY_MODE);
    LCD_WriteCommand(COMMAND_DISPLAY_ON);
    LCD_BackLightOn();
    
}