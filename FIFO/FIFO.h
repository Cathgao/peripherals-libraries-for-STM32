#ifndef __FIFO_H__
#define __FIFO_H__

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define FIFO_SIZE 50

extern uint8_t FIFO_write;
extern uint8_t FIFO_count;
extern uint8_t FIFO_read;
extern uint8_t FIFO_buff[FIFO_SIZE];

void FIFO_Data_Write(uint8_t write_data);
uint8_t FIFO_Data_Read(void);
void FIFO_reset(void);


#endif 
