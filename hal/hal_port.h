#ifndef _HAL_PORT_
#define _HAL_PORT_

#define Ctrl_Out1         PTT_PTT3
#define Ctrl_Out2         PTT_PTT6
#define Ctrl_Out3         PTT_PTT5
#define Ctrl_Out4         PTT_PTT4
#define Ctrl_Out5         PORTA_PA1
#define Ctrl_Out6         PTM_PTM2
#define Ctrl_Out7         PORTD_PD7
#define Ctrl_Out8         PORTB_PB2

#define Ctrl_Out9         PTJ_PTJ4
#define Ctrl_Out10        PORTA_PA3
#define Ctrl_Out11        PTM_PTM3
#define Ctrl_Out12        PTP_PTP1
#define Ctrl_Out13        PORTA_PA2
#define Ctrl_Out14        PORTD_PD5
#define Ctrl_Out15        PTP_PTP0
#define Ctrl_Out16        PTJ_PTJ5



#define Ctrl_Out17         PORTB_PB3
#define Ctrl_Out18         PORTA_PA0
#define Ctrl_Out19         PORTD_PD6
#define Ctrl_Out20         PTP_PTP2
#define Ctrl_Out21         PORTB_PB5
#define Ctrl_Out22         PORTB_PB6
#define Ctrl_Out23         PORTC_PC6
#define Ctrl_Out24         PORTD_PD3

 
#define Ctrl_Out25         PORTC_PC5
#define Ctrl_Out26         PORTC_PC0
#define Ctrl_Out27         PORTC_PC3
#define Ctrl_Out28         PORTC_PC4


#define Ctrl_Out29         PORTD_PD0
#define Ctrl_Out30         PORTC_PC7
#define Ctrl_Out31         PORTC_PC1
#define Ctrl_Out32         PORTC_PC2
#define Ctrl_Out33         PORTB_PB4
#define Ctrl_Out34         PTT_PTT2
#define Ctrl_Out35         PTS_PTS0
#define Ctrl_Out36         PORTD_PD1

#define Ctrl_In1           PTJ_PTJ7
#define Ctrl_In2           PTJ_PTJ6 

//电源控制
#define POWER_CTRL_5V      PTS_PTS1		// 未使用
#define POWER_CTRL_12V     PTS_PTS2     // 未使用

//MC33978 信号定义
//!<片选信号 低电平有效
#define MC_CS1n            PORTB_PB7
#define MC_CS2n            PORTB_PB1
#define MC_CS3n            PTJ_PTJ3
//!<休眠信号低电平有效
#define MC_WKn             PORTD_PD2

#define MC_INT0            PT01AD_PT0AD3
#define MC_INT1            PT01AD_PT1AD2
#define MC_INT2            PT01AD_PT0AD2
//!<TLE6250G休眠信号 高电平
#define TLE6250G_WK        PORTD_PD4    // 未使用


void Hal_Port_Init(void);
#endif
