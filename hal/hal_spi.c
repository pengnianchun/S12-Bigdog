#include <MC9S12G128.h>   
#include "hal_system.h" 
#include "hal_spi.h" 

#if (CLOCK_BUS != 24000000)
#error("ʱ�Ӳ�ƥ����Ҫ�������üĴ���");
#endif
/**
 * @file  :spi�ײ���������
 * @abstr :����λ����Ƶ����� 4MHz;
 */
 #if 0
 void Hal_Spi_Init(void)
 {
  /* �˿��������״̬�趨  */
  DDRJ_DDRJ0 = 0;
  DDRJ_DDRJ1 = 1;
  DDRJ_DDRJ2 = 1;
  DDRJ_DDRJ3 = 1;
  DDRAB_DDRB7 = 1;
  DDRAB_DDRB1 = 1;
  
 }
/*************************************************************/
/*                      SPI��дһ���ֽ�                      */
/*************************************************************/
u8 SPI_Byte(byte value)
{                        
	unsigned char localtemp = 0;
	unsigned char data = 0;
	MPMOSI = 0;
	MPSCK = 0;
	while(localtemp < 8)
	{
		data <<=1;
		if(value & 0x80)
		{
			MPMOSI = 1;
		}
		else
		{
			MPMOSI = 0;
		}
		delay_nus(100);
		MPSCK = 1;
		delay_nus(100);
		if(MPMISO)
		{
			data += 1;
		}
		
		MPSCK = 0;
		value <<=1;
		
		localtemp++;
	}
	return data;
}

#else
void Hal_Spi_Init(void)

 {
  /* �˿��������״̬�趨  */
  DDRJ_DDRJ0 = 0;
  DDRJ_DDRJ1 = 1;
  DDRJ_DDRJ2 = 1;
  DDRJ_DDRJ3 = 1;
  DDRAB_DDRB7 = 1;
  DDRAB_DDRB1 = 1;
  /* SPI1CR1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  SPI1CR1 = 0x00U;                     /* Disable the SPI1 module and clearing flags in SPISR register */
  /* SPI1CR2: XFRW=0,MODFEN=1,BIDIROE=0,SPISWAI=0,SPC0=0 */
  SPI1CR2 = 0x00U;                                      
  /* SPI1BR: SPPR2=1,SPPR1=0,SPPR0=0,SPR2=0,SPR1=1,SPR0=0 */
  SPI1BR = 0x44U;             //�����ʲ�������߷��߻��������                         
  /* SPI1CR1: SPIE=0,SPE=1,SPTIE=0,MSTR=1,CPOL=1,CPHA=0,SSOE=1,LSBFE=0 */
  SPI1CR1 = 0x50;       //    SSOE��Ҫ���ó�0 ����PJ2�޷����õ�ƽ                           
  /* ### */
  /* Initial interrupt priority */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
 }
 
 
 void SPI_byte_write(unsigned char data)
{
  SPI1DR = data;
  while(!(SPI1SR_SPIF));
  return;
}

unsigned int SPI_byte_read(void)
{
 
  while(!(SPI1SR_SPIF));
  return SPI1DR;
	
}
u8 SPI_Byte(byte value)
{
  	while(!(SPI1SR_SPTEF));
	SPI1DR = value;
	while(!(SPI1SR_SPIF));
  	return SPI1DRL;
}
#endif