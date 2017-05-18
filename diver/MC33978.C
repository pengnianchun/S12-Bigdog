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

unsigned char mc33978_rtn[4];


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

