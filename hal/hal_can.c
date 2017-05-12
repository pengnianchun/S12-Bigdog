#include <MC9S12G128.h> 
#include <hidef.h>     
#include "hal_system.h" 
#include "hal_can.h" 

func_type  can_process;

void hal_can_init(func_type func)

 {

//====================================================================//	
/* ### Init_MSCAN init code */
  /* CANCTL0: INITRQ=1 */
  CANCTL0 |= (uint8_t)0x01U;                      
  while(CANCTL1_INITAK == 0U) {        /* Wait for init acknowledge */
  }
  /* CANCTL1: CANE=1,CLKSRC=1,LOOPB=0,LISTEN=0,BORM=0,WUPM=0,SLPAK=0,INITAK=1 */
  CANCTL1 = 0xC1U;                                      
  /* CANBTR1: SAMP=0,TSEG22=0,TSEG21=0,TSEG20=1,TSEG13=0,TSEG12=0,TSEG11=1,TSEG10=0 */
  CANBTR1 = 0x12U;                                      
  /* CANBTR0: SJW1=1,SJW0=1,BRP5=0,BRP4=0,BRP3=1,BRP2=1,BRP1=1,BRP0=1 */
  CANBTR0 = 0xCFU;                                      
  /* CANIDAC: IDAM1=0,IDAM0=0,IDHIT2=0,IDHIT1=0,IDHIT0=0 */
  CANIDAC = 0x00U;                                      
  /* CANIDAR0: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR0 = 0x00U;                                      
  /* CANIDAR1: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR1 = 0x00U;                                      
  /* CANIDAR2: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR2 = 0x00U;                                      
  /* CANIDAR3: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR3 = 0x00U;                                      
  /* CANIDAR4: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR4 = 0x00U;                                      
  /* CANIDAR5: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR5 = 0x00U;                                      
  /* CANIDAR6: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR6 = 0x00U;                                      
  /* CANIDAR7: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  CANIDAR7 = 0x00U;                                      
  /* CANIDMR0: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR0 = 0xFFU;                                      
  /* CANIDMR1: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR1 = 0xFFU;                                      
  /* CANIDMR2: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR2 = 0xFFU;                                      
  /* CANIDMR3: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR3 = 0xFFU;                                      
  /* CANIDMR4: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR4 = 0xFFU;                                      
  /* CANIDMR5: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR5 = 0xFFU;                                      
  /* CANIDMR6: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR6 = 0xFFU;                                      
  /* CANIDMR7: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  CANIDMR7 = 0xFFU;                                      
  /* CANCTL0: INITRQ=0 */
  CANCTL0 &= (uint8_t)~(uint8_t)0x01U;                     
  while(CANCTL1_INITAK) {              /* Wait for init exit */
  }
  /* CANCTL0: RXFRM=0,RXACT=0,CSWAI=0,SYNCH=0,TIME=0,WUPE=0,SLPRQ=0,INITRQ=0 */
  
  CANCTL0 = 0x00U;   
  CANRFLG = 0xC3;                                   
  /* CANRIER: WUPIE=0,CSCIE=0,RSTATE1=0,RSTATE0=0,TSTATE1=0,TSTATE0=0,OVRIE=0,RXFIE=1 */
  CANRIER = 0x01U;                                      
  /* CANTIER: TXEIE2=0,TXEIE1=0,TXEIE0=0 */
  CANTIER = 0x00U;                                      
  /* ### */
  
  can_process=func;
	
 }
 

uint8_t hal_Can_SendData(uint32_t id, uint8_t mode,uint8_t priority, uint8_t length, uint8_t *txdata )
{

  uint8_t index;
	uint8_t ID_Data[4];
  uint8_t txbuffer = {0};

	if (!CANTFLG)              /* Is Transmit Buffer full?? */
		return ERR_BUFFER_FULL;

	CANTBSEL = CANTFLG;       /* Select lowest empty buffer */
	txbuffer = CANTBSEL;		/* Backup selected buffer */
	

	
	/* Load Id to IDR Registers */
	if(mode==STANDARD) 
	{
	
  	ID_Data[1]=(uint8_t)(id>>3);
  	ID_Data[0]=(uint8_t)id;
    ID_Data[0]=(ID_Data[0]<<5);
    CANTXIDR0=ID_Data[1];
    CANTXIDR1=ID_Data[0];

	}
	
		if(mode==EXTENDED) 
	{
	
	  uint8_t buf;
	  id=id<<1;
  	ID_Data[0]=(uint8_t)(id);
  	ID_Data[1]=(uint8_t)(id>>8);
    buf=ID_Data[2]=(uint8_t)(id>>16);
    buf=((buf<<2)&0xe0);
    ID_Data[2]=((ID_Data[2]&0x07)|buf|EXTENDED|SRR);
    ID_Data[3]=(uint8_t)(id>>22);
  
    CANTXIDR0= ID_Data[3];
    CANTXIDR1= ID_Data[2];
    CANTXIDR2= ID_Data[1];
    CANTXIDR3= ID_Data[0];
    
	}

   	for (index=0; index<length; index++)
	 {
		*(&CANTXDSR0 + index) = txdata[index];  /* Load data to Tx buffer Data Segment Registers*/
  	}

	CANTXDLR = length;                          /* Set Data Length Code */
	CANTXTBPR = priority;                       /* Set Priority */

	CANTFLG = txbuffer;	                     /* Start transmission */
	// while ( (CANTFLG & txbuffer) != txbuffer);  /* Wait for Transmission completion */
	return NO_ERR;
}


void  hal_can_receive(void) {
  
  uint8_t length, index;
  uint8_t temp[8],IDtemp[4],Temp1,Temp2;
  uint32_t ID; 
  
  length = (CANRXDLR & 0x0F);
	for (index=0; index<length; index++)
    temp[index] = *(&CANRXDSR0 + index); /* Get received data */
  
  IDtemp[0]=CANRXIDR0;
  IDtemp[1]=CANRXIDR1;
  IDtemp[2]=CANRXIDR2;
  IDtemp[3]=CANRXIDR3;
  
  if((IDtemp[1]&EXTENDED)==EXTENDED) 
  {
    
  
	  ID=(((unsigned long)IDtemp[2])<<7)|(((unsigned long)IDtemp[3])>>1);
	  ID=ID|(((unsigned long)(IDtemp[1]&0x07))<<15);
	  ID=ID|(((unsigned long)((IDtemp[1]&0xE0)>>5))<<18);
	  ID=ID|(((unsigned long)(IDtemp[0]))<<21);
	   (*can_process)(ID,EXTENDED,length,temp); 
  }
  else
  {
    ID=IDtemp[0];
    ID=ID<<3;
    IDtemp[1]=(IDtemp[1]>>5);
    ID=(ID|IDtemp[1]); 
   (*can_process)(ID,STANDARD,length,temp);
  }
 
}

