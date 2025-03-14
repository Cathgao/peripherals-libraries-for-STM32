#include "FIFO.h"

uint8_t FIFO_write;
uint8_t FIFO_count;
uint8_t FIFO_read;
uint8_t FIFO_buff[FIFO_SIZE];

void FIFO_reset(void)
{
    FIFO_count = 0;
    FIFO_read = 0;
    FIFO_write = 0;
    for (uint8_t i = 0; i < FIFO_SIZE; i++)
    {
        FIFO_buff[i] = 0;
    }
}

void FIFO_Data_Write(uint8_t write_data) // write byte to queue tail
{
    FIFO_buff[FIFO_write] = write_data;
    if (++FIFO_write >= FIFO_SIZE)
    {
        FIFO_write = 0;
    }

    if (FIFO_count < FIFO_SIZE)
    {
        FIFO_count++;
    }
    else
    {
        if(++FIFO_read >= FIFO_SIZE)
        {
            FIFO_read = 0;
        }
    }
}

uint8_t FIFO_Data_Read(void) // read byte from queue head. data will be deleted after read
{
    if (FIFO_count == 0) // queue is empty
    {
        return 0;
    }
    else
    {
        uint8_t read_data;
        read_data = FIFO_buff[FIFO_read];
        if (++FIFO_read >= FIFO_SIZE)
        {
            FIFO_read = 0;
        }
        FIFO_count--;
        return read_data;
    }
}
