#include <MC9S12G128.h> 
#include <hidef.h> 
#include "MCUinit.h"
extern void near _Startup(void);

#pragma CODE_SEG __NEAR_SEG NON_BANKED

static void MCU_init_reset(void);
/*
** ===================================================================
**     Method      :  MCU_init_reset (component MC9S12G128_100)
**
**     Description :
**         Device initialization code for after reset initialization.
** ===================================================================
*/


static void MCU_init_reset(void)
{

  /*  Initialization of memory configuration */
  /* MMCCTL1: NVMRES=0 */
  MMCCTL1 = 0x00U;                                      
  /* PKGCR: APICLKS7=0,PKGCR2=1,PKGCR1=1,PKGCR0=0 */
  PKGCR = 0x06U;                                      
  /* DIRECT: DP15=0,DP14=0,DP13=0,DP12=0,DP11=0,DP10=0,DP9=0,DP8=0 */
  DIRECT = 0x00U;                                      
  /* IVBR: IVB_ADDR=0xFF */
  IVBR = 0xFFU;                                      
  /* ECLKCTL: NECLK=1,NCLKX2=1,DIV16=0,EDIV4=0,EDIV3=0,EDIV2=0,EDIV1=0,EDIV0=0 */
  ECLKCTL = 0xC0U;                                      
  /* Jump to the default entry point */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  asm jmp _Startup;
  /*lint -restore Enable MISRA rule (1.1) checking. */
} /*MCU_init*/

/*
** ===================================================================
**     Interrupt handler : isr_default
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__interrupt void isr_default(void)
{
  /* Write your interrupt code here ... */

}
/* end of isr_default */

/* Interrupt vector table */

     
#pragma CODE_SEG __NEAR_SEG NON_BANKED
/*
** ===================================================================
**     Interrupt handler : isrVapi
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

__interrupt void isrVapi(void)
{
	CPMUAPICTL_APIF=1;
}
/* end of isrVapi */

__interrupt void isrVcanrx(void)
{
  hal_can_receive();
  CANRFLG = 0x01;   /* Clear RXF */ 
}
/* end of isrVcanrx */

/*
** ===================================================================
**     Interrupt handler : isrVportj
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__interrupt void isrVportj(void)
{
  /* Write your interrupt code here ... */
  PIFJ_PIFJ5=1;
}
/*
** ===================================================================
**     Interrupt handler : isrVtimch0
**
**     Description :
**     	    通道0输入捕捉                             . 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
vu16  pulse_temp[2];//捕捉的脉冲数
__interrupt void ivVtimch0(void)
{
	static unsigned int cont0;
    unsigned int temp;
    temp = TC0;
    capture[0] = temp - cont0;
	pulse_temp[0]++;
    cont0 = temp;
	if(TFLG1_C0F == 1)
	{
	    TFLG1_C0F = 1;
	}
}
/* end of isrVtimch0 */
/*
** ===================================================================
**     Interrupt handler : isrVtimch1
**
**     Description :
**     		通道1输入捕捉                             . 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__interrupt void ivVtimch1(void)
{
  static unsigned int cont1;
  unsigned int temp;
  temp = TC1;
  capture[1] = temp - cont1;
  pulse_temp [1]++;
  cont1 = temp;
  if(TFLG1_C1F == 1)
  {
    TFLG1_C1F = 1;
  }
}
/* end of isrVtimch1 */
/*
** ===================================================================
**     Interrupt handler : isrVtimch2
**
**     Description :
**     		完成定时任务. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
static vu8 s_pulse_cont;
__interrupt void ivVtimch2(void)
{
	static u16 cont = 0;;
	cont++;
	
	if(cont>10000){
	  cont = 0;
	  s_pulse_cont ++;
	  if(s_pulse_cont>=PUSLE_SEVE_DATA_SIZE)
	  {
	  	s_pulse_cont = 0;
	  }
	  pulse[0][s_pulse_cont] = pulse_temp[0];
	  pulse[1][s_pulse_cont] = pulse_temp[1];
	  pulse_temp[0] = pulse_temp[1] = 0;
	}
  
  if(TFLG1_C2F == 1)
  {
    TFLG1_C2F = 1;
    TC2 = TCNT + ECT_TC1_IDX;         //设置输出比较时间为0.0001s
  }
  TimeOutConfig = 1;
  RunTime++;
  
}
/* end of isrVtimch2 */

 #pragma CODE_SEG DEFAULT

/* ISR prototype */
typedef void (*near tIsrFunc)(void);

#ifndef UNASSIGNED_ISR
  #define UNASSIGNED_ISR isr_default   /* unassigned interrupt service routine */
#endif
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static const tIsrFunc _InterruptVectorTable[]  @0xFF80U= { /* Interrupt vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* ISR name                               No.  Address  Name          Description */
  &UNASSIGNED_ISR,                      /* 0x40  0xFF80   ivVsi         unused by PE */
  &UNASSIGNED_ISR,                      /* 0x41  0xFF82   ivVportad     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x42  0xFF84   ivVatdcompare unused by PE */
  &UNASSIGNED_ISR,                      /* 0x43  0xFF86   ivVReserved60 unused by PE */
  &isrVapi,                             /* 0x44  0xFF88   ivVapi        unused by PE */
  &UNASSIGNED_ISR,                      /* 0x45  0xFF8A   ivVlvi        unused by PE */
  &UNASSIGNED_ISR,                      /* 0x46  0xFF8C   ivVReserved57 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x47  0xFF8E   ivVportp      unused by PE */
  &UNASSIGNED_ISR,                      /* 0x48  0xFF90   ivVReserved55 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x49  0xFF92   ivVReserved54 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x4A  0xFF94   ivVReserved53 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x4B  0xFF96   ivVReserved52 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x4C  0xFF98   ivVReserved51 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x4D  0xFF9A   ivVReserved50 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x4E  0xFF9C   ivVReserved49 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x4F  0xFF9E   ivVReserved48 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x50  0xFFA0   ivVReserved47 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x51  0xFFA2   ivVReserved46 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x52  0xFFA4   ivVReserved45 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x53  0xFFA6   ivVReserved44 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x54  0xFFA8   ivVReserved43 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x55  0xFFAA   ivVReserved42 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x56  0xFFAC   ivVReserved41 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x57  0xFFAE   ivVReserved40 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x58  0xFFB0   ivVcantx      unused by PE */
  &isrVcanrx,                           /* 0x59  0xFFB2   ivVcanrx      unused by PE */
  &UNASSIGNED_ISR,                      /* 0x5A  0xFFB4   ivVcanerr     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x5B  0xFFB6   ivVcanwkup    unused by PE */
  &UNASSIGNED_ISR,                      /* 0x5C  0xFFB8   ivVflash      unused by PE */
  &UNASSIGNED_ISR,                      /* 0x5D  0xFFBA   ivVflashfd    unused by PE */
  &UNASSIGNED_ISR,                      /* 0x5E  0xFFBC   ivVspi2       unused by PE */
  &UNASSIGNED_ISR,                      /* 0x5F  0xFFBE   ivVspi1       unused by PE */
  &UNASSIGNED_ISR,                      /* 0x60  0xFFC0   ivVReserved31 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x61  0xFFC2   ivVsci2       unused by PE */
  &UNASSIGNED_ISR,                      /* 0x62  0xFFC4   ivVReserved29 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x63  0xFFC6   ivVcpmuplllck unused by PE */
  &UNASSIGNED_ISR,                      /* 0x64  0xFFC8   ivVcpmuocsns  unused by PE */
  &UNASSIGNED_ISR,                      /* 0x65  0xFFCA   ivVReserved26 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x66  0xFFCC   ivVReserved25 unused by PE */
  &isrVportj,                           /* 0x67  0xFFCE   ivVportj      unused by PE */
  &UNASSIGNED_ISR,                      /* 0x68  0xFFD0   ivVReserved23 unused by PE */
  &UNASSIGNED_ISR,                      /* 0x69  0xFFD2   ivVatd        unused by PE */
  &UNASSIGNED_ISR,                      /* 0x6A  0xFFD4   ivVsci1       unused by PE */
  &UNASSIGNED_ISR,                      /* 0x6B  0xFFD6   ivVsci0       unused by PE */
  &UNASSIGNED_ISR,                      /* 0x6C  0xFFD8   ivVspi0       unused by PE */
  &UNASSIGNED_ISR,                      /* 0x6D  0xFFDA   ivVtimpaie    unused by PE */
  &UNASSIGNED_ISR,                      /* 0x6E  0xFFDC   ivVtimpaaovf  unused by PE */
  &UNASSIGNED_ISR,                      /* 0x6F  0xFFDE   ivVtimovf     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x70  0xFFE0   ivVtimch7     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x71  0xFFE2   ivVtimch6     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x72  0xFFE4   ivVtimch5     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x73  0xFFE6   ivVtimch4     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x74  0xFFE8   ivVtimch3     unused by PE */
  &ivVtimch2,                           /* 0x75  0xFFEA   ivVtimch2     unused by PE */
  &ivVtimch1,                           /* 0x76  0xFFEC   ivVtimch1     unused by PE */
  &ivVtimch0,                           /* 0x77  0xFFEE   ivVtimch0     unused by PE */
  &UNASSIGNED_ISR,                      /* 0x78  0xFFF0   ivVrti        unused by PE */
  &UNASSIGNED_ISR,                      /* 0x79  0xFFF2   ivVirq        unused by PE */
  &UNASSIGNED_ISR,                      /* 0x7A  0xFFF4   ivVxirq       unused by PE */
  &UNASSIGNED_ISR,                      /* 0x7B  0xFFF6   ivVswi        unused by PE */
  &UNASSIGNED_ISR,                       /* 0x7C  0xFFF8   ivVtrap       unused by PE */
  &MCU_init_reset,                      /* 0xFFFA  ivVcop         unused by PE */
  &MCU_init_reset,                      /* 0xFFFC  ivVclkmon      unused by PE */
  &MCU_init_reset                       /* 0xFFFE  ivVreset       used by PE */
};



#pragma CODE_SEG DEFAULT
#pragma MESSAGE DISABLE C12056

void hal_irq_init(void) 
{
  
/* ### Init_IRQ init code */
  /* IRQCR: IRQE=1,IRQEN=1 */
  DisableInterrupts ;
  PIEJ = 0x20U;                                      
  EnableInterrupts;
                                        
  /* ### */
}
void hal_api_init(void) 
{
  
  /* ### Init_API init code */
  /* CPMUAPICTL: APICLK=0,APIES=0,APIEA=0,APIFE=0,APIE=0,APIF=0 */
  CPMUAPICTL = 0x00U;                                      
  /* CPMUAPIR: APIR15=1,APIR14=1,APIR13=1,APIR12=0,APIR11=1,APIR10=0,APIR9=1,APIR8=0,APIR7=0,APIR6=1,APIR5=1,APIR4=0,APIR3=0,APIR2=0,APIR1=0,APIR0=0 */
  CPMUAPIR = 0xEA60U;                            
  /* CPMUACLKTR: ACLKTR5=0,ACLKTR4=0,ACLKTR3=0,ACLKTR2=0,ACLKTR1=0,ACLKTR0=0 */
  CPMUACLKTR = 0x00U;                                      
  /* CPMUAPICTL: APICLK=1,APIE=1,APIF=1 */
  CPMUAPICTL |= (unsigned char)0x83U;                      
  /* CPMUAPICTL: APIFE=1 */
  CPMUAPICTL |= (unsigned char)0x04U;        
}
  /* ### */