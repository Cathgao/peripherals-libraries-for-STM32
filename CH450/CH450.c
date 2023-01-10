/*
 * @Date: 2022-08-18 11:06:37
 * @LastEditors: Cath pjgao@youealcorp.com.cn
 * @LastEditTime: 2022-08-23 08:07:56
 * @FilePath: \MDK-ARMc:\Users\Administrator\Desktop\product\0733_new\Core\Src\CH450.c
 */
#include "CH450.h"
// #include "printf.h"

uint8_t NumberCode_CH450[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0-9

uint8_t CH450_send_sig_number(uint8_t pos, uint8_t num)
{
    uint8_t dig_addr = 0x64+2*pos;
    while (HAL_I2C_Master_Transmit(&CH450_port, dig_addr, &NumberCode_CH450[num], 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&CH450_port) != HAL_OK))
        {
            HAL_I2C_Init(&CH450_port);
            // printf_UART_DMA(&huart1, "CH450 write digi ERROR! 0x%x \n", HAL_I2C_GetError(&CH450_port));
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

void CH450_display_Error()
{
    uint8_t Error_code[] = {0x79, 0x50, 0x50, 0x5c, 0x50};
    for (uint8_t i = 0; i < 5; i++)
    {
        HAL_I2C_Master_Transmit(&CH450_port, 0x64 + 2 * i, &Error_code[i], 1, 0xff);
    }
}

void CH450_send_all_number(uint32_t num)
{
    //CH450_send_sig_number(0, num / 100000);
    CH450_send_sig_number(0, num % 100000 / 10000);
    CH450_send_sig_number(1, num % 10000 / 1000);
    CH450_send_sig_number(2, num % 1000 / 100);
    CH450_send_sig_number(3, num % 100 / 10);
    CH450_send_sig_number(4, num % 10);
}

uint8_t CH450_send_float( float num)
{
        // if ((num > 100) && (num < 1000))
        // {
        //     CH450_send_sig_number(1, (int)num % 1000 / 100);
        //     CH450_send_sig_number(2, (int)num % 100 / 10);
        //     CH450_send_12bit(((3 + 0x7) << 8) + ((int)num % 10) + 0x80);
        //     CH450_send_sig_number(4, (int)(num * 10) % 10);
        // }
        // else if ((num > 10) && (num < 100))
        // {
        //     CH450_send_sig_number(1, (int)num % 100 / 10);
        //     CH450_send_12bit(((2 + 0x7) << 8) + ((int)num % 10) + 0x80);
        //     CH450_send_sig_number(3, (int)(num * 10) % 10);
        //     CH450_send_sig_number(4, (int)(num * 100) % 100 / 10);
        // }
        // else if (num < 10)
        // {
        //     // CH450_send_sig_number(1, (int)num % 10);
        //     CH450_send_12bit(((1 + 0x7) << 8) + ((int)num % 10) + 0x80);
        //     CH450_send_sig_number(2, (int)(num * 10) % 10);
        //     CH450_send_sig_number(3, (int)(num * 100) % 10);
        //     CH450_send_sig_number(4, (int)(num * 1000) % 10);
        // }
        // else if (num < 1)
        // {
        //     CH450_send_12bit(((0 + 0x7) << 8) + ((int)num % 10) + 0x80);
        //     CH450_send_sig_number(1, (int)(num * 10) % 10);
        //     CH450_send_sig_number(2, (int)(num * 100) % 10);
        //     CH450_send_sig_number(3, (int)(num * 1000) % 10);
        // }
        return HAL_OK;
}

uint8_t CH450_ReadKey()
{
    uint8_t key_value;
    while (HAL_I2C_Master_Receive(&CH450_port, 0x4F, &key_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&CH450_port) != HAL_OK))
        {
            HAL_I2C_Init(&CH450_port);
            // printf_UART_DMA(&huart1, "CH450 read key ERROR! 0x%x \n", HAL_I2C_GetError(&CH450_port));
            return 0;
        }
    }
    //printf_UART_DMA(&huart1, "CH450 read key 0x%x \n", key_value);
    return key_value;
}

uint8_t CH450_init()
{
    uint8_t init_value = 0x03;
    while (HAL_I2C_Master_Transmit(&CH450_port, 0x48, &init_value, 1, 0xff) != HAL_OK)
    {
        if ((HAL_I2C_GetError(&CH450_port) != HAL_OK))
        {
            HAL_I2C_Init(&CH450_port);
            // printf_UART_DMA(&huart1, "CH450 init error\n", HAL_I2C_GetError(&CH450_port));
            return HAL_ERROR;
        }
    }
    CH450_send_all_number(00000);
    CH450_ReadKey();
    // printf_UART_DMA(&huart1,"CH450 init success\n");
    return HAL_OK;
}