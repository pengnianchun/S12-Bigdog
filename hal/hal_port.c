#include <MC9S12G128.h>   

void Hal_Port_Init(void)
 {
 //===========================prot a=========================================//  
 	DDRAB_DDRA = 0x0F;
 //===========================prot M=========================================//  
 	DDRM = 0x0C;
 //===========================prot s=========================================//  
  /* ### Init_GPIO init code */
  /* PTS: PTS7=0,PTS6=0,PTS5=0,PTS4=0,PTS3=0,PTS2=0,PTS1=0,PTS0=0 */
  PTS = 0x00U;                                      
  /* PPSS: PPSS7=0,PPSS6=0,PPSS5=0,PPSS4=0,PPSS3=0,PPSS2=0,PPSS1=0,PPSS0=0 */
  PPSS = 0x00U;                                      
  /* WOMS: WOMS7=0,WOMS6=0,WOMS5=0,WOMS4=0,WOMS3=0,WOMS2=0,WOMS1=0,WOMS0=0 */
  WOMS = 0x00U;                                      
  /* PERS: PERS7=1,PERS6=1,PERS5=1,PERS4=1,PERS3=1,PERS2=1,PERS1=1,PERS0=1 */
  PERS = 0xFFU;                                      
  /* DDRS: DDRS7=1,DDRS6=1,DDRS5=1,DDRS4=1,DDRS3=1,DDRS2=1,DDRS1=1,DDRS0=1 */
  DDRS = 0xFFU;           
  
//===========================prot c=========================================//  
   /* ### Init_GPIO init code */
  /* PORTC: PC7=0,PC6=0,PC5=0,PC4=0,PC3=0,PC2=0,PC1=0,PC0=0 */
  PORTC = 0x00U;                                      
  /* PUCR: PUPCE=1 */
  PUCR |= (unsigned char)0x04U;                      
  /* DDRC: DDRC7=1,DDRC6=1,DDRC5=1,DDRC4=1,DDRC3=1,DDRC2=1,DDRC1=1,DDRC0=1 */
  DDRC = 0xFFU;                                      
  /* ### */

 //===========================prot d=========================================//
   /* ### Init_GPIO init code */
  /* PORTD: PD7=0,PD6=0,PD5=0,PD4=0,PD3=0,PD2=0,PD1=0,PD0=0 */
  PORTD = 0x00U;                                      
  /* PUCR: PUPDE=1 */
  PUCR |= (unsigned char)0x08U;                      
  /* DDRD: DDRD7=1,DDRD6=1,DDRD5=1,DDRD4=1,DDRD3=1,DDRD2=1,DDRD1=1,DDRD0=1 */
  DDRD = 0xFFU;                                      
  /* ### */
 //===========================prot t=========================================//
  /* ### Init_GPIO init code */
  /* PTT: PTT7=0,PTT6=0,PTT5=0,PTT4=0,PTT3=0,PTT2=0,PTT1=0,PTT0=0 */
  PTT = 0x00U;                                      
  /* PPST: PPST7=0,PPST6=0,PPST5=0,PPST4=0,PPST3=0,PPST2=0,PPST1=0,PPST0=0 */
  PPST = 0x00U;                                      
  /* PERT: PERT7=1,PERT6=1,PERT5=1,PERT4=1,PERT3=1,PERT2=1,PERT1=1,PERT0=1 */
  PERT = 0xFFU;                                      
  /* DDRT: DDRT7=1,DDRT6=1,DDRT5=1,DDRT4=1,DDRT3=1,DDRT2=1,DDRT1=1,DDRT0=1 */
  DDRT = 0xFFU;                                      
  /* ### */
  
 //===========================prot p=========================================//
  
    /* Disable interrupts */
  /* PIEP: PIEP7=0,PIEP6=0,PIEP5=0,PIEP4=0,PIEP3=0,PIEP2=0,PIEP1=0,PIEP0=0 */
  PIEP = 0x00U;                                      
    /* Clear interrupt flags */
  /* PIFP: PIFP7=1,PIFP6=1,PIFP5=1,PIFP4=1,PIFP3=1,PIFP2=1,PIFP1=1,PIFP0=1 */
  PIFP = 0xFFU;                                      
  /* PTP: PTP3=0,PTP2=0,PTP1=0,PTP0=0 */
  PTP &= (unsigned char)~(unsigned char)0x0FU;                     
  /* PPSP: PPSP3=0,PPSP2=0,PPSP1=0,PPSP0=0 */
  PPSP &= (unsigned char)~(unsigned char)0x0FU;                     
  /* PERP: PERP3=1,PERP2=1,PERP1=1,PERP0=1 */
  PERP |= (unsigned char)0x0FU;                      
  /* DDRP: DDRP3=1,DDRP2=1,DDRP1=1,DDRP0=1 */
  DDRP |= (unsigned char)0x0FU;                      
  /* ### Init_GPIO init code */
 
 }
 
