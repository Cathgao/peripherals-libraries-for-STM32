#include "main.h"
#include "PCA9537.h"
//#include "printf.h"
#include "math.h"

uint8_t PCA9537_set_portIO(uint8_t port_num, uint8_t IO)
{
	uint8_t port_current_value = 0;
    while (HAL_I2C_Mem_Read(&PCA9537_port, PCA9537_addr, Config_reg, I2C_MEMADD_SIZE_8BIT, &port_current_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9537_port) != HAL_OK))
        {
            HAL_I2C_Init(&PCA9537_port);
            return HAL_ERROR;
        }
    }
    port_current_value &= ~(1 << port_num);
    port_current_value |= ((IO & 1) << port_num);
    while (HAL_I2C_Mem_Write(&PCA9537_port, PCA9537_addr, Config_reg, I2C_MEMADD_SIZE_8BIT, &port_current_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9537_port) != HAL_OK))
        {
            HAL_I2C_Init(&PCA9537_port);
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

uint8_t PCA9537_set_portLevel(uint8_t port_num, uint8_t level)
{
	uint8_t port_current_value = 0;
    while (HAL_I2C_Mem_Read(&PCA9537_port, PCA9537_addr, Output_reg, I2C_MEMADD_SIZE_8BIT, &port_current_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9537_port) != HAL_OK))
        {
            HAL_I2C_Init(&PCA9537_port);
            return HAL_ERROR;
        }
    }
    port_current_value &= ~(1 << port_num);
    port_current_value |= ((level & 1) << port_num);
    while (HAL_I2C_Mem_Write(&PCA9537_port, PCA9537_addr, Output_reg, I2C_MEMADD_SIZE_8BIT, &port_current_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9537_port) != HAL_OK))
        {
            HAL_I2C_Init(&PCA9537_port);
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

uint8_t PCA9537_read_port()
{
	uint8_t port_current_value = 0;
    while (HAL_I2C_Mem_Read(&PCA9537_port, PCA9537_addr, Input_reg, I2C_MEMADD_SIZE_8BIT, &port_current_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&PCA9537_port) != HAL_OK))
        {
            HAL_I2C_Init(&PCA9537_port);
            return 255;
        }
    }
	return port_current_value;
}

