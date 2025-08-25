#ifndef __PCA9632_H__
#define __PCA9632_H__

#include "main.h"

#define PCA9632_I2C_port hi2c1
#define PCA9632_Addr 0xC4
extern I2C_HandleTypeDef PCA9632_I2C_port;

uint8_t PCA9632_init();
uint8_t LED_ALLON();
uint8_t LED_ALLOFF();

typedef enum
{
    Mode1 = 0,
    Mode2,
    PWM0,
    PWM1,
    PWM2,
    PWM3,
    GRPPWM,
    GRPFREQ,
    LEDOUT,
    SUBADR1,
    SUBADR2,
    SUBADR3,
    ALLCALLADR
} PCA9632RegAddress;

typedef enum
{
    LEDoff = 0,
    LEDon,
    LEDPWM,
    LEDgroup
} LEDOutPutState;

#endif
