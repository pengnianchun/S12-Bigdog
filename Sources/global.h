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
	u8 McErr1;
	u8 McErr2;
	u8 McErr3;
}
FIR_ERR;


EXTERN vu8 TimeOutConfig;		//定时器溢出标注
EXTERN vu16 RunTime;		//每近一次中断加1,用于做超时判断

EXTERN vu16  capture[2];//输入捕捉值
EXTERN vu16  pulse[2];//捕捉的脉冲数
EXTERN vu16  CtrlOutBuffer[3];//输出缓冲器
EXTERN FIR_ERR fir_err;
EXTERN u16	MC_SELECT;

#define ADC_BUF_MAX		0x20
EXTERN vu16 adc_cont;//采样计数
EXTERN vu16 u16_adc_buff[ADC_BUF_MAX];//单次采样数据缓存区

EXTERN u16 u16_admux0_data[22]; 
EXTERN u16 u16_admux1_data[22]; 

extern void GlobalParaInit(void);
#endif