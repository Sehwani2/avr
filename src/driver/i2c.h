#ifndef _I2C_H_
#define _I2C_H_


#include "def.h"

#define I2C_DDR        DDRD
#define I2C_SCL        PORTD0
#define I2C_SDA        PORTD1

void i2cInit();
void i2cStart();
void i2cStop();
void i2cTxData(uint8_t data);
void i2cTxByte(uint8_t devAddrRW, uint8_t data);

#endif // _I2C_H