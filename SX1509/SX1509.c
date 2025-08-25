#include "SX1509.h"
#include "math.h"
// #include "printf.h"

__IO uint16_t key_value;

uint8_t SX1509_init()
{
    uint8_t InputReg = InputPort0;
    uint8_t dev_addr = SX1509_addr;
    uint8_t reset_reg[] = {0x12, 0x34};
    uint8_t pullUp_reg = 0xff;
    uint8_t DirRegB = 0x01;
    HAL_Delay(100);
    while (HAL_I2C_Mem_Write_DMA(&SX1509_port, dev_addr, 0x06, I2C_MEMADD_SIZE_8BIT, &pullUp_reg, 1) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&SX1509_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "SX1509 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&SX1509_port));
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Mem_Write_DMA(&SX1509_port, dev_addr, 0x07, I2C_MEMADD_SIZE_8BIT, &pullUp_reg, 1) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&SX1509_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "SX1509 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&SX1509_port));
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Mem_Write_DMA(&SX1509_port, dev_addr, 0x0e, I2C_MEMADD_SIZE_8BIT, &DirRegB, 1) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&SX1509_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "SX1509 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&SX1509_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

uint8_t SX1509Scan()
{
    uint8_t dev_addr = SX1509_addr;
    uint8_t key[2];
    while (HAL_I2C_Mem_Read(&SX1509_port, dev_addr, 0x10, I2C_MEMADD_SIZE_8BIT, key, 2, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&SX1509_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "PCA9535 DMA read ERROR! 0x%x \n", HAL_I2C_GetError(&SX1509_port));
            return HAL_ERROR;
        }
    }
    key_value = key[1] + (key[0]<<8);
    return HAL_OK;
}

uint8_t key_convert(uint8_t *keyValue)
{
    uint8_t value;
    if (keyValue[0] != 0)
    {
        value = log2(keyValue[0]) + 1;
    }
    else if (keyValue[1] != 0)
    {
        value = log2(keyValue[1]) + 9;
    }
    return value;
}