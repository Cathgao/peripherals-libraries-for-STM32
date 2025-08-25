#ifndef __LTR308ALS_H__
#define __LTR308ALS_H__

#include "main.h"
#define LTR308ALS_port hi2c1
#define LTR308ALS_addr (0x53 << 1)
#define reg_MAIN_CTRL 0x00
#define reg_ALS_MEAS_RATE 0x04
#define reg_ALS_GAIN 0x05
#define reg_ALS_DATA_0 0x0d
#define reg_ALS_DATA_1 0x0e
#define reg_ALS_DATA_2 0x0f
#define reg_INT_CFG 0x19

extern I2C_HandleTypeDef hLTR308ALS_porti2c1;

uint8_t LTR308ALS_init();
uint16_t LTR308ALS_read_2byte(uint8_t reg_addr, uint8_t length);
uint8_t LTR308ALS_write_byte(uint8_t reg_addr,uint8_t reg_data);
uint16_t LTR308ALS_GetLux();


#endif
