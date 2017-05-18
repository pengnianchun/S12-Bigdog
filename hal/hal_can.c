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
CANCTL0 = 0x01;           /* Enter Initialization Mode
                               *
                               *  0b00000001
                               *    ||||||||__ Enter Initialization Mode
                               *    |||||||___ Sleep Mode Request bit
                               *    ||||||____ Wake-Up disabled
                               *    |||||_____ Time stamping disabled
                               *    ||||______ Synchronized Status
                               *    |||_______ CAN not affected by Wait
                               *    ||________ Receiver Active Status bit
                               *    |_________ Received Frame Flag bit
                               */

	while (!(CANCTL1&0x01))
	{
		_FEED_COP();
	};	/* Wait for Initialization Mode acknowledge
                                             * INITRQ bit = 1
                                             */

	CANCTL1 = 0xC0;           /* Enable MSCAN module and LoopBack Mode
                               *
                               *  0b10100000
                               *    ||||||||__ Initialization Mode Acknowledge
                               *    |||||||___ Sleep Mode Acknowledge
                               *    ||||||____ Wake-up low-pass filter disabled
                               *    |||||_____ Unimplemented
                               *    ||||______ Listen Only Mode disabled
                               *    |||_______ Loop Back Mode enabled
                               *    ||________ Ext Osc/Xtal as Clock Source
                               *    |_________ MSCAN Module enabled
                               */

	CANBTR0 = 0xCF;           /* Synch Jump = 3 Tq clock Cycles
                               *
                               *  0b11000111
                               *    ||||||||__
                               *    |||||||___\
                               *    ||||||____ |
                               *    |||||_____ |_ CAN Clock Prescaler = 7
                               *    ||||______ |
                               *    |||_______ |
                               *    ||________/
                               *    |_________>- SJW = 3
                               */

	CANBTR1 = 0x12;	          /* Set Number of samples per bit, TSEG1 and TSEG2
                               *
                               *  0b00111010
                               *    ||||||||__
                               *    |||||||___|
                               *    ||||||____|- TSEG1 = 10
                               *    |||||_____|
                               *    ||||______
                               *    |||_______\_ TSEG2 = 3
                               *    ||________/
                               *    |_________ One sample per bit
                               */



	/* Acceptance Filters */
	CANIDAC = 0x00U;
	/* CANIDAR0: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR0 = 0x00U;
	/* CANIDAR1: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR1 = 0x00U;
	/* CANIDAR2: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR2 = 0x00U;
	/* CANIDAR3: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR3 = 0x00U;
	/* CANIDAR4: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR4 = 0x00U;
	/* CANIDAR5: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR5 = 0x00U;
	/* CANIDAR6: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR6 = 0x00U;
	/* CANIDAR7: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR7 = 0x00U;
	/* CANIDMR0: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR0 = 0xFFU;
	/* CANIDMR1: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR1 = 0xFFU;
	/* CANIDMR2: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR2 = 0xFFU;
	/* CANIDMR3: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR3 = 0xFFU;
	/* CANIDMR4: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR4 = 0x00U;
	/* CANIDMR5: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR5 = 0x00U;
	/* CANIDMR6: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR6 = 0x00U;
	/* CANIDMR7: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR7 = 0x00U;

	CANCTL0 = 0x00;            /* Exit Initialization Mode Request */
	while ((CANCTL1&0x01) != 0)
	{
		_FEED_COP();
	};	/* Wait for Normal Mode */

	while(!(CANCTL0&0x10))_FEED_COP();
	CANRFLG = 0xC3;
	CANRIER = 0x01;                                  
  /* ### */
  can_process=func;
	
 }
 

uint8_t hal_Can_SendData(uint32_t id, uint8_t mode,uint8_t priority, uint8_t length, uint8_t *txdata )
{

  uint8_t index;
  uint8_t ID_Data[4];
  uint8_t txbuffer = {0};

	if (0 == CANCTL0_SYNCH)              /* Is Transmit Buffer full?? */
		return ERR_BUFFER_FULL;
	do{
		CANTBSEL = CANTFLG;       /* Select lowest empty buffer */
		txbuffer = CANTBSEL;		/* Backup selected buffer */
	}
	while(!txbuffer);
	
	/* Load Id to IDR Registers */
	if(mode==STANDARD) 
	{
		CANTXIDR0 = (unsigned char)(id>>3);
		CANTXIDR1 = (unsigned char)(id<<5);
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

