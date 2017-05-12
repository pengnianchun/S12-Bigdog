#ifndef GLOBAL_H__
	#define GLOBAL_H__
	
#ifdef GLOBAL_EXTERN
#define EXTERN
#else
#define EXTERN extern
#endif
#include "Hal_system.h"

typedef struct{
	//mc33978�������
	u8 McErr1;
	u8 McErr2;
	u8 McErr3;
}
FIR_ERR;


EXTERN vu8 TimeOutConfig;		//��ʱ�������ע
EXTERN vu16 RunTime;		//ÿ��һ���жϼ�1,��������ʱ�ж�

EXTERN vu16  capture[2];//���벶׽ֵ
EXTERN vu16  pulse[2];//��׽��������
EXTERN vu16  CtrlOutBuffer[3];//���������
EXTERN FIR_ERR fir_err;
EXTERN u16	MC_SELECT;

#define ADC_BUF_MAX		0x20
EXTERN vu16 adc_cont;//��������
EXTERN vu16 u16_adc_buff[ADC_BUF_MAX];//���β������ݻ�����

EXTERN u16 u16_admux0_data[22]; 
EXTERN u16 u16_admux1_data[22]; 

extern void GlobalParaInit(void);
#endif