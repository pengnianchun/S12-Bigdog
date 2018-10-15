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

POUT gPout,pout;

void rain_wape(void);

static u16 per_old = 0;
void InitOutput(void)
{
    Ctrl_Out1 = 0;
    Ctrl_Out2 = 0;
    Ctrl_Out3 = 0;
    Ctrl_Out4 = 0;
    Ctrl_Out5 = 0;
    Ctrl_Out6 = 0;
    Ctrl_Out7 = 0;
    Ctrl_Out8 = 0;
    Ctrl_Out9 = 0;
    Ctrl_Out10 = 0;
    Ctrl_Out11 = 0;
    Ctrl_Out12 = 0;
    Ctrl_Out13 = 0;
    Ctrl_Out14 = 0;
    Ctrl_Out15 = 0;
    Ctrl_Out16 = 0;
    Ctrl_Out17 = 0;
    Ctrl_Out18 = 0;
    Ctrl_Out19 = 0;
    Ctrl_Out20 = 0;
    Ctrl_Out21 = 0;
    Ctrl_Out22 = 0;
    Ctrl_Out23 = 0;
    Ctrl_Out24 = 0;
    Ctrl_Out25 = 0;
    Ctrl_Out26 = 0;
	Ctrl_Out27 = 0;
    Ctrl_Out28 = 0;
    Ctrl_Out29 = 0;
    Ctrl_Out30 = 0;
  	Ctrl_Out31 = 0;
    Ctrl_Out32 = 0;
    Ctrl_Out33 = 0;
    Ctrl_Out34 = 0;
    Ctrl_Out35 = 0;
    Ctrl_Out36 = 0;
}

#define OPENLOAD_VALUE     6
//#define PROTECT_THRESHOLD  60
#define PROTECT_MAX_CNT    100
//12 --1.8A

//23--3.6A
//64--10A
//115 -18A


unsigned char PROTECT_THRESHOLD[40]= {12,90,90,90,
                                      60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,
                                      18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18
                                     };
unsigned char pf[40]={0};                 //故障保护缓存
static unsigned char pcnt[40]={0}; //过载时间计数器
unsigned int pcur[40]={0};                //输出电流缓存

#if 1
static void POUT_Protect(void)
{
    unsigned char i,j,dump;
    for(j = 0; j < 5; j++)
    {
        dump = gPout.BYTES[j];
        for (i = 0; i < 8; i++)
        {
            if ((dump & 0x01) == 1)  //一个AD值大约等于156.2mA
            {
                if (pf[j * 8 + i] != 0x02)//没有故障
                {
                    pcur[j * 8 + i] = u16_admux_data[j * 8 + i + 1];//检测电流
                    if (pcnt[j * 8 + i] >= (PROTECT_MAX_CNT))//100个周期电流都大于保护阈值1000ms
                    {
                        pout.BYTES[j] = (pout.BYTES[j] & ~(0x01 << i));//关闭输出
                        pf[j * 8 + i] = 0x02; //故障保护
                    }
                    else
                    {
                        pout.BYTES[j]= (pout.BYTES[j] | (0x01 << i));//打开输出
                        if (pcur[j * 8 + i] < OPENLOAD_VALUE) pf[j * 8 + i] = 0x01; //开路(输出小于1200mA)
                        else pf[j * 8 + i] = 0x00; //正常
                    }
                    if (pcur[j * 8 + i] > (PROTECT_THRESHOLD[j * 8 + i]))//检测输出电流过载的时间长度
                    {
                        pcnt[j * 8 + i]++;
                    }
                    else//恢复时间
                    {
                        if (pcnt[j * 8 + i] > 0) pcnt[j * 8 + i]--;
                    }
                }
            }
            else
            {
                pout.BYTES[j] = (pout.BYTES[j] & ~(0x01 << i));
                pcnt[j * 8 + i] = 0;
                pf[j * 8 + i] = 0;
            }
            dump = dump >> 1;
        }
    }

	if(pcnt[0]>200)
		{
	pcnt[1] = 0;

	}
	Ctrl_Out1 = pout.BITS.O1;
    Ctrl_Out2 = pout.BITS.O2;
    Ctrl_Out3 = pout.BITS.O3;
    Ctrl_Out4 = pout.BITS.O4;
    Ctrl_Out5 = pout.BITS.O5;
    Ctrl_Out6 = pout.BITS.O6;
    Ctrl_Out7 = pout.BITS.O7;
    Ctrl_Out8 = pout.BITS.O8;
    Ctrl_Out9 = pout.BITS.O9;
    Ctrl_Out10 = pout.BITS.O10;
    Ctrl_Out11 = pout.BITS.O11;
    Ctrl_Out12 = pout.BITS.O12;
    Ctrl_Out13 = pout.BITS.O13;
    Ctrl_Out14 = pout.BITS.O14;
    Ctrl_Out15 = pout.BITS.O15;
    Ctrl_Out16 = pout.BITS.O16;
    Ctrl_Out17 = pout.BITS.O17;
    Ctrl_Out18 = pout.BITS.O18;
    Ctrl_Out19 = pout.BITS.O19;
    Ctrl_Out20 = pout.BITS.O20;
    Ctrl_Out21 = pout.BITS.O21;
    Ctrl_Out22 = pout.BITS.O22;
    Ctrl_Out23 = pout.BITS.O23;
    Ctrl_Out24 = pout.BITS.O24;
    Ctrl_Out25 = pout.BITS.O25;
    Ctrl_Out26 = pout.BITS.O26;
    Ctrl_Out27 = pout.BITS.O27;
    Ctrl_Out28 = pout.BITS.O28;
    Ctrl_Out29 = pout.BITS.O29;
    Ctrl_Out30 = pout.BITS.O30;
    Ctrl_Out31 = pout.BITS.O31;
    Ctrl_Out32 = pout.BITS.O32;
    Ctrl_Out33 = pout.BITS.O33;
    Ctrl_Out34 = pout.BITS.O34;
    Ctrl_Out35 = pout.BITS.O35;
    Ctrl_Out36 = pout.BITS.O36;
}
#endif

void RenovatingOutput(void)
{
    u16 dty,per;
    u8 i;


		
		gPout.BYTES[1]=ID_72x_data.out[1].Byte;
		

		for( i=3;i<6;i++){
		
		gPout.BYTES[i]=ID_72x_data.out[i].Byte;
		
	}
 	gPout.BITS.O2 =  ID_72x_data.out[0].Bits.bit1;
	gPout.BITS.O3  =  ID_72x_data.out[0].Bits.bit2;
 	gPout.BITS.O5 =  ID_72x_data.out[0].Bits.bit3;
	gPout.BITS.O6  =  ID_72x_data.out[0].Bits.bit4;
 	gPout.BITS.O7 =  ID_72x_data.out[0].Bits.bit5;
	gPout.BITS.O8  =  ID_72x_data.out[0].Bits.bit6;

	gPout.BITS.O17 =  ID_72x_data.out[2].Bits.bit0;
	gPout.BITS.O18  =  ID_72x_data.out[2].Bits.bit1;
 	gPout.BITS.O19 =  ID_72x_data.out[2].Bits.bit2;
	gPout.BITS.O20  =  ID_72x_data.out[2].Bits.bit3;
 	gPout.BITS.O21 =  ID_72x_data.out[2].Bits.bit4;
	gPout.BITS.O22  =  ID_72x_data.out[2].Bits.bit5;
	gPout.BITS.O24 =  ID_72x_data.out[2].Bits.bit7;

	// gPout.BITS.O23 = 0;
    if (Select_addr != FRONT_MODULE_ADDR)
    {
        //!<用于雨刮，喷嘴控制。
        gPout.BITS.O1 = ID_72x_data.out[0].Bits.bit0;
        gPout.BITS.O4   = ID_72x_data.out[0].Bits.bit3;
        gPout.BITS.O23  = ID_72x_data.out[2].Bits.bit6;
    }
    else
    {
        rain_wape();
    }


    POUT_Protect();   


    per = ID_72x_data.per[0] + ID_72x_data.per[1] *256;
    per = 50000u/per;
    if(per == 0)//周期period
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

#define RAIN_SLOW_OUTbuffer gPout.BITS.O4
#define RAIN_HIGH_OUTbuffer gPout.BITS.O1
#define SPRAY_OUTbuffer  gPout.BITS.O23



//雨刮程序
unsigned char DELAY_START = 0;
unsigned char DELAY_END = 0;

void rain_wape(void)
{
    static unsigned char RAIN_RST = 0;
    //RAIN_SLOW	       雨刮慢档
    //RAIN_INTERVAL	   雨刮间歇档
    //RAIN_HIGH	       雨刮快档

    if (wipe_int_time > 0) wipe_int_time--; //雨刮间歇时间
    if (wash_time > 0) wash_time--; //雨刮洗涤时间
    if (wipe_stop_time > 0)wipe_stop_time--;
	

    if (K_ON && RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL)  //慢档
    {
        if (DELAY_START == 0)
        {
            DELAY_START = 1;
            wipe_motoron_delay = WIPE_WPP_TIMEOUT;//200ms等待后开始执行电机
        }
        RAIN_FAST_CTL = 0;
        if (wipe_motoron_delay == 0)
        {
            RAIN_SLOW_CTL = 1;
            RAIN_SLOW_OUTbuffer = 1; //雨刮慢档电机
            RAIN_HIGH_OUTbuffer = 0;
            wash_time = 0;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    }
	
/*********************************慢档工作处理完成*************************************/

   if (K_ON && RAIN_HIGH && !RAIN_INTERVAL)  //快档 快档慢档同时有效时，快档有效
    {
        if (DELAY_START == 0)
        {
            DELAY_START = 1;
            wipe_motoron_delay = WIPE_WPP_TIMEOUT;//200ms等待后开始执行电机
        }
        RAIN_FAST_CTL = 0;
        if (wipe_motoron_delay == 0)
        {
            RAIN_SLOW_OUTbuffer = 0;
            RAIN_SLOW_CTL = 0;;
            RAIN_HIGH_OUTbuffer = 1; //雨刮快档电机
            wash_time = 0;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    }

   /*********************************快档工作处理完成*************************************/
   
    if (K_ON && RAIN_SPRAY)
    {
        SPRAY_OUTbuffer = 1; //喷水电机
        if (DELAY_START == 0)
        {
            DELAY_START = 1;
            wipe_motoron_delay = WIPE_WPP_TIMEOUT;//200ms等待后开始执行电机
        }
        RAIN_FAST_CTL = 0;
        if (wipe_motoron_delay == 0)
        {
            RAIN_SLOW_CTL = 1;;
            RAIN_SLOW_OUTbuffer = 1; //雨刮慢档电机
            RAIN_HIGH_OUTbuffer = 0;
            wash_time = WASH_TIMEOUT;
            DELAY_START = 0;
            DELAY_END = 0;
        }
    }
    else
    {
        if (wash_time <= 0) SPRAY_OUTbuffer = 0;//喷水开关关闭
    }
    if (K_ON && !RAIN_SLOW && !RAIN_HIGH && RAIN_INTERVAL)  //间歇档
    {
   
        if (wipe_int_time == 0)
        {
            if (DELAY_START == 0)
            {
                DELAY_START = 1;
                wipe_motoron_delay = WIPE_WPP_TIMEOUT;//200ms等待后开始执行电机
            }
            RAIN_FAST_CTL = 0;
	  
            if (wipe_motoron_delay == 0)
            {
                RAIN_SLOW_CTL = 1;
                RAIN_SLOW_OUTbuffer = 1;
                RAIN_HIGH_OUTbuffer = 0;
                wash_time = 0;
                DELAY_START = 0;
                DELAY_END = 0;
            }
        }

		
    }
    //雨刮无操作，需要停止工作
    if (!K_ON || (!RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL && !RAIN_SPRAY && (wash_time == 0)))
    {
       
        if (!HOME_VOL && RAIN_HIGH_OUT && wipe_stop_time > 0)
        {
            RAIN_HIGH_OUTbuffer = 0;
            RAIN_SLOW_OUTbuffer = 1;
            SPRAY_OUT = 0;
            RAIN_SLOW_CTL = 1;
            wipe_int_time = 0;
        }
        if (wipe_stop_time == 0)   //雨刮操作开关断开 20内强制关闭雨刮 保护雨刮电机
        {
            RAIN_HIGH_OUTbuffer = 0;
            RAIN_SLOW_OUTbuffer = 0;
            SPRAY_OUT = 0;
            RAIN_SLOW_CTL = 1;
            wipe_int_time = 0;
        }
    }
    else
    {
        wipe_stop_time = WIPE_STOP_TIMEOUT;
    }

    if (HOME_VOL == 1 && RAIN_RST == 0)  //雨刮复位开关 HOME_VOL==1  第一次到复位处
    {
        if (K_ON)
        {
            if (!RAIN_SLOW && !RAIN_HIGH && !RAIN_INTERVAL && !RAIN_SPRAY && (wash_time == 0))
            {
                RAIN_HIGH_OUTbuffer = 0;
                RAIN_SLOW_OUTbuffer = 0;
	       RAIN_FAST_CTL = 0;
                RAIN_SLOW_CTL = 0;//--------------------------------
            }
            if (RAIN_INTERVAL)  //间歇
            {
                RAIN_SLOW_OUTbuffer = 0;
                RAIN_SLOW_CTL = 1;
                wipe_int_time = WIPE_WPP_TIMEOUT;

            }
        }
        else
        {
            RAIN_HIGH_OUTbuffer = 0;
            RAIN_SLOW_OUTbuffer = 0;
            SPRAY_OUT = 0;
            RAIN_SLOW_CTL = 1;
            wipe_int_time = 0;
        }
    }

    if (HOME_VOL)
    {
        if ((RAIN_HIGH_OUT == 0) && (RAIN_SLOW_OUT == 0))
        {
            if (DELAY_END == 0)
            {
                DELAY_END = 1;
                wipe_motoron_delay = WIPE_WPP_DISCHARGING;//打开放电延时时间为30-10=20ms,实际测量发现输出关断有10ms延时
            }
            if (wipe_motoron_delay == 0)
            {
                RAIN_HIGH_OUT = 0;
                RAIN_FAST_CTL = 1;
	       RAIN_SLOW_CTL = 0;
                DELAY_END = 0;
                DELAY_START = 0;
            }
        }
    }

    RAIN_RST = HOME_VOL;
	
}



void wipe_delay(void)   //1ms
{

    if (wipe_motoron_delay > 0)wipe_motoron_delay--;//电机上电延迟时间
}























