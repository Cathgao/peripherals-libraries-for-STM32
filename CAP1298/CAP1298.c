#include "math.h"
#include "printf.h"

__IO uint8_t key_value;

uint8_t Touch_CAP1298_init()
{
    uint8_t dev_addr = TOUCH_CAP1298_Addr;
    uint8_t button_enable_reg = 0xfe;
    uint8_t repeat_rate_reg = 0x00;
    uint8_t config_reg = 0x41;
    while (HAL_I2C_Mem_Write(&TOUCH_I2C_port, dev_addr, 0x21, I2C_MEMADD_SIZE_8BIT, &button_enable_reg, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TOUCH_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "SX1509 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&TOUCH_I2C_port));
            HAL_I2C_Init(&TOUCH_I2C_port);
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Mem_Write(&TOUCH_I2C_port, dev_addr, 0x28, I2C_MEMADD_SIZE_8BIT, &repeat_rate_reg, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TOUCH_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "SX1509 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&TOUCH_I2C_port));
            HAL_I2C_Init(&TOUCH_I2C_port);
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Mem_Write(&TOUCH_I2C_port, dev_addr, 0x44, I2C_MEMADD_SIZE_8BIT, &config_reg, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TOUCH_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9535 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&TOUCH_I2C_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

uint8_t Touch_CAP1298_read()
{
    uint8_t dev_addr = TOUCH_CAP1298_Addr;
    uint8_t key;
    uint8_t status_reg = 0x00;
    
    while (HAL_I2C_Mem_Read(&TOUCH_I2C_port, dev_addr, 0x03, I2C_MEMADD_SIZE_8BIT, &key, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TOUCH_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9535 DMA read ERROR! 0x%x \n", HAL_I2C_GetError(&TOUCH_I2C_port));
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Mem_Write(&TOUCH_I2C_port, dev_addr, 0x00, I2C_MEMADD_SIZE_8BIT, &status_reg, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TOUCH_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9535 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&TOUCH_I2C_port));
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Mem_Read(&TOUCH_I2C_port, dev_addr, 0x03, I2C_MEMADD_SIZE_8BIT, &key, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TOUCH_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9535 DMA read ERROR! 0x%x \n", HAL_I2C_GetError(&TOUCH_I2C_port));
            return HAL_ERROR;
        }
    }
    key_value = key;
    return HAL_OK;
}

uint8_t key_convert(uint8_t keyValue)
{
    return log2(keyValue);
}