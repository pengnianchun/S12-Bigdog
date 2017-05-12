#include <MC9S12G128.h>   
#include "hal_system.h"
#include "hal_adc.h"

static uint8_t s_channel = 0;
void hal_adc_init(void)
{
	
	ATDCTL2 = 0x40;  //启动A/D模块,快速清零,禁止中断
	ATDCTL1_SRES=0;  //选用8位模数转换
	ATDCTL3 = 0x88;   //每次只转换一个通道
	ATDCTL4 = 0xE6;   //AD模块时钟频率为2MHz
	ATDDIEN=0xFFF;
	ATDDIENL_IEN0=0;
	ATDDIENH_IEN8=0;
	ATDCTL5 = 0x00;    //启动转换AD00
}
//修改通道不影响当次采集
void set_adc_ch(uint8_t ch)
{
	s_channel = ch;
}
uint8_t get_adc_ch(void)
{
	return s_channel;
}

uint16_t hal_read_adc(void)
{
    uint16_t ad;
	if(s_channel>12)
      return 0;
	//while(!ATDSTAT0_SCF);
	ad = ATDDR0L;
	ATDCTL5=s_channel;
	return ad;
}
 
