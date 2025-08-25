#ifndef __PCA9537_H__
#define __PCA9537_H__

#include "main.h"

#define PCA9537_port hi2c1
#define PCA9537_addr 0x92

extern I2C_HandleTypeDef PCA9537_port;

#define Input_reg 0
#define Output_reg 1
#define Polarity_reg 2
#define Config_reg 3

uint8_t PCA9537_set_portIO(uint8_t port_num, uint8_t IO);
uint8_t PCA9537_set_portLevel(uint8_t port_num, uint8_t level);
uint8_t PCA9537_read_port();

#endif
