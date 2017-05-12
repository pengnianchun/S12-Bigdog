
#include <MC9S12G128.h> 
#include <hidef.h>       
#include "hal_system.h"

void System_init(void)
{

	/* CPMUPROT: PROT=0 */
	CPMUPROT = 0x26U;                    /* Disable protection of clock configuration registers */
	/* CPMUCLKS: PSTP=0 */
	CPMUCLKS &= (unsigned char)~(unsigned char)CPMUCLKS_PSTP_MASK;                     
	/* CPMUCLKS: PLLSEL=1 */
	CPMUCLKS |= (unsigned char)CPMUCLKS_PLLSEL_MASK;    /* Enable the PLL to allow write to divider registers */
	/* CPMUREFDIV: REFFRQ1=0,REFFRQ0=1,REFDIV3=0,REFDIV2=0,REFDIV1=0,REFDIV0=1 */
	CPMUREFDIV_REFDIV = CLOCK_REFDIV;
	CPMUREFDIV_REFFRQ = 0X01; /* Set the divider register */                
	/* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=0,SYNDIV5=0,SYNDIV4=0,SYNDIV3=0,SYNDIV2=1,SYNDIV1=0,SYNDIV0=1 */
	CPMUSYNR_SYNDIV = CLOCK_SYNDIV; /* Set the multiplier register */
	/* CPMUPOSTDIV: POSTDIV4=0,POSTDIV3=0,POSTDIV2=0,POSTDIV1=0,POSTDIV0=0 */
	CPMUPOSTDIV = 0x00U;                 /* Set the post divider register */
	/* CPMUOSC: OSCE=1,OSCBW=0,OSCPINS_EN=0,OSCFILT=0 */
	CPMUOSC = 0x80U;                     /* Enable the oscillator */
	/* CPMUPLL: FM1=0,FM0=0 */
	CPMUPLL = 0x00U;                     /* Set the PLL frequency modulation */
	while(CPMUFLG_UPOSC == 0U) {         /* Wait until the oscillator is qualified by the PLL */
	}
	/* CPMUPROT: PROT=0 */
	CPMUPROT = 0x00U;                    /* Enable protection of clock configuration registers */  

}




void delay_1us(void)                 //1us延时函数 
  { 
   _FEED_COP(); 

  } 
  
void delay_nus(unsigned int n)       //N us延时函数 
  { 
   unsigned int nus_i=0; 
   for (nus_i=0;nus_i<n;nus_i++) 
   delay_1us(); 
  }  
	
void delay_1ms(void)                 //1ms延时函数 
  { 
   unsigned int ms_i; 
   for (ms_i=0;ms_i<1440;ms_i++) 
   {   
   _FEED_COP();
   
   }  
  } 
void delay_nms(unsigned int n)       //N ms延时函数 
  { 
   unsigned int nms_i=0; 
   for (nms_i=0;nms_i<n;nms_i++) 
   delay_1ms(); 
  }