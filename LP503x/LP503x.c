#include "LP503x.h"

void LP563x_LED_on(uint8_t LED,uint8_t brigntness)
{
    uint8_t intensity = brigntness * 2.55;
    while (HAL_I2C_Mem_Write(&LP563x_port, LP563x_addr, (LED + 0x14), I2C_MEMADD_SIZE_8BIT, &intensity, 1 ,0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&LP563x_port) != HAL_OK))
        {
            HAL_I2C_Init(&LP563x_port);
            // printf_UART_DMA(&huart1, "CH455 init error\n", HAL_I2C_GetError(&CH455_port));
        }
    }
}

void LP563x_LED_all_on(void)
{
    uint8_t LED_reg[27];
    for (uint8_t i = 0; i < 27; i++)
    {
        LED_reg[i] = 0x80;
    }
    while (HAL_I2C_Mem_Write(&LP563x_port, LP563x_addr, 0x14, I2C_MEMADD_SIZE_8BIT, &LED_reg, sizeof(LED_reg) ,0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&LP563x_port) != HAL_OK))
        {
            HAL_I2C_Init(&LP563x_port);
            // printf_UART_DMA(&huart1, "CH455 init error\n", HAL_I2C_GetError(&CH455_port));
        }
    }
}


uint8_t LP563x_init()
{
    uint8_t init_value = 0xff;
    while (HAL_I2C_Mem_Write(&LP563x_port, LP563x_addr, 0x38, I2C_MEMADD_SIZE_8BIT, &init_value, 1 ,0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&LP563x_port) != HAL_OK))
        {
            HAL_I2C_Init(&LP563x_port);
            // printf_UART_DMA(&huart1, "CH455 init error\n", HAL_I2C_GetError(&CH455_port));
            return HAL_ERROR;
        }
    }
    init_value = 0x40;
    while (HAL_I2C_Mem_Write(&LP563x_port, LP563x_addr, 0x00, I2C_MEMADD_SIZE_8BIT, &init_value, 1 ,0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&LP563x_port) != HAL_OK))
        {
            HAL_I2C_Init(&LP563x_port);
            // printf_UART_DMA(&huart1, "CH455 init error\n", HAL_I2C_GetError(&CH455_port));
            return HAL_ERROR;
        }
    }
    // CH455_ReadKey();
    // printf_UART_DMA(&huart1,"CH455 init success\n");
    return HAL_OK;
}