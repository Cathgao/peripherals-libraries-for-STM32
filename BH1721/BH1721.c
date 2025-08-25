#include "BH1721.h"
#include "printf.h"

uint8_t BH1721_init()
{
    uint8_t Opecode[] = {0x01, 0x10};
    while (HAL_I2C_Master_Transmit(&BH1721_port, BH1721_addr, &Opecode[0], 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&BH1721_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&BH1721_port));
            return HAL_ERROR;
        }
    }
    while (HAL_I2C_Master_Transmit(&BH1721_port, BH1721_addr, &Opecode[1], 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&BH1721_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&BH1721_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

uint16_t BH1721_read()
{
    uint8_t resualt_raw[2];
    while (HAL_I2C_Master_Receive(&BH1721_port, BH1721_addr, resualt_raw, 2, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&BH1721_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&BH1721_port));
        }
    }
    //printf_UART_DMA(&huart1, "sensor raw data: %X %X\n", resualt_raw[0], resualt_raw[1]);
    return (uint16_t)(resualt_raw[0] << 8) + resualt_raw[1];
}