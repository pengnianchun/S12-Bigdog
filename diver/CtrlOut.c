#include "MCUinit.h"
#include "CtrlOut.h"
#include "protocol.h" 
#include "config.h"
#include "ctrlin.h"

//!<输出端子映射

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
		//!<用于雨刮，喷嘴控制。
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



//雨刮程序
unsigned char DELAY_START = 0;
unsigned char DELAY_END = 0;

void rain_wape(void) 
{
    static unsigned char RAIN_RST = 0;   
    //RAIN_SLOW	       雨刮慢档
    //RAIN_INTERVAL	   雨刮间歇档
    //RAIN_HIGH	       雨刮快档
    //RAIN_SPRAY	   雨刮喷水档
    
    if (wipe_int_time > 0) wipe_int_time--; //雨刮间歇时间
    if (wash_time > 0) wash_time--; //雨刮洗涤时间
    if (wipe_stop_time > 0)wipe_stop_time--;

    if (K_ON && RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL) {//慢档
        if (DELAY_START == 0) {
            DELAY_START = 1;
            wipe_wpp_time = WIPE_WPP_TIMEOUT;
        }
        RAIN_INTERVAL_CTR = 0;
        if (wipe_wpp_time == 0) {
            SET_RAIN_INTERVAL_CTR2;
            RAIN_SLOW_OUT = 1; //雨刮慢档电机
            RAIN_HIGH_OUT = 0;
            wash_time = 0;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    }
    if (K_ON && RAIN_HIGH && !RAIN_INTERVAL) {//快档 快档慢档同时有效时，快档有效
        if (DELAY_START == 0) {
            DELAY_START = 1;
            wipe_wpp_time = WIPE_WPP_TIMEOUT;
        }
        RAIN_INTERVAL_CTR = 0;
        if (wipe_wpp_time == 0) {
            RAIN_SLOW_OUT = 0;
           CLR_RAIN_INTERVAL_CTR2;
            RAIN_HIGH_OUT = 1; //雨刮快档电机
            wash_time = 0;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    }
    if (K_ON && RAIN_SPRAY) {
        RAIN_SPRAY = 1; //喷水电机
        if (DELAY_START == 0) {
            DELAY_START = 1;
            wipe_wpp_time = WIPE_WPP_TIMEOUT;
        }
        RAIN_INTERVAL_CTR = 0;
        if (wipe_wpp_time == 0) {
            SET_RAIN_INTERVAL_CTR2;
            RAIN_SLOW_OUT = 1; //雨刮慢档电机
            RAIN_HIGH_OUT = 0;
            wash_time = WASH_TIMEOUT;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    } else {
        if (wash_time <= 0) RAIN_SPRAY = 0;
    }
    if (K_ON && !RAIN_SLOW && !RAIN_HIGH && RAIN_INTERVAL) {//间歇档
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
    //雨刮无操作，需要停止工作
    if (!K_ON || (!RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL && !RAIN_SPRAY && (wash_time == 0))) {
        /*if (!HOME_VOL && wipe_stop_time > 0) {//雨刮半途掉电，上电可自动归位
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
        if (wipe_stop_time == 0) { //雨刮操作开关断开 20内强制关闭雨刮 保护雨刮电机
            RAIN_HIGH_OUT = 0;
            RAIN_SLOW_OUT = 0;
            RAIN_SPRAY = 0;
            SET_RAIN_INTERVAL_CTR2;
            wipe_int_time = 0;
        }
    } else {
        wipe_stop_time = WIPE_STOP_TIMEOUT;
    }

    if (HOME_VOL == 1 && RAIN_RST == 0) {//雨刮复位开关 HOME_VOL==1
        if (K_ON) {
            if (!RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL && !RAIN_SPRAY && (wash_time == 0)) {
                RAIN_HIGH_OUT = 0;
                RAIN_SLOW_OUT = 0;   
                SET_RAIN_INTERVAL_CTR2;
            }
            if (RAIN_INTERVAL) {//间歇
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
                wipe_wpp_time = WIPE_WPP_DISCHARGING;//打开放电延时时间为30-10=20ms,实际测量发现输出关短有10ms延时
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

    if (wipe_wpp_time > 0)wipe_wpp_time--;//电机上电延迟时间    
}























