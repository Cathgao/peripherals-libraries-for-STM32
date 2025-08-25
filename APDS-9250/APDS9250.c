#include "APDS9250.h"
// #include "printf.h"

uint8_t APDS9250_write_byte(uint8_t reg_addr, uint8_t reg_data)
{
    uint8_t data = reg_data;
    while (HAL_I2C_Mem_Write(&APDS9250_port, APDS9250_addr, reg_addr | COMMAND_BIT, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&APDS9250_port) != HAL_OK))
        {
            HAL_I2C_Init(&APDS9250_port);
            // printf_UART_DMA(&huart1, "APDS9250 write ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9250_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}
uint8_t APDS9250_read_byte(uint8_t reg_addr)
{
    uint8_t data;
    while (HAL_I2C_Mem_Read(&APDS9250_port, APDS9250_addr, reg_addr | COMMAND_BIT, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&APDS9250_port) != HAL_OK))
        {
            HAL_I2C_Init(&APDS9250_port);
            // printf_UART_DMA(&huart1, "APDS9250 read ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9250_port));
            return 0;
        }
    }
    return data;
}

uint16_t APDS9250_GetLux()
{
    uint8_t resualt[2];
    uint16_t Lux_value;
    resualt[0] = APDS9250_read_byte(0x13);
    resualt[1] = APDS9250_read_byte(0x14);
    Lux_value = resualt[0] + uint16_t(resualt[1]<<8);
    // printf_UART_DMA(&huart1, "OTP3001 read raw: CH0:%d CH1:%d\n", channel0, channel1);
    // printf_UART_DMA(&huart1, "OTP3001 value:%dlux\n", Lux_value);
    return Lux_value;
}

uint8_t APDS9250_init()
{
    uint8_t init_value = 0x06;
    if (APDS9250_write_byte(0x00, init_value))
    {
        // printf_UART_DMA(&huart1, "APDS9250 init fail\n");
        HAL_I2C_Init(&APDS9250_port);
        return HAL_ERROR;
    }
    // printf_UART_DMA(&huart1, "APDS9250 init success\n");
    return HAL_OK;
}
