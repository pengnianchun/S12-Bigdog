#include <MC9S12G128.h>   
#include <string.h>
#include "mcuinit.h"
#include "hal_system.h" 
#include "hal_pwm.h" 
#include "hal_int.h"
#include "hal_can.h" 
#include "hal_port.h"
#include "protocol.h" 


                              
ID_70_TYPE   ID_70x_data;
ID_71_TYPE   ID_71x_data;
ID_72_TYPE   ID_72x_data;
ID_73_TYPE   ID_73x_data;
ID_73_TYPE   ID_74x_data;
ID_73_TYPE   ID_75x_data;
ID_73_TYPE   ID_76x_data;
ID_73_TYPE   ID_77x_data;
ID_73_TYPE   ID_78x_data;
ID_73_TYPE   ID_79x_data;
ID_73_TYPE   ID_7Ax_data;
ID_73_TYPE   ID_7Bx_data;


uint32_t ID_70x;
uint32_t ID_71x;
uint32_t ID_72x;
uint32_t ID_73x;
uint32_t ID_74x;
uint32_t ID_75x;
uint32_t ID_76x;
uint32_t ID_77x;
uint32_t ID_78x;
uint32_t ID_79x;
uint32_t ID_7Ax;
uint32_t ID_7Bx;

//====================================================================//
void ID_Select(int addr)
{

  ID_70x=ID_70x_BASE + addr;
  ID_71x=ID_71x_BASE + addr;
  ID_72x=ID_72x_BASE + addr;
  ID_73x=ID_73x_BASE + addr;
  ID_74x=ID_74x_BASE + addr;
  ID_75x=ID_75x_BASE + addr;
  ID_76x=ID_76x_BASE + addr;
  ID_77x=ID_77x_BASE + addr;
  ID_78x=ID_78x_BASE + addr;
  ID_79x=ID_79x_BASE + addr;
  ID_7Ax=ID_7Ax_BASE + addr;
  ID_7Bx=ID_7Bx_BASE + addr;

  
  
}
//====================================================================//

void can_receive_protocol(uint32_t ID,uint8_t mode,uint8_t length,uint8_t *data) 
{
	if (ID == ID_72x)
	{
		memcpy(&ID_72x_data,data,8);
	}
}
 
 
void can_process0(void) 
{
  
 hal_Can_SendData(ID_70x,STANDARD,0x03,8,&ID_70x_data); 
 
}
void can_process1(void) 
{
 memcpy(&ID_71x_data,&u16_admux_data[38],6);
 hal_Can_SendData(ID_71x,STANDARD,0x03,8,&ID_71x_data); 
 
}
//!<AUIR3315 电流 比率 2800
/**
 * Ir = Iif * 2800;
 * Iif = V/R;
 * 1bit = 5V/256;
 *      = 5V/R/256
 * R = 1K;
 * 1bit = 5/256mA
 * n为采样点
 * ==> Ir = n * 5/256*2800mA = 54.6875mA/bit
 */
#define AUIR3315_Ratio  5468/100
void Current_AUIR3315(void *src,void *des,int len)
{
	u16 *pOut = (u16 *)des;
	u8 *pIn = (u8*)src;
	for(;len<=0;len--)
	{
		*pOut++ = (*pIn)*AUIR3315_Ratio;
		*pIn++;
	}
}
//!<BTS 6143 D 电流 比率 9700
// Ir = n * 5/256*9700 mA = 183.4
#define BTS6143_Ratio  1834/10
void Current_BTS6143(void *src,void *des,int len)
{
	u16 *pOut = (u16 *)des;
	u8 *pIn = (u8*)src;
	for(;len<=0;len--)
	{
		*pOut++ = (*pIn)*BTS6143_Ratio;
		*pIn++;
	}
}
//!<BTS740S2 电流 比率 4800
//!<Ir = n * 5/256*4800 mA = 93.75
#define BTS740_Ratio    937/10
void Current_BTS740(void *src,void *des,int len)
{
	u16 *pOut = (u16 *)des;
	u8 *pIn = (u8*)src;
	for(;len<=0;len--)
	{
		*pOut++ = (*pIn)*BTS740_Ratio;
		*pIn++;
	}
}
void can_process3(void) 
{
 //memcpy(&ID_73x_data,&u16_admux_data[1],8);
 Current_AUIR3315(&ID_73x_data,&u16_admux_data[1],4);
 hal_Can_SendData(ID_73x,STANDARD,0x03,8,&ID_73x_data); 
}
void can_process4(void) 
{
 //memcpy(&ID_74x_data,&u16_admux_data[9],8);
  Current_BTS6143(&ID_74x_data,&u16_admux_data[5],4);
 hal_Can_SendData(ID_74x,STANDARD,0x03,8,&ID_74x_data); 
}
void can_process5(void) 
{
 //memcpy(&ID_75x_data,&u16_admux_data[17],8);
 Current_BTS6143(&ID_75x_data,&u16_admux_data[9],4);
 hal_Can_SendData(ID_75x,STANDARD,0x03,8,&ID_75x_data); 
}
void can_process6(void) 
{
 //memcpy(&ID_76x_data,&u16_admux_data[25],8);
 Current_BTS6143(&ID_76x_data,&u16_admux_data[13],4);
 hal_Can_SendData(ID_76x,STANDARD,0x03,8,&ID_76x_data); 
}
void can_process7(void) 
{
 //memcpy(&ID_77x_data,&u16_admux_data[33],4);
 Current_BTS6143(&ID_77x_data,&u16_admux_data[17],4);
 hal_Can_SendData(ID_77x,STANDARD,0x03,8,&ID_77x_data); 
}
void can_process8(void) 
{
 Current_BTS740(&ID_78x_data,&u16_admux_data[21],4);
 hal_Can_SendData(ID_78x,STANDARD,0x03,8,&ID_78x_data); 
}
void can_process9(void) 
{
 Current_BTS740(&ID_79x_data,&u16_admux_data[25],4);
 hal_Can_SendData(ID_79x,STANDARD,0x03,8,&ID_79x_data); 
}
void can_processA(void) 
{
 Current_BTS740(&ID_7Ax_data,&u16_admux_data[29],4);
 hal_Can_SendData(ID_7Ax,STANDARD,0x03,8,&ID_7Ax_data); 
}
void can_processB(void) 
{
 Current_BTS740(&ID_7Bx_data,&u16_admux_data[33],4);
 hal_Can_SendData(ID_7Bx,STANDARD,0x03,8,&ID_7Bx_data); 
}