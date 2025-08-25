#include "TM1637.h"
#include "main.h"

uint8_t Cmd_SetData;
uint8_t Cmd_SetAddr;
uint8_t  Cmd_DispCtrl;
bool _PointFlag;

//int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
uint8_t SMG1_Num,SMG2_Num,SMG3_Num,SMG4_Num;
int8_t ClockPoint = 1;
unsigned char Update;
int8_t halfsecond = 0;
int8_t second;
int8_t minute ;
int8_t hour;


unsigned char temp=0xCF;//显示跳动的冒号
unsigned char NumDis[24]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0X6F,\
                          0x77,0x7C,0x39,0x5E,0x79,0x71,\
                          0x08,0x48,0x49,\
                          0x76,0x38,0x0E,0x50,0x37};//0123456789ABCDEF一二三HLJRS  	

static int8_t TubeTab[] = {0x3f,0x06,0x5b,0x4f,
                           0x66,0x6d,0x7d,0x07,
                           0x7f,0x6f,0x77,0x7c,
                           0x39,0x5e,0x79,0x71};//0~9,A,b,C,d,E,F   
													
void TM1637_Delay_us(unsigned  int Nus)
{
 for(;Nus>0;Nus--)
	{
	  __nop();
	}
}

void TM1637_Start(void)
{
	TM1637_DIO_OUT(); 
  TM1637_CLK_1;
	TM1637_DIO_1;
  TM1637_Delay_us(4);
	TM1637_DIO_0;
	TM1637_Delay_us(4);
	TM1637_CLK_0;
	TM1637_Delay_us(4);
}
void TM1637_Ack(void)
{
	TM1637_DIO_IN(); 
  TM1637_CLK_0;
	TM1637_Delay_us(10);
	while(TM1637_READ_DIO);
	TM1637_CLK_1;
	TM1637_Delay_us(4);
	TM1637_CLK_0;
}
void TM1637_Stop(void)
{
	TM1637_DIO_OUT(); 
	TM1637_CLK_0;
	TM1637_Delay_us(4);
	TM1637_DIO_0;
	TM1637_Delay_us(4);
	TM1637_CLK_1;
	TM1637_Delay_us(4);
	TM1637_DIO_1;
	TM1637_Delay_us(4);
}
uint8_t TM1637_WriteByte(unsigned char oneByte)
{
 unsigned char i,count1;
	TM1637_DIO_OUT(); 
	for(i=0;i<8;i++)
	{
	 TM1637_CLK_0;
		if(oneByte&0x01)
		{
			TM1637_DIO_1;
		}
		else
		{
			TM1637_DIO_0;
		}
		TM1637_Delay_us(4);
		oneByte=oneByte>>1;
		TM1637_CLK_1;
		TM1637_Delay_us(4);
	}
	TM1637_CLK_0;
	TM1637_Delay_us(4);
	TM1637_DIO_1;
	TM1637_Delay_us(4);
	TM1637_CLK_1;
	
	GPIO_Initure.Pin = GPIO_PIN_10;
	GPIO_Initure.Mode = GPIO_MODE_INPUT;
	GPIO_Initure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure); 
	
	while(TM1637_READ_DIO)
	{
		count1+=1;
		if(count1==200)
		{
			TM1637_DIO_OUT();
			TM1637_DIO_0;
			count1=0;
			return 1;
		}
		TM1637_DIO_IN();
	}
	
	GPIO_Initure.Pin = GPIO_PIN_10;
	GPIO_Initure.Mode =GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	return 0;
}
void TM1637_Write(unsigned char DATA)   
{
        unsigned char i;   
        for(i=0;i<8;i++)        
        {
						TM1637_CLK_0;     
						if(DATA & 0x01)
						TM1637_DIO_1;
						else TM1637_DIO_0;
						TM1637_Delay_us(6);
						DATA=DATA>>1;      
						TM1637_CLK_1;    
						TM1637_Delay_us(6);
        }  
        //TM1637_ack();
}
void TM1637_Init(void)
{
 TM1637_set(5,0X00,0X00);
 clearDisplay();
}

void TM1637_set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and it takes effect the next time it displays.
}

void clearDisplay(void)
{
  display(0x00,0x7f);
  display(0x01,0x7f);
  display(0x02,0x7f);
  display(0x03,0x7f);  
}

void display(uint8_t BitAddr,int8_t DispData)
{
  int8_t SegData;
  TM1637_Start();        
  TM1637_WriteByte(ADDR_FIXED);
  TM1637_Stop();           
  TM1637_Start();          
  TM1637_WriteByte(BitAddr|0xc0);
  TM1637_WriteByte(SegData);
  TM1637_Stop();            
  TM1637_Start();          
  TM1637_WriteByte(0x8c);
  TM1637_Stop();           
}

int8_t coding(int8_t DispData)
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0; 
  if(DispData == 0x7f) DispData = 0x00 + PointData;//The bit digital tube off
  else DispData = TubeTab[DispData] + PointData;
  return DispData;
}


void TimeUpdate(void)
{
  if(ClockPoint)TM1637_point(POINT_ON);
  else TM1637_point(POINT_OFF); 
  SMG1_Num = hour / 10;
  SMG2_Num = hour % 10;
  SMG3_Num = minute / 10;
  SMG4_Num = minute % 10;
  Update = OFF;
}

void TM1637_point(bool PointFlag)
{
  _PointFlag = PointFlag;
}

void TimingISR()
{
	hour=(SMG1_Num*10)+SMG2_Num;
	minute=(SMG3_Num*10)+SMG4_Num;
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute --;
      if(minute == -1)
      {
				minute=59;
        hour --;
        if(hour == -1)
				{
					hour = 0;
        minute = 0;
				}
      }
      second = 0;
    }
    halfsecond = 0;  
  }
  ClockPoint = (~ClockPoint) & 0x01;
}

void SMG_Display(int8_t display1, int8_t display2,int8_t display3,int8_t display4)
{
	Display_GONGLV(0X00,display1);	
	Display_GONGLV(0X01,display2);
	Display_GONGLV(0X02,display3);
	Display_GONGLV(0X03,display4);
}


void Display_GONGLV(uint8_t BitAddr,int8_t DispData)
{
  TM1637_Start();         
  TM1637_WriteByte(ADDR_FIXED);
  TM1637_Stop();           
  TM1637_Start();          
  TM1637_WriteByte(BitAddr|0xc0);
  TM1637_WriteByte(DispData);
  TM1637_Stop();            
  TM1637_Start();          
  TM1637_WriteByte(0x8f);
  TM1637_Stop();           
}

int8_t coding_OFF(int8_t DispData)
{

  if(DispData == 0x7f) DispData = 0x00 + 0;//The bit digital tube off
  else DispData = TubeTab[DispData] + 0;
  return DispData;
}


