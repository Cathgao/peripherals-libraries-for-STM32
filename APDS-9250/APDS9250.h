#ifndef __APDS9250_H__
#define __APDS9250_H__

#include "main.h"
#define APDS9250_port hi2c2
#define APDS9250_addr 0x52

#define COMMAND_BIT 0xA0

#define reg_ENABLE 0x00
#define reg_CONFIG 0x01
#define reg_C0DATAL 0x14
#define reg_C0DATAH 0x15
#define reg_C1DATAL 0x16
#define reg_C1DATAH 0x17

extern I2C_HandleTypeDef APDS9250_port;

uint8_t APDS9250_init();
uint8_t APDS9250_read_byte(uint8_t reg_addr);
uint8_t APDS9250_write_byte(uint8_t reg_addr,uint8_t reg_data);
uint16_t APDS9250_GetLux();

#endif

