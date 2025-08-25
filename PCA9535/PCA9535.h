#ifndef __PCA9535_H__
#define __PCA9535_H__

#include "main.h"

#define PCA9535_I2C_port hi2c1
#define PCA9535_Addr 0x40
extern I2C_HandleTypeDef PCA9535_I2C_port;

#define KEY1 0x01
#define KEY2 0x02
#define KEY3 0x04
#define KEY4 0x08
#define KEY5 0x10
#define KEY6 0x20
#define KEY7 0x40
#define KEY8 0x80
#define KEY9 0x01
#define KEY10 0x02
#define KEY11 0x04
#define KEY12 0x08

uint8_t PCA9535_init();
uint8_t PCA9535Scan();
uint8_t key_convert(uint8_t *keyValue);

extern __IO uint8_t key_value[2];
typedef enum
{
    InputPort0 = 0,
    InputPort1,
    OutPort0,
    OutPort1,
    PolarityInversionPort0,
    PolarityInversionPort1,
    ConfigurationPort0,
    ConfigurationPort1
} PCA9535CommandByte;

#endif
