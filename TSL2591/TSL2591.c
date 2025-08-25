#include "TSL2591.h"
#include "printf.h"

uint8_t TSL2591_write_byte(uint8_t reg_addr, uint8_t reg_data)
{
    uint8_t data = reg_data;
    while (HAL_I2C_Mem_Write(&TSL2591_port, TSL2591_addr, reg_addr | COMMAND_BIT, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TSL2591_port) != HAL_OK))
        {
            HAL_I2C_Init(&TSL2591_port);
            printf_UART_DMA(&huart1, "TSL2591 write ERROR! 0x%x \n", HAL_I2C_GetError(&TSL2591_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}
uint8_t TSL2591_read_byte(uint8_t reg_addr)
{
    uint8_t data;
    while (HAL_I2C_Mem_Read(&TSL2591_port, TSL2591_addr, reg_addr | COMMAND_BIT, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&TSL2591_port) != HAL_OK))
        {
            HAL_I2C_Init(&TSL2591_port);
            printf_UART_DMA(&huart1, "TSL2591 read ERROR! 0x%x \n", HAL_I2C_GetError(&TSL2591_port));
            return 0;
        }
    }
    return data;
}

uint32_t TSL2591_GetLux()
{
    uint8_t resualt[4];
    uint32_t Lux_value;
    uint16_t channel0,channel1;
    resualt[0] = TSL2591_read_byte(0x14);
    resualt[1] = TSL2591_read_byte(0x15);
    resualt[2] = TSL2591_read_byte(0x16);
    resualt[3] = TSL2591_read_byte(0x17);
    channel0 = resualt[0] + (resualt[1] << 8);
    channel1 = resualt[1] + (resualt[2] << 8);
    Lux_value = (channel0 ) / 9.84;
    printf_UART_DMA(&huart1, "OTP3001 read raw: CH0:%d CH1:%d\n", channel0, channel1);
    printf_UART_DMA(&huart1, "OTP3001 value:%dlux\n", Lux_value);
    return Lux_value;
}

uint8_t TSL2591_init()
{
    uint8_t init_value[] = {0x03, 0x12};
    if (TSL2591_write_byte(0x00, init_value[0]) || TSL2591_write_byte(0x01, init_value[1]))
    {
        printf_UART_DMA(&huart1, "TSL2591 init fail\n");
        HAL_I2C_Init(&TSL2591_port);
        return HAL_ERROR;
    }
    printf_UART_DMA(&huart1, "TSL2591 init success\n");
    return HAL_OK;
}
