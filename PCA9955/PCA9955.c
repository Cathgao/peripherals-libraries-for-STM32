#include "PCA9955.h"
#include "printf.h"
#include "math.h"

__IO uint16_t LED_state=0x5555;

static uint8_t LED_commit(uint16_t LED_state)
{
    uint8_t dev_addr = PCA9955_Addr;
    uint8_t LED_reg[] = {0x00, 0x00, 0x00, 0x00};
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            LED_reg[i] += ((0x01 & (LED_state >> (j + 4 * i))) << (2 * j));
        }
    }
    printf_UART_DMA(&huart1, "###LED %X %X %X %X\n", LED_reg[0], LED_reg[1], LED_reg[2], LED_reg[3]);
    while (HAL_I2C_Mem_Write_DMA(&PCA_I2C_port, dev_addr, 0x82, I2C_MEMADD_SIZE_8BIT, LED_reg, sizeof(LED_reg)) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9955 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }
}

uint8_t PCA9955_init()
{
    uint8_t reg00_value = 0x06;
    uint8_t reg45_value = 0xff;
    uint8_t reg_value_LED[] = {0x00, 0x00, 0x00, 0x00};
    uint8_t reg_value_MISC[32];
    uint8_t dev_addr = PCA9955_Addr;

    for (uint8_t i = 0; i < 32; i++) // fill with 0xff
    {
        reg_value_MISC[i] = 0xff;
    }

    while (HAL_I2C_Mem_Write_DMA(&PCA_I2C_port, dev_addr, 0x45, I2C_MEMADD_SIZE_8BIT, &reg45_value, 1) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9955 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }

    while (HAL_I2C_Mem_Write_DMA(&PCA_I2C_port, dev_addr, 0x82, I2C_MEMADD_SIZE_8BIT, reg_value_LED, sizeof(reg_value_LED)) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9955 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }

    while (HAL_I2C_Mem_Write_DMA(&PCA_I2C_port, dev_addr, 0x88, I2C_MEMADD_SIZE_8BIT, reg_value_MISC, sizeof(reg_value_MISC)) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9955 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }

    while (HAL_I2C_Mem_Write_DMA(&PCA_I2C_port, dev_addr, 0x00, I2C_MEMADD_SIZE_8BIT, &reg00_value, 1) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA_I2C_port) != HAL_OK))
        {
            printf_UART_DMA(&huart1, "PCA9955 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }
    LED_commit(LED_state);
    return HAL_OK;
}

void LED_toggle(uint16_t LED_num)
{
    if ((LED_num < 0) || (LED_num > 16))
    {
        return;
    }
    if (LED_state & ((uint16_t)0x01 << LED_num))
    {
        LED_state &= ~((uint16_t)0x01 << LED_num);
    }
    else
    {
        LED_state |= ((uint16_t)0x01 << LED_num);
    }
    printf_UART_DMA(&huart1, "toggle LED%d\n", LED_num);
    printf_UART_DMA(&huart1, "LED_state%X\n", LED_state);
    LED_commit(LED_state);
}
