#include <MC9S12G128.h>   
#include <string.h>
#include "mcuinit.h"
#include "hal_system.h" 
#include "hal_pwm.h" 
#include "hal_int.h"
#include "hal_can.h" 
#include "hal_port.h"
#include "protocol.h" 
#include "config.h"

                              
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
static unsigned int GetHalAddr(void)
{
  	//!<Todo:获取地址
  	unsigned int temp = 0;
#if 0
	//电平需要取反
	temp = Ctrl_In1?0:1;
	temp |= Ctrl_In2?0:2;
#else
	GetInput();
	temp = GetBigdogAddr();
#endif
    return temp;
}
/**
 * @LockAddr
 * @说明:用于锁定地址需要定时调用；
 */
void LockAddr(void)
{
	unsigned int temp = 0;
	if (mode_addr_err_timeout>0)
	{
		mode_addr_err_timeout--;
	}
	else
	{
		mode_addr_error = 0;
	}
	if(mode_addr_timeout<LOCK_ADDR_TIMEOUT)
	{
		mode_addr_look = 0;
		mode_addr_timeout++;
		temp = GetHalAddr();
		if (temp != Select_addr)
		{
			Select_addr = temp;
			mode_addr_timeout = 0;
			ID_Select(Select_addr);
		}
		else if(mode_addr_error != 0)
		{
			//!地址冲突不能进行锁定
			mode_addr_timeout = 0;
		}
	}
	else
	{
		mode_addr_look = 1;
		
	}
}

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
	else if(ID == ID_70x)
	{
		//!<地址冲突
		mode_addr_error = 1;
		mode_addr_err_timeout = ADDR_ERR_TIMEOUT;
	}
	else if(OnlineCheckID == ID)
	{
		OnlineCheckConfig = 1;
	}
	else if(ExcuteAppID == ID)
	{
		ExecutiveEraseFlashConfig = 1;
	}
}
 
 
void can_process0(void) 
{
  if (mode_addr_error == 1)
  {
  	ID_70x_data.addr_err = Select_addr;
  }
  else
  {
  	ID_70x_data.addr_err = 0xFF;
  }
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
 * R = 0.51K;
 * 1bit = 5/256/0.51 mA
 * n为采样点
 * ==> Ir = n * 5/256/0.51*2800mA = 107.2mA/bit
 */
#define AUIR3315_Ratio  1072/10
void Current_AUIR3315(void *des,void *src,int len)
{
	u8 *pOut = (u8 *)des;
	u8 *pIn = (u8*)src;
	u16 temp,i=0;
	for(;len>0;len--)
	{
		temp = (unsigned long)(*pIn)*AUIR3315_Ratio;
		pOut[i++] =  temp &0xFF;
		pOut[i++] =  (temp>>8)&0xFF;
		pIn++;
	}
}
//!<BTS 6143 D 电流 比率 9700
// Ir = n * 5/256/2*9700 mA = 94.7 mA/bit
#define BTS6143_Ratio  947/10
void Current_BTS6143(void *des,void *src,int len)
{
	u8 *pOut = (u8 *)des;
	u8 *pIn = (u8*)src;
	u16 temp,i=0;
	for(;len>0;len--)
	{
		temp = (unsigned long)(*pIn)*BTS6143_Ratio;
		pOut[i++] =  temp &0xFF;
		pOut[i++] =  (temp>>8)&0xFF;
		*pIn++;
	}
}
//!<BTS740S2 电流 比率 4800
//!<Ir = n * 5/256/2*4800 mA = 46.88 mA/bit
#define BTS740_Ratio    469/10
void Current_BTS740(void *des,void *src,int len)
{
	u8 *pOut = (u8 *)des;
	u8 *pIn = (u8*)src;
	u16 temp,i=0;
	for(;len>0;len--)
	{
		temp = (unsigned long)(*pIn)*BTS740_Ratio;
		pOut[i++] =  temp &0xFF;
		pOut[i++] =  (temp>>8)&0xFF;
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

//=============================================================
void ExecutiveCheckHandle(void)
{
	u8 data[8];
	data[0] = VERSIONS_MAJOR>>8;
	data[1] = VERSIONS_MAJOR;
	data[2] = VERSIONS_MINOR>>8;
	data[3] = VERSIONS_MINOR;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = CAN_BL_APP;
	hal_Can_SendData(OnlineCheckID,EXTENDED,0x03,8,data); 
}