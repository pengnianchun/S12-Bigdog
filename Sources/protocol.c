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
#include "CtrlOut.h"


                              
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
ID_56_TYPE   ID_56x_data;
ID_57_TYPE   ID_57x_data;


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
uint32_t ID_56x;
uint32_t ID_57x;



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
  ID_56x=ID_56x_BASE + addr;
  ID_57x=ID_57x_BASE + addr;

  
  
}
//====================================================================//

void can_receive_protocol(uint32_t ID,uint8_t mode,uint8_t length,uint8_t *data) 
{
	if ((ID == 0x721)||(ID == 0x722))//721前模块   722后模块
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
//!<50055 电流 比率 16000
/**
 * Ir = Iif * 16000;
 * Iif = V/R;
 * 1bit = 5V/256;
 *      = 5V/R/256
 * R = 2K;
 * 1bit = 5/256/0.51 mA
 * n为采样点
 * ==> Ir = n * 5/256/2 *16000 mA = 156.25mA/bit
 */
#define AUIR3315_Ratio  1562/10
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
#define VERESION 100
void can_send_message_Pout(void) {
#if 1
    ID_56x_data.gPout[0]= gPout.BYTES[0]; //(unsigned char) (128 * FPO8 + 64 * FPO7 + 32 * FPO6 + 16 * FPO5 + 8 * FPO4 + 4 * FPO3 + 2 * FPO2 + FPO1);
    ID_56x_data.gPout[1] = gPout.BYTES[1]; //(unsigned char) (128 * OD + 64 * FPO15 + 32 * FPO14 + 16 * FPO13 + 8 * FPO12 + 4 * FPO11 + 2 * FPO10 + FPO9);
    ID_56x_data.gPout[2] = gPout.BYTES[2];
    ID_56x_data.gPout[3] = gPout.BYTES[3];
    ID_56x_data.gPout[4] = gPout.BYTES[4];
    ID_56x_data.gPout[5] = gPout.BYTES[5];	
    ID_56x_data.pf8 = (pf[32]&0x03) +((pf[33] << 2) & 0x0c)+(pf[34] << 4 & 0x30)+(pf[35] << 6 & 0xc0);;
    ID_56x_data.version= VERESION;

   #endif
    hal_Can_SendData(ID_56x,STANDARD,0x03,8,&ID_56x_data); 



    // can1_send_message(0x560 + g, data, 8);
}

void can_send_message_Fout(void) {
#if 1

    ID_57x_data.pf[0] = (pf[0]&0x03) +((pf[1] << 2) & 0x0c)+(pf[2] << 4 & 0x30)+(pf[3] << 6 & 0xc0);
    ID_57x_data.pf[1] = (pf[4]&0x03) +((pf[5] << 2) & 0x0c)+(pf[6] << 4 & 0x30)+(pf[7] << 6 & 0xc0);
    ID_57x_data.pf[2]= (pf[8]&0x03) +((pf[9] << 2) & 0x0c)+(pf[10] << 4 & 0x30)+(pf[11] << 6 & 0xc0);
    ID_57x_data.pf[3] = (pf[12]&0x03) +((pf[13] << 2) & 0x0c)+(pf[14] << 4 & 0x30)+(pf[15] << 6 & 0xc0);

    ID_57x_data.pf[4] = (pf[16]&0x03) +((pf[17] << 2) & 0x0c)+(pf[18] << 4 & 0x30)+(pf[19] << 6 & 0xc0);
    ID_57x_data.pf[5] = (pf[20]&0x03) +((pf[21] << 2) & 0x0c)+(pf[22] << 4 & 0x30)+(pf[23] << 6 & 0xc0);
    ID_57x_data.pf[6]= (pf[24]&0x03) +((pf[25] << 2) & 0x0c)+(pf[26] << 4 & 0x30)+(pf[27] << 6 & 0xc0);
    ID_57x_data.pf[7] = (pf[28]&0x03) +((pf[29] << 2) & 0x0c)+(pf[30] << 4 & 0x30)+(pf[31] << 6 & 0xc0);
	
    
#endif
    hal_Can_SendData(ID_57x,STANDARD,0x03,8,&ID_57x_data); 



    // can1_send_message(0x560 + g, data, 8);
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