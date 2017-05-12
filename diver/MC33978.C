#include <MC9S12G128.h>   
#include "hal_system.h" 

#include "Hal_adc.h"
#include "Hal_spi.h"
#include "MC33978.h"
#include "global.h"
#include "protocol.h" 

/**
 * @file:  MC33978
 * @abstr: MC33978多路选择器驱动程序
 */
#define CMD_CHECK_SPI			0x00
#define MC_TIMEOUT				50000

static unsigned char mc33978_rtn[4];


       
volatile SW_STATUS s_input;

void ChipSelect(void)
{
	switch(MC_SELECT)
	{
		case 0:
			SPI_CS0=0;SPI_CS1=1;SPI_CS2=1;
			break;
		case 1:
			SPI_CS0=1;SPI_CS1=0;SPI_CS2=1;
			break;
		case 2:
			SPI_CS0=1;SPI_CS1=1;SPI_CS2=0;
			break;
		default:
			SPI_CS0=1;SPI_CS1=1;SPI_CS2=1;
			break;
	}
}
void ChipCancel(void)
{
	SPI_CS0=1;SPI_CS1=1;SPI_CS2=1;
}
void mc33978_write(unsigned char cmd, unsigned char config1, unsigned char config2, unsigned char config3) {
    ChipSelect();
    mc33978_rtn[0] = SPI_Byte(cmd);
    mc33978_rtn[1] = SPI_Byte(config1);
    mc33978_rtn[2] = SPI_Byte(config2);
    mc33978_rtn[3] = SPI_Byte(config3);
    ChipCancel();
}


ERROR_TYPEDEF CheckSpi(void)
{
	
    mc33978_write(0x0, 0, 0, 0);
    mc33978_write(0x0, 0, 0, 0);
	if ((mc33978_rtn[0] == 0x00)&&(mc33978_rtn[1] == 0x12)&&(mc33978_rtn[2] == 0x34)&&(mc33978_rtn[3] == 0x56))
	{
		return OK;
	}
	else
	{
		return ERROR_MC33978;
	}
}
/**
 * 调用前需要先选择芯片
 */
ERROR_TYPEDEF mc33978_Input_Init(void) 
{
	u16 timeout;
	ERROR_TYPEDEF err;
	timeout = RunTime;
	do{
	  	if ((RunTime - timeout) >= MC_TIMEOUT)
	  	{
			return ERROR_TIMEOUT;
	  	} 	
  		err = CheckSpi();
  	}while(err != OK);
	mc33978_write(0x49, 0, 0, 0);
    delay_nus(100);
	//DeviceConfiguration
    mc33978_write(0x03, 0, 0x00, 0x00); //SP0-BAT SP1-7=GND

    //Tri-State SP Register
    mc33978_write(0x05, 0, 0, 0x00); //
    //Tri-State SG Register
    mc33978_write(0x07, 0x00, 0x00, 0x00); //0x2D,SG13,SG11,SG10,SG8=1;0x20 SG5=1;  ; 

    //Wetting Current Level SP Register
    mc33978_write(0x09, 0, 0, 0); //SP0-7 2mA

    //Wetting Current Level SG Register 0
    mc33978_write(0x0B, 0, 0, 0); //SG0-7 2mA

    //Wetting Current Level SG Register 1
    mc33978_write(0x0D, 0, 0, 0); //SG8-13 2mA

    //Continuous Wetting Current SP Register
    mc33978_write(0x17, 0, 0, 0x00); //SP0-7 脉冲

    //Continuous Wetting Current SG Register
    mc33978_write(0x19, 0, 0x00, 0x00); //SG0-13 脉冲 

    //Interrupt Enable SP Register
    mc33978_write(0x1B, 0, 0, 0x00);

    //Interrupt Enable SG Register
    mc33978_write(0x1D, 0, 0x00, 0x00);

    //Low Power Mode Configuration Register 
    mc33978_write(0x1F, 0, 0, 0); //poll 3ms

    //Wake-up Enable SP Register 
    mc33978_write(0x21, 0, 0, 0x00);

    //Wake-up Enable SG Register 
    mc33978_write(0x21, 0, 0x00, 0x00);

    // Polling Current Configuration SP Register
    mc33978_write(0x2D, 0, 0x00, 0x00);
    //Polling Current Configuration SG Register  
    mc33978_write(0x2F, 0, 0x00, 0x00);
	return OK;
}
ERROR_TYPEDEF mc33978_Adc_Init(void) 
{
	u16 timeout;
	ERROR_TYPEDEF err;
	timeout = RunTime;
	do{
		if ((RunTime - timeout) >= MC_TIMEOUT)
		{
			return ERROR_TIMEOUT;
		}	
		err = CheckSpi();
	}while(err != OK);
	mc33978_write(0x49, 0, 0, 0);
	delay_nus(100);
	//DeviceConfiguration
	mc33978_write(0x03, 0, 0x00, 0x00); //SP0-BAT SP1-7=GND

	//Tri-State SP Register
	mc33978_write(0x05, 0, 0, 0xFF); //
	//Tri-State SG Register
	mc33978_write(0x07, 0x00, 0xFF, 0xFF); //0x2D,SG13,SG11,SG10,SG8=1;0x20 SG5=1;	; 

	//Wetting Current Level SP Register
	mc33978_write(0x09, 0, 0, 0); //SP0-7 2mA

	//Wetting Current Level SG Register 0
	mc33978_write(0x0B, 0, 0, 0); //SG0-7 2mA

	//Wetting Current Level SG Register 1
	mc33978_write(0x0D, 0, 0, 0); //SG8-13 2mA

	//Continuous Wetting Current SP Register
	mc33978_write(0x17, 0, 0, 0x00); //SP0-7 脉冲

	//Continuous Wetting Current SG Register
	mc33978_write(0x19, 0, 0x00, 0x00); //SG0-13 脉冲 

	//Interrupt Enable SP Register
	mc33978_write(0x1B, 0, 0, 0x00);

	//Interrupt Enable SG Register
	mc33978_write(0x1D, 0, 0x00, 0x00);

	//Low Power Mode Configuration Register 
	mc33978_write(0x1F, 0, 0, 0); //poll 3ms

	//Wake-up Enable SP Register 
	mc33978_write(0x21, 0, 0, 0x00);

	//Wake-up Enable SG Register 
	mc33978_write(0x21, 0, 0x00, 0x00);

	// Polling Current Configuration SP Register
	mc33978_write(0x2D, 0, 0x00, 0x00);
	//Polling Current Configuration SG Register  
	mc33978_write(0x2F, 0, 0x00, 0x00);
	//AMUX Control Register
	mc33978_write(0x3B, 0x00, 0x00, 0x01);
	return OK;
}

//void mc33978_DeviceConfiguration(unsigned char mode=0x01);

void mc33978_DeviceConfiguration(unsigned char mode) {
    //DeviceConfiguration
    mc33978_write(0x03, 0, 0x00, mode); //SP0-BAT SP1-7=GND
}

void mc33978_AMUX(unsigned char chs) {
    //AMUX Control Register
    chs = chs & 0x3f;
    mc33978_write(0x3B, 0x00, 0x00, chs);
}
#define IN_KL1			(s_input.BITS.SP0)
#define IN_KL2			(s_input.BITS.SP1)
#define IN_KL3			(s_input.BITS.SP2)
#define IN_KL4			(s_input.BITS.SP3)
#define IN_KL20			(s_input.BITS.SP4)
#define IN_KL19			(s_input.BITS.SP5)
#define IN_KL21			(s_input.BITS.SP6)
#define IN_KL22         (s_input.BITS.SP7)
#define IN_KL5			(s_input.BITS.SG0)
#define IN_KL6			(s_input.BITS.SG1)
#define IN_KL7			(s_input.BITS.SG2)
#define IN_KL8			(s_input.BITS.SG3)
#define IN_KL9			(s_input.BITS.SG4)
#define IN_KL10			(s_input.BITS.SG5)
#define IN_KL11			(s_input.BITS.SG6)
#define IN_KL12			(s_input.BITS.SG7)
#define IN_KL15			(s_input.BITS.SG8)
#define IN_KL14			(s_input.BITS.SG9)
#define IN_KL13			(s_input.BITS.SG10)
#define IN_KL18			(s_input.BITS.SG11)
#define IN_KL17			(s_input.BITS.SG12)
#define IN_KL16			(s_input.BITS.SG13)

void mc33978_ReadSwtichStatus(void) {
	SELECT_INPUT_MC();
    mc33978_write(0x3E, 0, 0, 0);
    mc33978_write(0x3E, 0, 0, 0);

    if (mc33978_rtn[0] == 0x3E) {
        s_input.BYTES[0] = mc33978_rtn[3];
        s_input.BYTES[1] = mc33978_rtn[2];
        s_input.BYTES[2] = mc33978_rtn[1];

		ID_681_data.input1.Bits.bit0 = IN_KL1;
		ID_681_data.input1.Bits.bit1 = IN_KL2;
		ID_681_data.input1.Bits.bit2 = IN_KL3;
		ID_681_data.input1.Bits.bit3 = IN_KL4;
		ID_681_data.input1.Bits.bit4 = IN_KL5;
		ID_681_data.input1.Bits.bit5 = IN_KL6;
		ID_681_data.input1.Bits.bit6 = IN_KL7;
		ID_681_data.input1.Bits.bit7 = IN_KL8;

		ID_681_data.input2.Bits.bit0 = IN_KL9;
		ID_681_data.input2.Bits.bit1 = IN_KL10;
		ID_681_data.input2.Bits.bit2 = IN_KL11;
		ID_681_data.input2.Bits.bit3 = IN_KL12;
		ID_681_data.input2.Bits.bit4 = IN_KL13;
		ID_681_data.input2.Bits.bit5 = IN_KL14;
		ID_681_data.input2.Bits.bit6 = IN_KL15;
		ID_681_data.input2.Bits.bit7 = IN_KL16;
        
    }
}
//=======================================================
void GetInputStatus(void)
{
	SELECT_INPUT_MC();
	mc33978_ReadSwtichStatus();
}

#define AD_CH_GS0    0x01
#define AD_CH_GS1    0x02
#define AD_CH_GS2    0x03
#define AD_CH_GS3    0x04
#define AD_CH_GS4    0x05
#define AD_CH_GS5    0x06
#define AD_CH_GS6    0x07
#define AD_CH_GS7    0x08
#define AD_CH_GS8    0x09
#define AD_CH_GS9    0x0A
#define AD_CH_GS10   0x0B
#define AD_CH_GS11   0x0C
#define AD_CH_GS12   0x0D
#define AD_CH_GS13   0x0E

#define AD_CH_SP0    0x0F
#define AD_CH_SP1    0x10
#define AD_CH_SP2    0x11
#define AD_CH_SP3    0x12
#define AD_CH_SP4    0x13
#define AD_CH_SP5    0x14
#define AD_CH_SP6    0x15
#define AD_CH_SP7    0x16
#if 1
const u8 ADMUX0_CH[]={
                      AD_CH_GS0,AD_CH_GS1,AD_CH_GS2,AD_CH_GS3,AD_CH_GS4,
					  AD_CH_GS5,AD_CH_GS6,AD_CH_GS7,AD_CH_GS8,AD_CH_GS9,
					  AD_CH_GS10,AD_CH_GS11,AD_CH_GS12,AD_CH_GS13,
					  AD_CH_SP0,AD_CH_SP1,AD_CH_SP2,AD_CH_SP3,AD_CH_SP6,AD_CH_SP7,
                      };
const u8 ADMUX1_CH[]={
                      AD_CH_GS0,AD_CH_GS1,AD_CH_GS2,AD_CH_GS3,AD_CH_GS4,
					  AD_CH_GS5,AD_CH_GS6,AD_CH_GS7,AD_CH_GS8,AD_CH_GS9,
					  AD_CH_GS10,AD_CH_GS11,AD_CH_GS12,AD_CH_GS13,AD_CH_SP0,
					  AD_CH_SP1,AD_CH_SP2,AD_CH_SP3,AD_CH_SP4,AD_CH_SP5,
					  AD_CH_SP6,AD_CH_SP7,
                      };
#else
const u8 ADMUX0_CH[] = {AD_CH_SP0};
const u8 ADMUX1_CH[] = {AD_CH_SP0};

#endif
u16 admux0_cont=0,admux1_cont=0;
/**
 * 俩路信号交替采样
 * 描述:选择下次采样通道->获取adc值,此时ad在采样另一通ad值->获取ad值填充到对应位置
 */
void GetAdcData(void)
{
	u8 ch,i;
	u32 temp = 0;
	ch = get_adc_ch();
	if (admux0_cont >= sizeof(ADMUX0_CH))
	{
		//异常情况程序正常不会进入
		admux0_cont = 0;
	}
	if(admux1_cont >= sizeof(ADMUX1_CH))
	{
		//异常情况程序正常不会进入
		admux1_cont = 0;
	}
	if (ADMUX_CH0 == ch)
	{
		
		if (adc_cont > 1)
		{
			set_adc_ch(ADMUX_CH1);
			hal_read_adc();
			temp = 0;
			for(i = 1;i<adc_cont;i++)
			{
				temp = temp + u16_adc_buff[i];
			}
			//adc_cont不会等0 不会出现除零异常
			temp = temp/(adc_cont - 1);
			adc_cont = 0;
			u16_admux0_data[admux0_cont] = (u16)temp;
			
			if (++admux0_cont>=sizeof(ADMUX0_CH))
			{
				admux0_cont = 0;
			}
			SELECT_ADC0_MC();
			mc33978_AMUX(ADMUX0_CH[admux0_cont]);
		}
	}
	else if(ADMUX_CH1 == ch)
	{
		if (adc_cont > 1){
			set_adc_ch(ADMUX_CH0);
			hal_read_adc();
			temp = 0;
			for(i = 1;i<adc_cont;i++)
			{
				temp = temp + u16_adc_buff[i];
			}
			//adc_cont不会等0 不会出现除零异常
			temp = temp/(adc_cont-1);
			u16_admux1_data[admux1_cont] = (u16)temp;
			adc_cont = 0;
			if (++admux1_cont>=sizeof(ADMUX1_CH))
			{
				admux1_cont = 0;
			}
			
			SELECT_ADC1_MC();
			mc33978_AMUX(ADMUX1_CH[admux1_cont]);
		}
	}
	else
	{
		set_adc_ch(ADMUX_CH1);
		hal_read_adc();//丢弃本次采样
		adc_cont = 0;
	}
}

