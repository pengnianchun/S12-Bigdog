#define GLOBAL_EXTERN
#include <stdio.h>
#include "global.h"
//!<全局变量初始化函数
void GlobalParaInit(void)
{
	TimeOutConfig = 0;
	RunTime = 0;
	OnlineCheckConfig = 0;
	ExecutiveEraseFlashConfig = 0;
	adc_cont = 0;
	ms_1 = 0;
	ms_10=0;
	ms_100=0;
	adc_time=0;
	mode_addr_look = 0;
	mode_addr_error = 0;
	mode_addr_timeout = 0;
	memset(capture,0,sizeof(capture));
	memset(CtrlOutBuffer,0,sizeof(CtrlOutBuffer));
	memset(&fir_err,0,sizeof(FIR_ERR));
	wash_time = 300; //3秒
    wipe_int_time = 0;
    wipe_stop_time = 2000; //20秒
    memset(capture,0,sizeof(capture));
	memset(pulse,0,sizeof(pulse));
	memset(u16_admux_data,0,sizeof(u16_admux_data));
	admux0_cont=0;
	admux1_cont=0;
}


