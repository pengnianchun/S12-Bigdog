#define GLOBAL_EXTERN
#include <stdio.h>
#include "global.h"
//!<ȫ�ֱ�����ʼ������
void GlobalParaInit(void)
{
	TimeOutConfig = 0;
	RunTime = 0;
	memset(capture,0,sizeof(capture));
	memset(CtrlOutBuffer,0,sizeof(CtrlOutBuffer));
	memset(&fir_err,0,sizeof(FIR_ERR));
}


