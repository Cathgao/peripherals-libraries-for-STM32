#include "main.h"
#include "OTP3001.h"
#ifdef OTP3001PRINT
#include "printf.h"
#endif
#include "math.h"

uint32_t OTP3001_GetLux()
{
    uint8_t resualt[2];
    uint32_t Lux_value;
    while (HAL_I2C_Mem_Read(&OTP3001_port, OTP3001_addr, 0x00, I2C_MEMADD_SIZE_8BIT, resualt, 2, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&OTP3001_port) != HAL_OK))
        {
            HAL_I2C_Init(&OTP3001_port);
            return 0;
        }
    }
    Lux_value = 0.01 * pow(2, resualt[0] >> 4) * (((resualt[0] & 0x0F) << 8) + resualt[1]);
#ifdef OTP3001PRINT
    printf_UART_DMA(&huart1, "OTP3001 read raw: 0x%X\n", (resualt[0] << 8) + resualt[1]);
    printf_UART_DMA(&huart1, "OTP3001 value:%dlux\n", Lux_value);
#endif
    return Lux_value;
}

uint8_t OTP3001_init()
{
    uint8_t init_value[] = {0xC6,0x10};
    while (HAL_I2C_Mem_Write(&OTP3001_port, OTP3001_addr, 0x01, I2C_MEMADD_SIZE_8BIT, &init_value, 2, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&OTP3001_port) != HAL_OK))
        {
            HAL_I2C_Init(&OTP3001_port);
            return HAL_ERROR;
        }
    }
    #ifdef OTP3001PRINT
    printf_UART_DMA(&huart1,"OTP3001 init success\n");
    #endif
    return HAL_OK;
}