#include "main.h"
#include "TM1616.h"

uint8_t NumberCode[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0-9

void TM1616_write_byte(uint8_t data)
{
    for (uint8_t count = 0; count < 8; count++)
    {
        TM_CLK_CLR;
        if (data & 0x01)
        {
            TM_DIN_SET;
        }
        else
        {
            TM_DIN_CLR;
        }
        data >>= 1;
        TM_CLK_SET;
    }
}

void TM1616_writeRegData(uint8_t RegAddr, uint8_t data)
{
    TM_STB_CLR;
    TM1616_write_byte(RegAddr);
    TM1616_write_byte(data);
    TM_STB_SET;
}

void TM1616_SetSingleNum(uint8_t pos, uint8_t num)
{
    TM_STB_CLR;
    TM1616_write_byte(0x00);
    TM_STB_SET;
    TM_STB_CLR;
    TM1616_write_byte(0x44); // fix addr mode
    TM_STB_SET;
    TM1616_writeRegData(0xc0 + pos * 2, NumberCode[num]);
}

void TM1616_SetAllNum(uint16_t num)
{
    TM_STB_CLR;
    TM1616_write_byte(0x00);
    TM_STB_SET;
    TM_STB_CLR;
    TM1616_write_byte(0x40); // continuous addr mode
    TM_STB_SET;
    TM_STB_CLR;
    TM1616_write_byte(0xc0);
    TM1616_write_byte(NumberCode[num % 10]);       // 00h
    TM1616_write_byte(0x00);                       // 01h
    TM1616_write_byte(NumberCode[num % 100 / 10]); // 02h
    TM1616_write_byte(0x00);
    TM1616_write_byte(NumberCode[num % 1000 / 100]);
    TM1616_write_byte(0x00);
    TM1616_write_byte(NumberCode[num / 1000]);
    TM_STB_SET;
}

void TM1616_init()
{
    TM_STB_SET;
    TM_CLK_SET;
    HAL_Delay(10);
    TM_STB_CLR;
    TM1616_write_byte(0x00);
    TM_STB_SET;
    TM_STB_CLR;
    TM1616_write_byte(0x8f);
    TM_STB_SET;
}