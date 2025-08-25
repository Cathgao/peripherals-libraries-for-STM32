#include "LTR308ALS.h"



uint16_t LTR308ALS_read_2byte(uint8_t reg_addr, uint8_t length)
{
  uint16_t data;
  while (HAL_I2C_Mem_Read(&LTR308ALS_port, LTR308ALS_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&data, length, 0xff) != HAL_OK)
  {
      if ((HAL_I2C_GetError(&LTR308ALS_port) != HAL_OK))
      {
          HAL_I2C_Init(&LTR308ALS_port);
          // printf_UART_DMA(&huart1, "APDS9306 read ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9306_port));
          return 0;
      }
  }
  return data;
}
uint8_t LTR308ALS_write_byte(uint8_t reg_addr,uint8_t reg_data)
{
  uint8_t data = reg_data;
  while (HAL_I2C_Mem_Write(&LTR308ALS_port, LTR308ALS_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xff) != HAL_OK)
  {
      if ((HAL_I2C_GetError(&LTR308ALS_port) != HAL_OK))
      {
          HAL_I2C_Init(&LTR308ALS_port);
          // printf_UART_DMA(&huart1, "APDS9306 write ERROR! 0x%x \n", HAL_I2C_GetError(&APDS9306_port));
          return HAL_ERROR;
      }
  }
  return HAL_OK;
}


uint8_t LTR308ALS_init()
{
  if(LTR308ALS_write_byte(reg_MAIN_CTRL, 0x02) != HAL_OK)
    {
      return HAL_ERROR;
    }
  if(LTR308ALS_write_byte(reg_ALS_MEAS_RATE, 0x40) != HAL_OK)
    {
      return HAL_ERROR;
    }
  return HAL_OK;
}

uint16_t LTR308ALS_GetLux()
{
  uint16_t raw_data = 0;
  raw_data = LTR308ALS_read_2byte(reg_ALS_DATA_0, 2);
  return (float)raw_data*0.8;
}

