#ifndef _HAL_PORT_
#define _HAL_PORT_

#define Ctrl_Out1         PORTC_PC0
#define Ctrl_Out2         PORTC_PC1
#define Ctrl_Out3         PORTC_PC2
#define Ctrl_Out4         PORTC_PC3
#define Ctrl_Out5         PORTC_PC4
#define Ctrl_Out6         PORTC_PC5
#define Ctrl_Out7         PORTC_PC6
#define Ctrl_Out8         PORTC_PC7

#define Ctrl_Out9         PORTD_PD0
#define Ctrl_Out10        PORTD_PD1
#define Ctrl_Out11        PORTD_PD2
#define Ctrl_Out12        PORTD_PD3
#define Ctrl_Out13        PORTD_PD4
#define Ctrl_Out14        PORTD_PD5
#define Ctrl_Out15        PORTD_PD6
#define Ctrl_Out16        PORTD_PD7



#define Ctrl_Out17         PTT_PTT0
#define Ctrl_Out18         PTT_PTT1
#define Ctrl_Out19         PTT_PTT2
#define Ctrl_Out20         PTT_PTT3
#define Ctrl_Out21         PTT_PTT4
#define Ctrl_Out22         PTT_PTT5
#define Ctrl_Out23         PTT_PTT6
#define Ctrl_Out24         PTT_PTT7

 
#define Ctrl_Out25         PTP_PTP0
#define Ctrl_Out26         PTP_PTP1
#define Ctrl_Out27         PTP_PTP2
#define Ctrl_Out28         PTP_PTP3


#define Ctrl_Out29         PTS_PTS0
#define Ctrl_Out30         PTS_PTS1
#define Ctrl_Out31         PTS_PTS2
#define Ctrl_Out32         PTS_PTS3
#define Ctrl_Out33         PTS_PTS4
#define Ctrl_Out34         PTS_PTS5
#define Ctrl_Out35         PTS_PTS6
#define Ctrl_Out36         PTS_PTS7

void Hal_Port_Init(void);
#endif
