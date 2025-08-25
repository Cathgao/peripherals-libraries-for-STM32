#include "APDS9306.h"
// #include "printf.h"

uint8_t APDS9306_write_byte(uint8_t reg_addr, uint8_t reg_data)
{
    uint8_t data = reg_data;
    while (HAL_I2C_Mem_Write(&APDS9306_port, APDS9306_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&APDS9306_port) != HAL_OK))
        {
            HAL_I2C_Init(&APDS9306_port);
            // printf_UART_DMA(&huart1, "APDS9306 write ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9306_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}
uint8_t APDS9306_read_byte(uint8_t reg_addr)
{
    uint8_t data;
    while (HAL_I2C_Mem_Read(&APDS9306_port, APDS9306_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&APDS9306_port) != HAL_OK))
        {
            HAL_I2C_Init(&APDS9306_port);
            // printf_UART_DMA(&huart1, "APDS9306 read ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9306_port));
            return 0;
        }
    }
    return data;
}

uint16_t APDS9306_GetLux()
{
    uint16_t resualt[2];
    uint16_t Lux_value;
    resualt[0] = APDS9306_read_byte(0x0d);
    resualt[1] = APDS9306_read_byte(0x0e);
    Lux_value = resualt[0] + (resualt[1]<<8);
    // printf_UART_DMA(&huart1, "OTP3001 read raw: CH0:%d CH1:%d\n", channel0, channel1);
    // printf_UART_DMA(&huart1, "OTP3001 value:%dlux\n", Lux_value);
    return Lux_value;
}

uint8_t APDS9306_init()
{
    uint8_t init_value = 0x02;
    while (HAL_I2C_Mem_Write(&APDS9306_port, APDS9306_addr, 0x00, I2C_MEMADD_SIZE_8BIT, &init_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&APDS9306_port) != HAL_OK))
        {
            HAL_I2C_Init(&APDS9306_port);
            // printf_UART_DMA(&huart1, "APDS9306 write ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9306_port));
            return HAL_ERROR;
        }
    }
//    HAL_Delay(100);
//    init_value = 0x02;
//    while (HAL_I2C_Mem_Write(&APDS9306_port, APDS9306_addr, 0x00, I2C_MEMADD_SIZE_8BIT, &init_value, 1, 0xff) != HAL_OK)
//    {
//        if ((HAL_I2C_GetError(&APDS9306_port) != HAL_OK))
//        {
//            HAL_I2C_Init(&APDS9306_port);
//            // printf_UART_DMA(&huart1, "APDS9306 write ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9306_port));
//            return HAL_ERROR;
//        }
//    }
    // printf_UART_DMA(&huart1, "APDS9306 init success\n");
    return HAL_OK;
}
