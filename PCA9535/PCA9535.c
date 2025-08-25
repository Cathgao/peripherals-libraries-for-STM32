#include "PCA9535.h"
// #include "printf.h"
#include "math.h"

__IO uint8_t key_value[2];

uint8_t PCA9535_init()
{
    uint8_t InputReg = InputPort0;
    while (HAL_I2C_Master_Transmit(&PCA9535_I2C_port, PCA9535_Addr, &InputReg, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9535_I2C_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "PCA9535 DMA write ERROR! 0x%x \n", HAL_I2C_GetError(&PCA9535_I2C_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

uint8_t PCA9535Scan()
{
    if (PCA9535_init() != HAL_OK)
    {
        return HAL_ERROR;
    }
    while (HAL_I2C_Master_Receive(&PCA9535_I2C_port, PCA9535_Addr, key_value, 2, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9535_I2C_port) != HAL_OK))
        {
            // printf_UART_DMA(&huart1, "PCA9535 DMA read ERROR! 0x%x \n", HAL_I2C_GetError(&PCA9535_I2C_port));
            return HAL_ERROR;
        }
    }
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
