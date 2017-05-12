#include <MC9S12G128.h>   
#include "hal_system.h"
#include "hal_adc.h"

static uint8_t s_channel = 0;
void hal_adc_init(void)
{
	
	ATDCTL2 = 0x40;  //����A/Dģ��,��������,��ֹ�ж�
	ATDCTL1_SRES=0;  //ѡ��8λģ��ת��
	ATDCTL3 = 0x88;   //ÿ��ֻת��һ��ͨ��
	ATDCTL4 = 0xE6;   //ADģ��ʱ��Ƶ��Ϊ2MHz
	ATDDIEN=0xFFF;
	ATDDIENL_IEN0=0;
	ATDDIENH_IEN8=0;
	ATDCTL5 = 0x00;    //����ת��AD00
}
//�޸�ͨ����Ӱ�쵱�βɼ�
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
 
