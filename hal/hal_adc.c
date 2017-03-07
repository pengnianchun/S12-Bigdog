#include <MC9S12G128.h>   
#include "hal_system.h"

void hal_adc_init(void)
{
	
	ATDCTL1=0x00;   
	ATDCTL2=0x40;   
	ATDCTL3=0xc0;   
	ATDCTL4=0x01;   
	ATDCTL5=0x00;    
	ATDDIENL=0xFEFD;    //打开管脚
	
}

 
uint16_t hal_read_adc(uint8_t ch)
{
	uint16_t ad[16],i;    
  uint16_t sum=0;
  
	if(ch>16)
  return 0;
	
	ATDCTL5=0x20|ch;
	
	for(i=0;i<10;i++)
	 {
	  
	
	while(ATDSTAT0_SCF == 0); //等待转换完成
   	
	ad[0]=ATDDR0;
	ad[1]=ATDDR1;
	ad[2]=ATDDR2;
	ad[3]=ATDDR3;
	ad[4]=ATDDR4;
	ad[5]=ATDDR5;
	ad[6]=ATDDR6;
  ad[7]=ATDDR7;
  sum+=(ad[0]+ad[1]+ad[2]+ad[3]+ad[4]+ad[5]+ad[6]+ad[7])/8;
	 }
	 
	sum=sum/10;	
	return sum;
	
}
 
