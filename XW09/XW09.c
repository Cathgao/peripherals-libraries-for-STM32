#include "XW09.h"

#ifdef SW_I2C
void MyI2C_W_SCL(uint8_t BitValue)
{
	HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, (GPIO_PinState)BitValue);		//根据BitValue，设置SCL引脚的电平											//延时10us，防止时序频率超过要求
}

void MyI2C_W_SDA(uint8_t BitValue)
{
	HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, (GPIO_PinState)BitValue);		//根据BitValue，设置SDA引脚的电平，BitValue要实现非0即1的特性											//延时10us，防止时序频率超过要求
}

GPIO_PinState MyI2C_R_SDA(void)
{
	GPIO_PinState BitValue;
	BitValue = HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN);		//读取SDA电平											//延时10us，防止时序频率超过要求
	return BitValue;											//返回SDA电平
}

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);							//释放SDA，确保SDA为高电平
	MyI2C_W_SCL(1);							//释放SCL，确保SCL为高电平
	MyI2C_W_SDA(0);							//在SCL高电平期间，拉低SDA，产生起始信号
	MyI2C_W_SCL(0);							//起始后把SCL也拉低，即为了占用总线，也为了方便总线时序的拼接
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);							//拉低SDA，确保SDA为低电平
	MyI2C_W_SCL(1);							//释放SCL，使SCL呈现高电平
	MyI2C_W_SDA(1);							//在SCL高电平期间，释放SDA，产生终止信号
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)				//循环8次，主机依次发送数据的每一位
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));	//使用掩码的方式取出Byte的指定一位数据并写入到SDA线
		MyI2C_W_SCL(1);						//释放SCL，从机在SCL高电平期间读取SDA
		MyI2C_W_SCL(0);						//拉低SCL，主机开始发送下一位数据
	}
}

GPIO_PinState MyI2C_ReceiveByte(void)
{
	uint8_t i;
	GPIO_PinState Byte = (GPIO_PinState)0x00;					//定义接收的数据，并赋初值0x00，此处必须赋初值0x00，后面会用到
	MyI2C_W_SDA(1);							//接收前，主机先确保释放SDA，避免干扰从机的数据发送
	for (i = 0; i < 8; i ++)				//循环8次，主机依次接收数据的每一位
	{
		MyI2C_W_SCL(1);						//释放SCL，主机机在SCL高电平期间读取SDA
		if (MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}	//读取SDA数据，并存储到Byte变量
														//当SDA为1时，置变量指定位为1，当SDA为0时，不做处理，指定位为默认的初值0
		MyI2C_W_SCL(0);						//拉低SCL，从机在SCL低电平期间写入SDA
	}
	return Byte;							//返回接收到的一个字节数据
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);					//主机把应答位数据放到SDA线
	MyI2C_W_SCL(1);							//释放SCL，从机在SCL高电平期间，读取应答位
	MyI2C_W_SCL(0);							//拉低SCL，开始下一个时序模块
}

GPIO_PinState MyI2C_ReceiveAck(void)
{
	GPIO_PinState AckBit;							//定义应答位变量
	MyI2C_W_SDA(1);							//接收前，主机先确保释放SDA，避免干扰从机的数据发送
	MyI2C_W_SCL(1);							//释放SCL，主机机在SCL高电平期间读取SDA
	AckBit = MyI2C_R_SDA();					//将应答位存储到变量里
	MyI2C_W_SCL(0);							//拉低SCL，开始下一个时序模块
	return AckBit;							//返回定义应答位变量
}

uint16_t XW09_ReadKey (void)
{

}

#else

uint8_t XW09_ReadKey (void)
{
  uint16_t key_value;
  while (HAL_I2C_Master_Receive(&XW09_port, XW09_addr, &key_value, 2, 0xff) != HAL_OK)
    {
      if ((HAL_I2C_GetError (&XW09_port) != HAL_OK))
	{
	  HAL_I2C_Init (&XW09_port);
	  return 255;
	}
    }
//  CDC_Transmit_FS(&key_value, 2);
  switch(key_value)
  {
    case 0xffef:
      return 0;
	  break;
    case 0xfff7:
      return 1;
          break;
    case 0xfffb:
      return 2;
          break;
    case 0xfffd:
      return 3;
          break;
    case 0xfffe:
      return 4;
          break;
    case 0xffff:
      return 5;
          break;
    case 0x7fff:
      return 6;
          break;
    case 0xbfff:
      return 7;
          break;
    case 0xdfff:
      return 8;
          break;
    default:
      return 255;
	  break;
  }
}

#endif
