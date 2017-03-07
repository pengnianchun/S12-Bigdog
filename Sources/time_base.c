#include <MC9S12G128.h>   
#include "hal_system.h" 
#include "hal_pwm.h" 
#include "hal_int.h"
#include "hal_can.h" 
#include "hal_port.h" 
#include "protocol.h"

uint16_t  g_mea_fre=0, g_pulse_count=0;

void pulse_count(void) 
{
 g_pulse_count++;
}

void mea_fre_init(void)
{
g_mea_fre=0;
g_pulse_count=0;
 
}

void fre_200ms_process(void) 
{
 
 g_mea_fre=g_pulse_count*5; //频率获取到当前频率
 
 g_pulse_count=0;
}

/*更新指定位置*/
//==================================================================//
void Update_Out_Ctrl(void) 
{
 Ctrl_Out20=ID_6A4_data.front1.Bits.bit0;
}
//=================================================================//