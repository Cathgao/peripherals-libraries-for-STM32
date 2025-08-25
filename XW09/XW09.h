#ifndef __XW09_H__
#define __XW09_H__

#include "main.h"



#ifdef SW_I2C
#define SCL_PORT GPIOB
#define SDA_PORT GPIOB
#define SCL_PIN  GPIO_PIN_10
#define SDA_PIN  GPIO_PIN_11

#else
extern I2C_HandleTypeDef XW09_port;
#define XW09_port hi2c1
#define XW09_addr 0x80

uint8_t XW09_ReadKey(void);
#endif

#endif
