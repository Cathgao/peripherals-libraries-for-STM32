#include "CH452A.h"
#include "printf.h"

uint8_t CH452_send_12bit(uint16_t data)
{
    uint8_t data_8bit = data;
    uint8_t dev_addr = CH452_addr_3b + (data >> 7);
    return HAL_I2C_Master_Transmit(&CH452_port, dev_addr, &data_8bit, 1, 0xff);
}

uint8_t CH452_send_sig_number(uint8_t pos, uint8_t num)
{
    if ((pos > 8) || (pos < 0))
    {
        return HAL_ERROR;
    }
    uint16_t send_data = ((pos + 0x7) << 8) + num;
    return CH452_send_12bit(send_data);
    
}

void CH452_send_half_number(uint8_t half_posi, uint16_t num)
{
    switch (half_posi)
    {
    case LEFT:
        CH452_send_sig_number(1, num / 1000);
        CH452_send_sig_number(2, num % 1000 / 100);
        CH452_send_sig_number(3, num % 100 / 10);
        CH452_send_sig_number(4, num % 10);
        break;
    case RIGHT:
        CH452_send_sig_number(5, num / 1000);
        CH452_send_sig_number(6, num % 1000 / 100);
        CH452_send_sig_number(7, num % 100 / 10);
        CH452_send_sig_number(8, num % 10);
        break;
    default:
        break;
    }
}

void CH452_send_all_number(uint32_t num)
{
    CH452_send_sig_number(1, num / 10000000);
    CH452_send_sig_number(2, num % 10000000 / 1000000);
    CH452_send_sig_number(3, num % 1000000 / 100000);
    CH452_send_sig_number(4, num % 100000 / 10000);
    CH452_send_sig_number(5, num % 10000 / 1000);
    CH452_send_sig_number(6, num % 1000 / 100);
    CH452_send_sig_number(7, num % 100 / 10);
    CH452_send_sig_number(8, num % 10);
}

void CH452_send_half_float(uint8_t half_posi, float num)
{
    switch (half_posi)
    {
    case LEFT:
        if ((num > 100) && (num < 1000))
        {
            CH452_send_sig_number(1, (int)num % 1000 / 100);
            CH452_send_sig_number(2, (int)num % 100 / 10);
            CH452_send_12bit(((3 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(4, (int)(num * 10) % 10);
        }
        else if ((num > 10) && (num < 100))
        {
            CH452_send_sig_number(1, (int)num % 100 / 10);
            CH452_send_12bit(((2 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(3, (int)(num * 10) % 10);
            CH452_send_sig_number(4, (int)(num * 100) % 100 / 10);
        }
        else if (num < 10)
        {
            // CH452_send_sig_number(1, (int)num % 10);
            CH452_send_12bit(((1 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(2, (int)(num * 10) % 10);
            CH452_send_sig_number(3, (int)(num * 100) % 10);
            CH452_send_sig_number(4, (int)(num * 1000) % 10);
        }
        else if (num < 1)
        {
            CH452_send_12bit(((0 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(1, (int)(num * 10) % 10);
            CH452_send_sig_number(2, (int)(num * 100) % 10);
            CH452_send_sig_number(3, (int)(num * 1000) % 10);
        }
        break;
    case RIGHT:
        if ((num > 100) && (num < 1000))
        {
            CH452_send_sig_number(5, (int)num % 1000 / 100);
            CH452_send_sig_number(6, (int)num % 100 / 10);
            CH452_send_12bit(((7 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(8, (int)(num * 10) % 10);
        }
        else if ((num > 10) && (num < 100)) // 10.333
        {
            CH452_send_sig_number(5, (int)num % 100 / 10);
            // CH452_send_sig_number(2, (int)num % 10);
            CH452_send_12bit(((6 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(7, (int)(num * 10) % 10);
            CH452_send_sig_number(8, (int)(num * 100) % 100 / 10);
        }
        else if (num < 10)
        {
            // CH452_send_sig_number(1, (int)num % 10);
            CH452_send_12bit(((5 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(6, (int)(num * 10) % 10);
            CH452_send_sig_number(7, (int)(num * 100) % 10);
            CH452_send_sig_number(8, (int)(num * 1000) % 10);
        }
        else if (num < 1)
        {
            CH452_send_12bit(((5 + 0x7) << 8) + ((int)num % 10) + 0x80);
            CH452_send_sig_number(6, (int)(num * 10) % 10);
            CH452_send_sig_number(7, (int)(num * 100) % 10);
            CH452_send_sig_number(8, (int)(num * 1000) % 10);
        }
        break;
    default:
        break;
    }
}

uint8_t CH452_init()
{
    CH452_send_12bit(0x700);
    CH452_send_12bit(0x2a0);
    CH452_send_12bit(0x401);
    CH452_send_12bit(0x580);
    CH452_send_all_number(00000000);
    return HAL_OK;
}