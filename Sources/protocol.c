#include <MC9S12G128.h>   
#include "hal_system.h" 
#include "hal_pwm.h" 
#include "hal_int.h"
#include "hal_can.h" 
#include "hal_port.h"
#include "protocol.h" 

ID_6A4_TYPE  ID_6A4_data;
ID_454_TYPE  ID_454_data;

ID_68_TYPE  ID_681_data;
ID_68_TYPE  ID_682_data;
ID_68_TYPE  ID_683_data;

ID_67_TYPE  ID_671_data;
ID_67_TYPE  ID_672_data;
ID_67_TYPE  ID_673_data;

ID_56_TYPE  ID_561_data;
ID_56_TYPE  ID_562_data;
ID_56_TYPE  ID_563_data;

ID_45_TYPE  ID_451_data;
ID_45_TYPE  ID_452_data;
ID_45_TYPE  ID_453_data;

                              
ID_68_TYPE   *ID_68x_data;
ID_67_TYPE   *ID_67x_data;
ID_56_TYPE   *ID_56x_data;
ID_45_TYPE   *ID_45x_data;

uint32_t ID_67x;
uint32_t ID_68x;
uint32_t ID_56x;
uint32_t ID_45x;

//====================================================================//
void ID_Select(void)
{

  ID_67x=ID_671;
  ID_68x=ID_681;
  ID_56x=ID_561;
  ID_45x=ID_451;
  
  ID_68x_data=&(ID_681_data);
  ID_67x_data=&(ID_671_data);
  ID_56x_data=&(ID_561_data);
  ID_45x_data=&(ID_451_data);
}
//====================================================================//

void can_receive_protocol(uint32_t ID,uint8_t mode,uint8_t length,uint8_t *data) 
{
 switch(ID) 
 {
  case ID_6A4:
  
  ID_6A4_data.front1.Byte=data[0];
  ID_6A4_data.front2.Byte=data[1];
  ID_6A4_data.top1.Byte=  data[2];
  ID_6A4_data.top2.Byte=  data[3];
  ID_6A4_data.block1.Byte=data[4];
  ID_6A4_data.block2.Byte=data[5];
  
  break;
  
  case ID_454:
  
  ID_454_data.Totalmil[0]=data[0];
  ID_454_data.Totalmil[1]=data[1];
  ID_454_data.Totalmil[2]=data[2];
  ID_454_data.Totalmil[4]=data[3];
  ID_454_data.PulseNum[0]=data[4];
  ID_454_data.PulseNum[1]=data[5];
  
  break;
  
  default:
  break;
 
 }

}
 
 

void can_50ms_process0(void) 
{
  
 hal_Can_SendData(ID_68x,STANDARD,0x03,8,ID_68x_data); 
 
}


void can_500ms_process1(void) 
{
 
 ID_67x_data->num=1;
 hal_Can_SendData(ID_67x,STANDARD,0x03,8,ID_67x_data); 
 
 ID_67x_data->num=2;
 hal_Can_SendData(ID_67x,STANDARD,0x03,8,ID_67x_data); 
  
} 


void can_100ms_process2(void) 
{
 hal_Can_SendData(ID_56x,STANDARD,0x03,8,ID_56x_data); 
}


void can_1000ms_process3(void) 
{
 
 hal_Can_SendData(ID_45x,STANDARD,0x03,8,ID_45x_data); 
} 

void can_100ms_process4(void) 
{
 

} 