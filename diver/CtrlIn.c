#include "mcuinit.h"
#include "ctrlin.h"
#include "MC33978.h"


#define IN_KL01			(s_input.BITS.SP0)
#define IN_KL02			(s_input.BITS.SP1)
#define IN_KL03			(s_input.BITS.SP2)
#define IN_KL04			(s_input.BITS.SP3)
#define IN_KL20			(s_input.BITS.SP4)
#define IN_KL19			(s_input.BITS.SP5)
#define IN_KL21			(s_input.BITS.SP6)
#define IN_KL22         (s_input.BITS.SP7)
#define IN_KL05			(s_input.BITS.SG0)
#define IN_KL06			(s_input.BITS.SG1)
#define IN_KL07			(s_input.BITS.SG2)
#define IN_KL08			(s_input.BITS.SG3)
#define IN_KL09			(s_input.BITS.SG4)
#define IN_KL10			(s_input.BITS.SG5)
#define IN_KL11			(s_input.BITS.SG6)
#define IN_KL12			(s_input.BITS.SG7)
#define IN_KL15			(s_input.BITS.SG8)
#define IN_KL14			(s_input.BITS.SG9)
#define IN_KL13			(s_input.BITS.SG10)
#define IN_KL18			(s_input.BITS.SG11)
#define IN_KL17			(s_input.BITS.SG12)
#define IN_KL16			(s_input.BITS.SG13)

volatile SW_STATUS s_input;


void GetInput(void)
{
	u8 i;
	
	SELECT_INPUT_MC();
	mc33978_write(0x3E, 0, 0, 0);
	mc33978_write(0x3E, 0, 0, 0);

	if (mc33978_rtn[0] == 0x3E) {
		s_input.BYTES[0] = mc33978_rtn[3];
		s_input.BYTES[1] = mc33978_rtn[2];
		s_input.BYTES[2] = mc33978_rtn[1];

		ID_70x_data.input1.Bits.bit0 = IN_KL01;
		ID_70x_data.input1.Bits.bit1 = IN_KL02;
		ID_70x_data.input1.Bits.bit2 = IN_KL03;
		ID_70x_data.input1.Bits.bit3 = IN_KL04;
		ID_70x_data.input1.Bits.bit4 = IN_KL05;
		ID_70x_data.input1.Bits.bit5 = IN_KL06;
		ID_70x_data.input1.Bits.bit6 = IN_KL07;
		ID_70x_data.input1.Bits.bit7 = IN_KL08;

		ID_70x_data.input2.Bits.bit0 = IN_KL09;
		ID_70x_data.input2.Bits.bit1 = IN_KL10;
		ID_70x_data.input2.Bits.bit2 = IN_KL11;
		ID_70x_data.input2.Bits.bit3 = IN_KL12;
		ID_70x_data.input2.Bits.bit4 = IN_KL13;
		ID_70x_data.input2.Bits.bit5 = IN_KL14;
		ID_70x_data.input2.Bits.bit6 = IN_KL15;
		ID_70x_data.input2.Bits.bit7 = IN_KL16;
		
	}
	
}
void GetPer(void)
{
	u16 temp[2];
	int i;
	temp[0] = 0;
	temp[1] = 0;
	for(i=0;i<PUSLE_SEVE_DATA_SIZE;i++)
	{
		temp[0] += pulse[0][i];
		temp[1] += pulse[1][i];
	}
	ID_70x_data.per1[0] += temp[0]&0xFF;
	ID_70x_data.per1[1] += (temp[0]>>8)&0xFF;
	ID_70x_data.per2[0] += temp[1]&0xFF;
	ID_70x_data.per2[1] += (temp[1]>>8)&0xFF;
}

u16 admux0_cont=0,admux1_cont=0;
const u8 ADMUX0_CH[]={ 
                       1, 2, 3, 4, 0, 0,28,23,
                      34,33,21,22,27,32,31,36,30,29,35,25,26,24,
                      };
const u8 ADMUX1_CH[]={
	                  38,39,42,40,17,15,12,20,
					  41,43,14,19, 7, 6,11,16, 9,18, 5,13,10, 8,
                      };
/**
 * 俩路信号交替采样
 * 描述:选择下次采样通道->获取adc值,此时ad在采样另一通ad值->获取ad值填充到对应位置
 */
void GetAdcsingleData(U8 next_ch,u16 *cont,u8 *addr_arr)
{
	U8 i;
	u32 temp = 0;
	if (adc_cont > 1)
	{
		set_adc_ch(next_ch);
		(void)hal_read_adc();
		for(i = 1;i<adc_cont;i++)
		{
			temp = temp + u16_adc_buff[i];
		}
		temp = temp/(adc_cont - 1);
		adc_cont = 0;
		u16_admux_data[addr_arr[*cont]] = (u8)temp;
		if (++(*cont)>=ADC_CH_SIGN_SIZE)
		{
			  *cont = 0;
		}
		SELECT_ADC0_MC();
		mc33978_AMUX(*cont+1);
	}
}
void GetAdcData(void)
{
  u8 ch,i;
  u32 temp = 0;
  ch = get_adc_ch();
  if (admux0_cont >= ADC_CH_SIGN_SIZE)
  {
	  //异常情况程序正常不会进入
	  admux0_cont = 0;
  }
  if(admux1_cont >= ADC_CH_SIGN_SIZE)
  {
	  //异常情况程序正常不会进入
	  admux1_cont = 0;
  }
  
  if (ADMUX_CH0 == ch)
  {
	  
	  GetAdcsingleData(ADMUX_CH1,&admux0_cont,ADMUX0_CH);
  }
  else if(ADMUX_CH1 == ch)
  {
	  GetAdcsingleData(ADMUX_CH0,&admux1_cont,ADMUX1_CH);

  }
  else
  {
	  set_adc_ch(ADMUX_CH1);
	  (void)hal_read_adc();//丢弃本次采样
	  adc_cont = 0;
  }
}



