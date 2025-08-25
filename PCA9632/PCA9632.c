#include "PCA9632.h"
// #include "printf.h"
#include "math.h"

uint8_t PCA9632_init()
{
    uint8_t mode1 = 0x06;
    uint8_t tmp[] = {0x14, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0x0};//, 0x55};
    while (HAL_I2C_Mem_Write(&PCA9632_I2C_port, PCA9632_Addr, 0x00, I2C_MEMADD_SIZE_8BIT, &mode1, 1,0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9632_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA9632_I2C_port));
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Mem_Write(&PCA9632_I2C_port, PCA9632_Addr, 0x81, I2C_MEMADD_SIZE_8BIT, tmp, sizeof(tmp),0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9632_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA9632_I2C_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

uint8_t LED_ALLON()
{
    uint8_t LEDAllOn = 0x55;
    while (HAL_I2C_Mem_Write(&PCA9632_I2C_port, PCA9632_Addr, LEDOUT, I2C_MEMADD_SIZE_8BIT, &LEDAllOn, 1,0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9632_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA9632_I2C_port));
            return HAL_ERROR;
        }
    }
    printf_UART_DMA(&huart1, "PCA9632 DMA write success! All LEDs should on\n");
    return HAL_OK;
}

uint8_t LED_ALLOFF()
{
    uint8_t LEDAllOff = 0x00;
    while (HAL_I2C_Mem_Write_DMA(&PCA9632_I2C_port, PCA9632_Addr, LEDOUT, I2C_MEMADD_SIZE_8BIT, &LEDAllOff, 1) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9632_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA9632_I2C_port));
            return HAL_ERROR;
        }
    }
    printf_UART_DMA(&huart1, "PCA9632 DMA write success! All LEDs should off\n");
    return HAL_OK;
}

uint8_t LED_switch(uint8_t LED_group, uint8_t state)
{
    uint8_t newState = 0;
    if (LED_group < 5 && LEDgroup >= 0)
    {
        LEDState[LED_group] = state;
    }
    newState = LEDState[0] + (LEDState[1] << 2) + (LEDState[2] << 4) + (LEDState[3] << 6);
    __nop();
    while (HAL_I2C_Mem_Write(&PCA9632_I2C_port, PCA9632_Addr, LEDOUT, I2C_MEMADD_SIZE_8BIT, &newState, 1,0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9632_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA9632_I2C_port));
            return HAL_ERROR;
        }
    }
    printf_UART_DMA(&huart1, "PCA9632 write 0x%X\n", newState);
    return HAL_OK;
}