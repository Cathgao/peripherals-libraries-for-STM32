/******************************Copyright (c)***********************************
*                Jiangsu Zhihai Electronic Technology Co., Ltd.
*                      Research & Development Department
*
*													www.smarthealth-tech.com
*
-------------------------------------------------------------------------------
* @file    TM1637.h
* @author  GU DONGDONG
* @date    2015-11-25  
*******************************************************************************/
#ifndef TM1637_H
#define TM1637_H
#include "main.h"
#include "stdbool.h"

#define TM1637_CLK_1           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define TM1637_CLK_0           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)

#define TM1637_DIO_1           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET)
#define TM1637_DIO_0           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET)

#define TM1637_READ_DIO        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)


#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44

#define POINT_ON   1
#define POINT_OFF  0

#define ON 1
#define OFF 0
//IO��������
//#define TM1637_DIO_IN()     {GPIOB->CRH&=0X0FFFFFFF;GPIOB->CRH|=(u32)8<<28;}

//#define TM1637_DIO_OUT()    {GPIOB->CRH&=0X0FFFFFFF;GPIOB->CRH|=(u32)3<<28;}
#define TM1637_DIO_IN()		GPIO_InitTypeDef GPIO_Initure;\
													GPIO_Initure.Pin = GPIO_PIN_11;\
													GPIO_Initure.Mode = GPIO_MODE_INPUT;\
													GPIO_Initure.Pull = GPIO_PULLUP;\
													HAL_GPIO_Init(GPIOB, &GPIO_Initure)


#define TM1637_DIO_OUT() 	GPIO_InitTypeDef GPIO_Initure;\
													GPIO_Initure.Pin = GPIO_PIN_11;\
													GPIO_Initure.Mode =GPIO_MODE_OUTPUT_PP;\
													GPIO_Initure.Pull = GPIO_NOPULL;\
													GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;\
													HAL_GPIO_Init(GPIOB, &GPIO_Initure)
/** 
  * @brief  Configuration Dots's Mode enumeration  
  */
typedef enum
{ 
	DulDot = 0x00,
  LowDot= 0x01,
  HighDot= 0x2,
}DisDotSetting;
typedef enum
{ 
	sty = 0x00,
  Jep = 0x01, 
}DisDotMode;

//extern unsigned char NumDis[];
void TM1637_Delay_us(unsigned  int Nus); 
void TM1637_Start(void);
void TM1637_Ack(void);
void TM1637_Stop(void);
uint8_t TM1637_WriteByte(unsigned char oneByte);
unsigned char TM1637_ScanKey(void);
void TM1637_NixieTubeDisplay(void);
void TM1637_NixieTubeDisplayChar(unsigned char ch,unsigned char p);
void TM1637_NixieTubeDisplayNum(short Num,DisDotSetting Set,DisDotMode Mode);
void TM1637_Init(void);
void TM1637LED_Init(void);

void display(uint8_t BitAddr,int8_t DispData);
void clearDisplay(void);
void TM1637_set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr);
int8_t coding(int8_t DispData);
void TM1637_point(bool PointFlag);
void TimingISR(void);
void TimeUpdate(void);
void SMG_Display(int8_t display1, int8_t display2,int8_t display3,int8_t display4);
int8_t coding_OFF(int8_t DispData);
void Display_GONGLV(uint8_t BitAddr,int8_t DispData);
#endif
