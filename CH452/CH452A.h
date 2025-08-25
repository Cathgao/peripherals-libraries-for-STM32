#ifndef __CH452_H__
#define __CH452_H__

#include "main.h"

#define CH452_port hi2c2
#define CH452_addr_3b 0x60
extern I2C_HandleTypeDef CH452_port;

#define LEFT 0
#define RIGHT 1

uint8_t CH452_send_12bit(uint16_t data);
uint8_t CH452_send_sig_number(uint8_t pos,uint8_t num);
void CH452_send_half_number(uint8_t half_posi,uint16_t num);
void CH452_send_half_float(uint8_t half_posi,float num);
void CH452_send_all_number(uint32_t num);
uint8_t CH452_init();

#endif