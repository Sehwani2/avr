#include "i2c.h"

void i2cInit()
{
    I2C_DDR |= (1<<I2C_SCL) | (1<<I2C_SDA);
    TWBR = 72;      // 100khz
    // TWBR = 32;   // 200khz
    // TWBR = 12;   // 400khz
}

void i2cStart()
{
    TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);    // enable, start condition, interrupt
    while (!(TWCR & (1<<TWINT)));
}

void i2cStop()
{
    TWCR |= (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void i2cTxData(uint8_t data)
{
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}

void i2cTxByte(uint8_t devAddrRW, uint8_t data)
{
    i2cStart();
    i2cTxData(devAddrRW);
    i2cTxData(data);
    i2cStop();
    
}