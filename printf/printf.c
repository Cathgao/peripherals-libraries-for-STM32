// for ARM-MDK and ARM compiler V6 only

#include "printf.h"
#include "main.h"

__ASM(".global __use_no_semihosting");

uint8_t UART_printf_buffer[UART_PRINTF_MAX_LEN];

struct FILE
{
  int handle;
};

FILE __stdout;
void _sys_exit(int x)
{
  x = x;
}

int fputc(int ch, FILE *f)
{
  while ((USART1->ISR & 0x20) == 0)
    ;
  USART1->TDR = (uint8_t)ch;
  return ch;
}

void printf_UART_DMA(UART_HandleTypeDef *huart, char *format, ...)
{
  va_list arg_ptr; //ʵ�����ɱ�����б�
  while (!__HAL_UART_GET_FLAG(huart, UART_FLAG_TC))
    ;                        //�ж��Ƿ������
  va_start(arg_ptr, format); //��ʼ���ɱ�����б�
  vsnprintf((char *)UART_printf_buffer, UART_PRINTF_MAX_LEN + 1, format, arg_ptr);
  va_end(arg_ptr);
  HAL_UART_Transmit_DMA(huart, UART_printf_buffer, strlen((const char *)UART_printf_buffer));
}