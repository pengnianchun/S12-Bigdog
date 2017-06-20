#ifndef GLOBAL_H__
	#define GLOBAL_H__
	
#ifdef GLOBAL_EXTERN
#define EXTERN
#else
#define EXTERN extern
#endif
#include "Hal_system.h"

typedef struct{
	//mc33978错误代码
	int McErr1;
	int McErr2;
	int McErr3;
}
FIR_ERR;
#define PUSLE_SEVE_DATA_SIZE (10)

EXTERN vu8 TimeOutConfig;		//定时器溢出标注
EXTERN vu16 RunTime;		//每近一次中断加1,用于做超时判断

EXTERN vu16  capture[2];//输入捕捉值
EXTERN vu16  pulse[2][PUSLE_SEVE_DATA_SIZE];//捕捉的脉冲数
EXTERN vu16  CtrlOutBuffer[3];//输出缓冲器
EXTERN FIR_ERR fir_err;
EXTERN u16	MC_SELECT;
EXTERN u16 admux0_cont,admux1_cont;
#define ADC_BUF_MAX			0x20
#define ADC_CH_SIZE     	0x2C

EXTERN vu16 adc_cont;//采样计数
EXTERN vu16 u16_adc_buff[ADC_BUF_MAX];//单次采样数据缓存区
//0地址不用 1开始为采样数据
EXTERN u8 u16_admux_data[ADC_CH_SIZE]; 

EXTERN char OnlineCheckConfig,ExecutiveEraseFlashConfig;

EXTERN u16 ms_1,ms_10,ms_100,adc_time;//轮询相关计时器

EXTERN int Select_addr;  
EXTERN u8 mode_addr_look;//模块地址锁定标志 1有效;
EXTERN u8 mode_addr_error;//模块地址冲突标志；
EXTERN u16 mode_addr_timeout;//模块地址锁定计时器
EXTERN u16 mode_addr_err_timeout;

//!<时基为10ms；
EXTERN unsigned int wash_time; //3秒
EXTERN unsigned int wipe_int_time;
EXTERN unsigned int wipe_stop_time; //20秒
EXTERN unsigned int wipe_wpp_time;//电机上电延迟时间 
extern void GlobalParaInit(void);
#endif