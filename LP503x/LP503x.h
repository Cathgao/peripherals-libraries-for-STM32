#ifndef __LP563X_H__
#define __LP563X_H__

#include "main.h"

#define LP563x_port hi2c2
#define LP563x_addr 0x64

extern I2C_HandleTypeDef LP563x_port;

void LP563x_LED_all_on(void);
void LP563x_LED_on(uint8_t LED,uint8_t brigntness);
uint8_t LP563x_init();

#endif
