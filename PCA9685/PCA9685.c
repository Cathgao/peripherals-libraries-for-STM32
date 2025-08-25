#include "PCA9685.h"
#include "main.h"

__IO uint16_t LED_state0, LED_state1;

uint8_t LED_PCA9685_init(uint8_t pca_addr)
{
    uint8_t reg00_value = 0x20;
    uint8_t reg01_value = 0x00;
    uint8_t ALLLED_reg[]={0x00,0x10,0x00,0x10};
    uint8_t reg_value_LED[64];
    uint8_t dev_addr = pca_addr;
    LED0_OE_clr;
    LED1_OE_clr;

    while (HAL_I2C_Mem_Write(&LED_I2C_port, dev_addr, 0x00, I2C_MEMADD_SIZE_8BIT, &reg00_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&LED_I2C_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }

    while (HAL_I2C_Mem_Write(&LED_I2C_port, dev_addr, 0x01, I2C_MEMADD_SIZE_8BIT, &reg01_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&LED_I2C_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }

    while (HAL_I2C_Mem_Write(&LED_I2C_port, dev_addr, 0xfa, I2C_MEMADD_SIZE_8BIT, ALLLED_reg, 4, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&LED_I2C_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
            return HAL_ERROR;
        }
    }
    LED_state0 = 0xff;
    LED_state1 = 0xff;
    return HAL_OK;
}

uint8_t LED_switch(uint8_t select ,uint8_t LED_num,uint8_t LED_state)
{
    uint8_t LED_reg;
    uint8_t reg_addr = 0x09 + (LED_num * 4);
    if ((LED_num < 0) || (LED_num > 16))
    {
        return HAL_ERROR;
    }
    if(select == 0)
    {
        if(LED_state == 0)
        {
            LED_state0 &= ~((uint16_t)0x01 << LED_num);
            LED_reg = 0x00;
        }
        else
        {
            LED_state0 |= ((uint16_t)0x01 << LED_num);
            LED_reg = 0x10;
        }
        while (HAL_I2C_Mem_Write(&LED_I2C_port, LED_PCA9685_Addr_0, reg_addr, I2C_MEMADD_SIZE_8BIT, &LED_reg, 1, 0xff) != HAL_OK)
        {
            if ((HAL_I2C_GetError(&LED_I2C_port) != HAL_OK))
            {
                return HAL_ERROR;
            }
        }
    }
    else
    {
        if(LED_state == 0)
        {
            LED_state1 &= ~((uint16_t)0x01 << LED_num);
            LED_reg = 0x00;
        }
        else
        {
            LED_state1 |= ((uint16_t)0x01 << LED_num);
            LED_reg = 0x10;
        }
        while (HAL_I2C_Mem_Write(&LED_I2C_port, LED_PCA9685_Addr_1, reg_addr, I2C_MEMADD_SIZE_8BIT, &LED_reg, 1, 0xff) != HAL_OK)
        {
            if ((HAL_I2C_GetError(&LED_I2C_port) != HAL_OK))
            {
                return HAL_ERROR;
            }
        }
    }
    return HAL_OK;
}

uint8_t LED_toggle(uint8_t select, uint16_t LED_num)
{
    uint8_t LED_reg = 0x10;
    uint8_t reg_addr = 0x09 + (LED_num * 4);
    if (select == 0)
    {
        if ((LED_num < 0) || (LED_num > 16))
        {
            return HAL_ERROR;
        }
        if (LED_state0 & ((uint16_t)0x01 << LED_num)) // current on
        {
            LED_state0 &= ~((uint16_t)0x01 << LED_num);
            LED_reg = 0x00;
        }
        else
        {
            LED_state0 |= ((uint16_t)0x01 << LED_num);
            LED_reg = 0x10;
        }
        while (HAL_I2C_Mem_Write(&LED_I2C_port, LED_PCA9685_Addr_0, reg_addr, I2C_MEMADD_SIZE_8BIT, &LED_reg, 1, 0xff) != HAL_OK)
        {
            if ((HAL_I2C_GetError(&LED_I2C_port) != HAL_OK))
            {
                // printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
                return HAL_ERROR;
            }
        }
    }
    else
    {
        if ((LED_num < 0) || (LED_num > 16))
        {
            return HAL_ERROR;
        }
        if (LED_state1 & ((uint16_t)0x01 << LED_num))
        {
            LED_state1 &= ~((uint16_t)0x01 << LED_num);
            LED_reg = 0x00;
        }
        else
        {
            LED_state1 |= ((uint16_t)0x01 << LED_num);
            LED_reg = 0x10;
        }
        while (HAL_I2C_Mem_Write(&LED_I2C_port, LED_PCA9685_Addr_1, reg_addr, I2C_MEMADD_SIZE_8BIT, &LED_reg, 1, 0xff) != HAL_OK)
        {
            if ((HAL_I2C_GetError(&LED_I2C_port) != HAL_OK))
            {
                // printf_UART_DMA(&huart1, "PCA9632 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA_I2C_port));
                return HAL_ERROR;
            }
        }
    }
    printf_UART_DMA(&huart1, "LED switch PCA:%d,LED:%d,regaddr:0x%X,regdata:0x%X\n", select, LED_num, reg_addr, LED_reg);
    return HAL_OK;
    // printf_UART_DMA(&huart1,"toggle LED%d\n",LED_num);
    // printf_UART_DMA(&huart1,"LED_state%X\n",LED_state);
}