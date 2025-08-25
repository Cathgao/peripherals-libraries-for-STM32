#ifndef __CH450_H__
#define __CH450_H__

#include "main.h"

#define CH450_port hi2c1
//#define CH450_addr 0x48
extern I2C_HandleTypeDef CH450_port;

uint8_t CH450_send_sig_number(uint8_t pos,uint8_t num);
uint8_t CH450_send_float(float num);
uint8_t CH450_ReadKey();
void CH450_display_Error();
void CH450_send_all_number(uint32_t num);
uint8_t CH450_init();

#endif