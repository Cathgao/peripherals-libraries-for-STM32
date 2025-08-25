#ifndef __SX1509_H__
#define __SX1509_H__

#include "main.h"

#define SX1509_addr 0x7c
#define SX1509_port hi2c1
extern I2C_HandleTypeDef SX1509_port;

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

extern __IO uint16_t key_value;

uint8_t SX1509_init();
uint8_t SX1509Scan();
uint8_t key_convert(uint8_t *keyValue);
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
