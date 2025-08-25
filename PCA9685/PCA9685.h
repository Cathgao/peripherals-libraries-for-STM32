#ifndef __PCA9685_H__
#define __PCA9685_H__

#define LED_I2C_port hi2c1
extern I2C_HandleTypeDef LED_I2C_port;

#define LED_PCA9685_Addr_0 0x94
#define LED0_OE_clr HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0)
#define LED0_OE_set HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1)

#define LED_PCA9685_Addr_1 0x8c
#define LED1_OE_clr HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0)
#define LED1_OE_set HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1)


extern __IO uint16_t LED_state0, LED_state1;

uint8_t LED_PCA9685_init(uint8_t pca_addr);
uint8_t LED_ALLON();
uint8_t LED_ALLOFF();
uint8_t key_convert(uint8_t keyValue);
uint8_t LED_toggle(uint8_t select,uint16_t LED_num);
uint8_t LED_switch(uint8_t select ,uint8_t LED_num,uint8_t LED_state);


#endif
