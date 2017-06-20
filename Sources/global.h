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
	int McErr1;
	int McErr2;
	int McErr3;
}
FIR_ERR;
#define PUSLE_SEVE_DATA_SIZE (10)

EXTERN vu8 TimeOutConfig;		//��ʱ�������ע
EXTERN vu16 RunTime;		//ÿ��һ���жϼ�1,��������ʱ�ж�

EXTERN vu16  capture[2];//���벶׽ֵ
EXTERN vu16  pulse[2][PUSLE_SEVE_DATA_SIZE];//��׽��������
EXTERN vu16  CtrlOutBuffer[3];//���������
EXTERN FIR_ERR fir_err;
EXTERN u16	MC_SELECT;
EXTERN u16 admux0_cont,admux1_cont;
#define ADC_BUF_MAX			0x20
#define ADC_CH_SIZE     	0x2C

EXTERN vu16 adc_cont;//��������
EXTERN vu16 u16_adc_buff[ADC_BUF_MAX];//���β������ݻ�����
//0��ַ���� 1��ʼΪ��������
EXTERN u8 u16_admux_data[ADC_CH_SIZE]; 

EXTERN char OnlineCheckConfig,ExecutiveEraseFlashConfig;

EXTERN u16 ms_1,ms_10,ms_100,adc_time;//��ѯ��ؼ�ʱ��

EXTERN int Select_addr;  
EXTERN u8 mode_addr_look;//ģ���ַ������־ 1��Ч;
EXTERN u8 mode_addr_error;//ģ���ַ��ͻ��־��
EXTERN u16 mode_addr_timeout;//ģ���ַ������ʱ��
EXTERN u16 mode_addr_err_timeout;

//!<ʱ��Ϊ10ms��
EXTERN unsigned int wash_time; //3��
EXTERN unsigned int wipe_int_time;
EXTERN unsigned int wipe_stop_time; //20��
EXTERN unsigned int wipe_wpp_time;//����ϵ��ӳ�ʱ�� 
extern void GlobalParaInit(void);
#endif