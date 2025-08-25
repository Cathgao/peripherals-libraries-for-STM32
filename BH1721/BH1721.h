#ifndef __BH1721_H__
#define __BH1721_H__

#include "main.h"

#define BH1721_port hi2c1
#define BH1721_addr 0x46

extern I2C_HandleTypeDef BH1721_port

uint8_t BH1721_init();
uint16_t BH1721_read();

#endif