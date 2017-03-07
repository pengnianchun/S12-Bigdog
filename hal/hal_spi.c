#include <MC9S12G128.h>   
#include "hal_system.h" 
#include "hal_spi.h" 

void  Spi_cs(uint8_t n) ;


void Hal_Spi_Init(void)

 {
 
  /* SPI1CR1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  SPI1CR1 = 0x00U;                     /* Disable the SPI1 module and clearing flags in SPISR register */
  /* SPI1CR2: XFRW=0,MODFEN=1,BIDIROE=0,SPISWAI=0,SPC0=0 */
  SPI1CR2 = 0x10U;                                      
  /* SPI1BR: SPPR2=1,SPPR1=0,SPPR0=0,SPR2=0,SPR1=1,SPR0=0 */
  SPI1BR = 0x42U;                                      
  /* SPI1CR1: SPIE=0,SPE=1,SPTIE=0,MSTR=1,CPOL=1,CPHA=0,SSOE=1,LSBFE=0 */
  SPI1CR1 = 0x5EU;                                      
  /* ### */
  /* Initial interrupt priority */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
 
   #if 0
 //===========================prot j=========================================//  
 
  /* ### Init_GPIO init code */
    /* Disable interrupts */
  /* PIEJ: PIEJ7=0,PIEJ6=0,PIEJ5=0,PIEJ4=0,PIEJ3=0,PIEJ2=0,PIEJ1=0,PIEJ0=0 */
  PIEJ = 0x00U;                                      
    /* Clear interrupt flags */
  /* PIFJ: PIFJ7=1,PIFJ6=1,PIFJ5=1,PIFJ4=1,PIFJ3=1,PIFJ2=1,PIFJ1=1,PIFJ0=1 */
  PIFJ = 0xFFU;                                      
  /* PPSJ: PPSJ5=0,PPSJ3=0,PPSJ2=0,PPSJ1=0,PPSJ0=0 */
  PPSJ &= (unsigned char)~(unsigned char)0x2FU;                     
  /* PERJ: PERJ5=1,PERJ3=1,PERJ2=1,PERJ1=1,PERJ0=1 */
  PERJ |= (unsigned char)0x2FU;                      
  /* DDRJ: DDRJ5=0,DDRJ3=1,DDRJ2=1,DDRJ1=1,DDRJ0=0 */
  DDRJ = (DDRJ & (unsigned char)~(unsigned char)0x21U) | (unsigned char)0x0EU;
  /* PIEJ: PIEJ7=0,PIEJ6=0,PIEJ5=1,PIEJ4=0,PIEJ3=0,PIEJ2=0,PIEJ1=0,PIEJ0=0 */
  
  //===========================prot b=========================================//  
   /* ### Init_GPIO init code */
  /* PUCR: PUPBE=1 */
  PUCR |= (unsigned char)0x02U;                      
  /* DDRB: DDRB1=1,DDRB0=1 */
  DDRB |= (unsigned char)0x03U;                      
  /* ### */
  
  Spi_cs(CS_OFF);
  #endif
 }
 
 void  Spi_cs(uint8_t n) 
 {
       if(n==0) 
       {
        SPI_CS0=0;
        SPI_CS1=1;
        SPI_CS2=1;
        }
       if(n==1) 
         {
       SPI_CS0=1;
       SPI_CS1=0;
       SPI_CS2=1;
         }
       if(n==2) 
         {
       SPI_CS0=1;
       SPI_CS1=1;
       SPI_CS2=0;
         }
       if(n==0xff) 
         {
       SPI_CS0=1;
       SPI_CS1=1;
       SPI_CS2=1;
         }
         
 }
 
 
 void SPI_byte_write(unsigned char data)
{

  SPI1DR = data;

  while(!(SPI1SR_SPIF));

  return;

  #if 0
	unsigned char localtemp = 0;

	MPSCK = 0;
	while(localtemp < 8)
	{
		if(data & 0b10000000)
		{
			MPMOSI = 1;
		}
		else
		{
			MPMOSI = 0;
		}
		delay_nus(1);
		MPSCK = 1;
		delay_nus(1);
		MPSCK = 0;
		data <<=1;
		localtemp++;
	}
	#endif 
}


unsigned char SPI_byte_read(void)
{
 
  while(!(SPI1SR_SPIF));

  return SPI1DR;

  #if 0
	unsigned char localtemp = 0;
	unsigned char data = 0;

	MPSCK = 0;
	while(localtemp < 7)
	{
		delay_nus(1);
		MPSCK = 1;
		if(MPMISO)
		{
			data += 1;
		}
		delay_nus(1);
		MPSCK = 0;
		data <<=1;
		localtemp++;
	}

	delay_nus(1);
	MPSCK = 1;
	if(MPMISO)
	{
		data += 1;
	}
	delay_nus(1);
	MPSCK = 0;

	return data;
	#endif
	
}