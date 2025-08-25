#ifndef __TM1616_H__
#define __TM1616_H__

#define TM_DIN PA8
#define TM_STB PB15
#define TM_CLK PB15

#define TM_DIN_CLR HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0)
#define TM_DIN_SET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1)

#define TM_STB_CLR HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0)
#define TM_STB_SET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1)

#define TM_CLK_CLR HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0)
#define TM_CLK_SET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1)

#define SET_MODE 0x00
#define GRD1 0xc0
#define GRD2 0xc2
#define GRD3 0xc4
#define GRD4 0xc6

extern uint8_t NumberCode[10];//0-9

void TM1616_init();
void TM1616_writeRegData(uint8_t RegAddr,uint8_t data);
void TM1616_SetSingleNum(uint8_t pos, uint8_t num);
void TM1616_SetAllNum(uint16_t num);

#endif
