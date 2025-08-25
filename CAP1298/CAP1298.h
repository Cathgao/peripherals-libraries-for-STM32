#ifndef __CAP1298_H__
#define __CAP1298_H__

#include "main.h"

#define TOUCH_I2C_port hi2c1
#define TOUCH_CAP1298_Addr 0x50

extern I2C_HandleTypeDef TOUCH_I2C_port;

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
extern __IO uint8_t key_value;
uint8_t Touch_CAP1298_init();
uint8_t Touch_CAP1298_read();
uint8_t key_convert(uint8_t keyValue);

#endif
