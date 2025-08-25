#ifndef __OTP3001_H__
#define __OTP3001_H__

#include "main.h"
// #define OTP3001PRINT
#define OTP3001_port hi2c1
#define OTP3001_addr 0x88

extern I2C_HandleTypeDef OTP3001_port;

uint32_t OTP3001_GetLux();
uint8_t OTP3001_init();

#endif
