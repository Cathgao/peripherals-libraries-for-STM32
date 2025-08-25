#ifndef __PCACHIP_H__
#define __PCACHIP_H__

#include "main.h"

#define PCA_I2C_port hi2c1
#define PCA9955_Addr 0x02
extern I2C_HandleTypeDef PCA_I2C_port;

extern __IO uint16_t LED_state;

uint8_t PCA9955_init();
uint8_t LED_ALLON();
uint8_t LED_ALLOFF();
void LED_toggle(uint16_t LED_num);