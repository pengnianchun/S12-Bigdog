#include "MCUinit.h"
#include "CtrlOut.h"
#include "protocol.h" 
#include "config.h"
#include "ctrlin.h"

//!<�������ӳ��

#define J2_07     Ctrl_Out32
#define J2_08     Ctrl_Out31
#define J2_09     Ctrl_Out36
#define J2_10     Ctrl_Out26
#define J2_11     Ctrl_Out35
#define J2_12     Ctrl_Out25

#define J3_04     Ctrl_Out34
#define J3_05     Ctrl_Out33
#define J3_07     Ctrl_Out22
#define J3_08     Ctrl_Out21
#define J3_09     Ctrl_Out28
#define J3_10     Ctrl_Out30
#define J3_11     Ctrl_Out29
#define J3_12     Ctrl_Out27
#define J3_13     Ctrl_Out2
#define J3_14     Ctrl_Out23
#define J3_15     Ctrl_Out24
#define J3_16     Ctrl_Out3
#define J3_17     Ctrl_Out4
#define J3_18     Ctrl_Out1

#define J5_16     Ctrl_Out5

#define J6_01     Ctrl_Out10
#define J6_02     Ctrl_Out15
#define J6_03     Ctrl_Out20
#define J6_04     Ctrl_Out6
#define J6_05     Ctrl_Out11
#define J6_06     Ctrl_Out16
#define J6_07     Ctrl_Out7
#define J6_08     Ctrl_Out12
#define J6_09     Ctrl_Out17
#define J6_10     Ctrl_Out8
#define J6_11     Ctrl_Out13
#define J6_12     Ctrl_Out18
#define J6_13     Ctrl_Out9
#define J6_14     Ctrl_Out14
#define J6_15     Ctrl_Out19


void rain_wape(void);

static u16 per_old = 0;
void InitOutput(void)
{
	Ctrl_Out1 = 0;Ctrl_Out2 = 0;Ctrl_Out3 = 0;Ctrl_Out4 = 0;Ctrl_Out5 = 0;Ctrl_Out6 = 0;Ctrl_Out7 = 0;Ctrl_Out8 = 0;Ctrl_Out9 = 0;Ctrl_Out10 = 0;
	Ctrl_Out11 = 0;Ctrl_Out12 = 0;Ctrl_Out13 = 0;Ctrl_Out14 = 0;Ctrl_Out15 = 0;Ctrl_Out16 = 0;Ctrl_Out17 = 0;Ctrl_Out18 = 0;Ctrl_Out19 = 0;Ctrl_Out20 = 0;
	Ctrl_Out21 = 0;Ctrl_Out22 = 0;Ctrl_Out23 = 0;Ctrl_Out24 = 0;Ctrl_Out25 = 0;Ctrl_Out26 = 0;
}


void RenovatingOutput(void)
{
	u16 dty,per;
	if (Select_addr != FRONT_MODULE_ADDR)
	{
		//!<������Σ�������ơ�
		Ctrl_Out1   = ID_72x_data.out[0].Bits.bit0;
		Ctrl_Out4   = ID_72x_data.out[0].Bits.bit3;
	}
	else
	{
		rain_wape();
	}
	 Ctrl_Out2   = ID_72x_data.out[0].Bits.bit1;
	 Ctrl_Out3   = ID_72x_data.out[0].Bits.bit2;
	 
	 Ctrl_Out5   = ID_72x_data.out[0].Bits.bit4;
	 Ctrl_Out6   = ID_72x_data.out[0].Bits.bit5;
	 Ctrl_Out7   = ID_72x_data.out[0].Bits.bit6;
	 Ctrl_Out8   = ID_72x_data.out[0].Bits.bit7;
	            
	 Ctrl_Out9   = ID_72x_data.out[1].Bits.bit0;
	 Ctrl_Out10  = ID_72x_data.out[1].Bits.bit1;
	 Ctrl_Out11  = ID_72x_data.out[1].Bits.bit2;
	 Ctrl_Out12  = ID_72x_data.out[1].Bits.bit3;
	 Ctrl_Out13  = ID_72x_data.out[1].Bits.bit4;
	 Ctrl_Out14  = ID_72x_data.out[1].Bits.bit5;
	 Ctrl_Out15  = ID_72x_data.out[1].Bits.bit6;
	 Ctrl_Out16  = ID_72x_data.out[1].Bits.bit7;
	            
	 Ctrl_Out17  = ID_72x_data.out[2].Bits.bit0;
	 Ctrl_Out18  = ID_72x_data.out[2].Bits.bit1;
	 Ctrl_Out19  = ID_72x_data.out[2].Bits.bit2;
	 Ctrl_Out20  = ID_72x_data.out[2].Bits.bit3;
	 Ctrl_Out21  = ID_72x_data.out[2].Bits.bit4;
	 Ctrl_Out22  = ID_72x_data.out[2].Bits.bit5;
	 Ctrl_Out23  = ID_72x_data.out[2].Bits.bit6;
	 Ctrl_Out24  = ID_72x_data.out[2].Bits.bit7;
	            
	 Ctrl_Out25  = ID_72x_data.out[3].Bits.bit0;
	 Ctrl_Out26  = ID_72x_data.out[3].Bits.bit1;
	 Ctrl_Out27  = ID_72x_data.out[3].Bits.bit2;
	 Ctrl_Out28  = ID_72x_data.out[3].Bits.bit3;
	 Ctrl_Out29  = ID_72x_data.out[3].Bits.bit4;
	 Ctrl_Out30  = ID_72x_data.out[3].Bits.bit5;
	 Ctrl_Out31  = ID_72x_data.out[3].Bits.bit6;
	 Ctrl_Out32  = ID_72x_data.out[3].Bits.bit7;
	            
	 Ctrl_Out33  = ID_72x_data.out[4].Bits.bit0;
	 Ctrl_Out34  = ID_72x_data.out[4].Bits.bit1;
	 Ctrl_Out35  = ID_72x_data.out[4].Bits.bit2;
	 Ctrl_Out36  = ID_72x_data.out[4].Bits.bit3;

	per = ID_72x_data.per[0] + ID_72x_data.per[1] *256;
	per = 50000u/per;
	if(per == 0)
	{
		per = 1;
	}
	if (per_old != per)
	{
		dty = per/2;//50%
		Change_Pwm(per,dty);
	}
	per_old = per;
}

#define K_ON             (ID_72x_data.out[5].Bits.bit0)
#define RAIN_SLOW        (ID_72x_data.out[5].Bits.bit1)
#define RAIN_HIGH        (ID_72x_data.out[5].Bits.bit2)
#define RAIN_INTERVAL    (ID_72x_data.out[5].Bits.bit3)
#define RAIN_SPRAY       (ID_72x_data.out[5].Bits.bit4)



//��γ���
unsigned char DELAY_START = 0;
unsigned char DELAY_END = 0;

void rain_wape(void) 
{
    static unsigned char RAIN_RST = 0;   
    //RAIN_SLOW	       �������
    //RAIN_INTERVAL	   ��μ�Ъ��
    //RAIN_HIGH	       ��ο쵵
    //RAIN_SPRAY	   �����ˮ��
    
    if (wipe_int_time > 0) wipe_int_time--; //��μ�Ъʱ��
    if (wash_time > 0) wash_time--; //���ϴ��ʱ��
    if (wipe_stop_time > 0)wipe_stop_time--;

    if (K_ON && RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL) {//����
        if (DELAY_START == 0) {
            DELAY_START = 1;
            wipe_wpp_time = WIPE_WPP_TIMEOUT;
        }
        RAIN_INTERVAL_CTR = 0;
        if (wipe_wpp_time == 0) {
            SET_RAIN_INTERVAL_CTR2;
            RAIN_SLOW_OUT = 1; //����������
            RAIN_HIGH_OUT = 0;
            wash_time = 0;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    }
    if (K_ON && RAIN_HIGH && !RAIN_INTERVAL) {//�쵵 �쵵����ͬʱ��Чʱ���쵵��Ч
        if (DELAY_START == 0) {
            DELAY_START = 1;
            wipe_wpp_time = WIPE_WPP_TIMEOUT;
        }
        RAIN_INTERVAL_CTR = 0;
        if (wipe_wpp_time == 0) {
            RAIN_SLOW_OUT = 0;
           CLR_RAIN_INTERVAL_CTR2;
            RAIN_HIGH_OUT = 1; //��ο쵵���
            wash_time = 0;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    }
    if (K_ON && RAIN_SPRAY) {
        RAIN_SPRAY = 1; //��ˮ���
        if (DELAY_START == 0) {
            DELAY_START = 1;
            wipe_wpp_time = WIPE_WPP_TIMEOUT;
        }
        RAIN_INTERVAL_CTR = 0;
        if (wipe_wpp_time == 0) {
            SET_RAIN_INTERVAL_CTR2;
            RAIN_SLOW_OUT = 1; //����������
            RAIN_HIGH_OUT = 0;
            wash_time = WASH_TIMEOUT;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    } else {
        if (wash_time <= 0) RAIN_SPRAY = 0;
    }
    if (K_ON && !RAIN_SLOW && !RAIN_HIGH && RAIN_INTERVAL) {//��Ъ��
        if (wipe_int_time == 0) {
            if (DELAY_START == 0) {
                DELAY_START = 1;
                wipe_wpp_time = WIPE_WPP_TIMEOUT;
            }
            RAIN_INTERVAL_CTR = 0;
            if (wipe_wpp_time == 0) {
                SET_RAIN_INTERVAL_CTR2;
                RAIN_SLOW_OUT = 1;
                RAIN_HIGH_OUT = 0;
                wash_time = 0;
                DELAY_START = 0;
                DELAY_END = 0;
            }
        }
    }
    //����޲�������Ҫֹͣ����
    if (!K_ON || (!RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL && !RAIN_SPRAY && (wash_time == 0))) {
        /*if (!HOME_VOL && wipe_stop_time > 0) {//��ΰ�;���磬�ϵ���Զ���λ
            RAIN_HIGH_OUT = 0;
            RAIN_SLOW_OUT = 1;
            RAIN_SPRAY = 0;
            SET_RAIN_INTERVAL_CTR2;
            wipe_int_time = 0;
        }*/
        if (!HOME_VOL && RAIN_HIGH_OUT && wipe_stop_time > 0) {
            RAIN_HIGH_OUT = 0;
            RAIN_SLOW_OUT = 1;
            RAIN_SPRAY = 0;
            SET_RAIN_INTERVAL_CTR2;
            wipe_int_time = 0;
        }
        if (wipe_stop_time == 0) { //��β������ضϿ� 20��ǿ�ƹر���� ������ε��
            RAIN_HIGH_OUT = 0;
            RAIN_SLOW_OUT = 0;
            RAIN_SPRAY = 0;
            SET_RAIN_INTERVAL_CTR2;
            wipe_int_time = 0;
        }
    } else {
        wipe_stop_time = WIPE_STOP_TIMEOUT;
    }

    if (HOME_VOL == 1 && RAIN_RST == 0) {//��θ�λ���� HOME_VOL==1
        if (K_ON) {
            if (!RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL && !RAIN_SPRAY && (wash_time == 0)) {
                RAIN_HIGH_OUT = 0;
                RAIN_SLOW_OUT = 0;   
                SET_RAIN_INTERVAL_CTR2;
            }
            if (RAIN_INTERVAL) {//��Ъ
                RAIN_SLOW_OUT = 0;
                SET_RAIN_INTERVAL_CTR2;
                wipe_int_time = WIPE_INT_TIMEOUT;
            }
        } else {
            RAIN_HIGH_OUT = 0;
            RAIN_SLOW_OUT = 0;
            RAIN_SPRAY = 0;
            SET_RAIN_INTERVAL_CTR2;
            wipe_int_time = 0;
        }
    }
    
    if (HOME_VOL) {
        if ((RAIN_HIGH_OUT == 0) && (RAIN_SLOW_OUT == 0)) {
            if (DELAY_END == 0) {
                DELAY_END = 1;
                wipe_wpp_time = WIPE_WPP_DISCHARGING;//�򿪷ŵ���ʱʱ��Ϊ30-10=20ms,ʵ�ʲ�����������ض���10ms��ʱ
            }
            if (wipe_wpp_time == 0) {
                RAIN_INTERVAL_CTR = 1;
                DELAY_END = 0;
                DELAY_START = 0;
            }
        }
    }
    
    RAIN_RST = HOME_VOL;
}



void wipe_delay(void) { //1ms  

    if (wipe_wpp_time > 0)wipe_wpp_time--;//����ϵ��ӳ�ʱ��    
}























