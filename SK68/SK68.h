#ifndef __SK68_H__
#define __SK68_H__
#include "main.h"

//struct LED_struct  //GRB
//{
//  uint8_t LOGO[3];
//  uint8_t LineTop[3];
//  uint8_t Sonic[3];
//  uint8_t Warn[3];
//  uint8_t Network[3];
//  uint8_t SD[3];
//  uint8_t Usb[3];
//  uint8_t Interrupt[3];
//  uint8_t Ring[3];
//  uint8_t Log[3];
//  uint8_t Update[3];
//  uint8_t Restore[3];
//  uint8_t Backup[3];
//  uint8_t Restart[3];
//  uint8_t Scan[3];
//  uint8_t Test[3];
//};

struct LED_struct//GRB
{
  uint32_t LOGO;
  uint32_t TopLine;
  uint32_t Sonic;
  uint32_t Warn;
  uint32_t Network;
  uint32_t SD;
  uint32_t Usb;
  uint32_t Interrupt;
  uint32_t Ring;
  uint32_t Log;
  uint32_t Update;
  uint32_t Restore;
  uint32_t Backup;
  uint32_t Restart;
  uint32_t Scan;
  uint32_t Test;
};



void SK68_set_color(uint8_t LED_name, uint32_t* color);

#endif /* __SK68_H_ */
