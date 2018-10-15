#ifndef CTRL_OUT_H__
  #define CTRL_OUT_H__
#define RAIN_HIGH_OUT    	Ctrl_Out1
#define RAIN_SLOW_OUT    	Ctrl_Out4
#define SPRAY_OUT   Ctrl_Out23//喷水电机
#define RAIN_FAST_CTL   Ctrl_ctr       //回流保护    快档电机
#define RAIN_SLOW_CTL  Ctrl_Out37 //回流保护  慢档电机
#define HOME_VOL		 (IN_KL03)


#define SET_RAIN_INTERVAL_CTR2	do{PORTB_PB0 = 1;}while(0)
#define CLR_RAIN_INTERVAL_CTR2  do{PORTB_PB0 = 0;}while(0)
extern void RenovatingOutput(void);
extern void wipe_delay(void);
void InitOutput(void);
void rain_wape(void) ;
typedef union
{ 
    unsigned char BYTES[6];
    struct 
    { 
        unsigned char O1:1; 
        unsigned char O2:1; 
        unsigned char O3:1; 
        unsigned char O4:1; 
        unsigned char O5:1; 
        unsigned char O6:1; 
        unsigned char O7:1; 
        unsigned char O8:1; 
        unsigned char O9:1; 
        unsigned char O10:1; 
        unsigned char O11:1; 
        unsigned char O12:1; 
        unsigned char O13:1; 
        unsigned char O14:1; 
        unsigned char O15:1; 
        unsigned char O16:1; 
        unsigned char O17:1; 
        unsigned char O18:1; 
        unsigned char O19:1; 
        unsigned char O20:1; 
        unsigned char O21:1; 
        unsigned char O22:1; 
        unsigned char O23:1; 
        unsigned char O24:1; 
        unsigned char O25:1; 
        unsigned char O26:1; 
        unsigned char O27:1; 
        unsigned char O28:1; 
        unsigned char O29:1; 
        unsigned char O30:1;
		unsigned char O31:1; 
        unsigned char O32:1; 
        unsigned char O33:1; 
        unsigned char O34:1; 
        unsigned char O35:1; 
        unsigned char O36:1; 
        unsigned char reserve : 4;
        unsigned char Qidong:1; 
        unsigned char man:1; 
		 unsigned char kuai:1; 
		  unsigned char jianxi:1; 
		   unsigned char penshui:1; 
		    unsigned char res2:3; 
    } BITS; 
} POUT; 

extern unsigned char pf[40];
extern POUT gPout;
#endif