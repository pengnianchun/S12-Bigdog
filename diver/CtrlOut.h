#ifndef CTRL_OUT_H__
  #define CTRL_OUT_H__
#define RAIN_HIGH_OUT    	Ctrl_Out1
#define RAIN_SLOW_OUT    	Ctrl_Out4
#define RAIN_INTERVAL_OUT   Ctrl_Out23
#define RAIN_INTERVAL_CTR   Ctrl_ctr   //É²³µ
#define RAIN_INTERVAL_CTR2  
#define HOME_VOL		 (IN_KL03)

#define SET_RAIN_INTERVAL_CTR2	do{PORTB_PB0 = 1;}while(0)
#define CLR_RAIN_INTERVAL_CTR2  do{PORTB_PB0 = 0;}while(0)
extern void RenovatingOutput(void);
extern void wipe_delay(void);
void InitOutput(void);
void rain_wape(void) ;
#endif