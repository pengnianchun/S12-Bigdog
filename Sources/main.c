
#include "MCUinit.h"
#include "global.h"
#include "protocol.h"
#include "Mc33978.h"
#include "ctrlin.h"
#include "ctrlout.h"
#include "config.h"
//!<校验字必须为32byte整数倍
static const char _AppcheckString[64]  @0x4000= "S12G128 Bigdog";


void polling(void)
{
	
	if (TimeOutConfig)
	{
		TimeOutConfig = 0;
		if (++ms_1>=10)
		{
			ms_1 = 0;
			if (++ms_10>=10)
			{
				ms_10 = 0;
				if (++ms_100>=20)
				{
					ms_100 = 0;
				}              
			}
		}
		if (adc_cont<ADC_BUF_MAX)
		{
			u16_adc_buff[adc_cont++] = hal_read_adc();
		}
		switch (ms_1)   
		{
			//!<每1ms一个循环
			case 0:
				if(OnlineCheckConfig == 1)
				{
					OnlineCheckConfig = 0;
					ExecutiveCheckHandle();
				}
				break;
			case 1:_FEED_COP();break;
			case 2:wipe_delay();
				break;
			case 3:break;
			case 4:break;
			case 5:break;
			case 6:break;
			case 7:break;
			case 8:break;
			default:
				switch (ms_10)
				{
					//!<每10ms一个循环
					//!<开关量读取逻辑在输出之前，输出尽量靠近开关量采集
					case 0:GetAdcData();break;
					case 1:GetInput();break;
					case 2:GetAdcData();break;
					case 3:RenovatingOutput();break;
					case 4:GetAdcData();break;
					case 5:GetPer();
					       LockAddr();break;
					case 6:GetAdcData();break;
					case 7:can_process0();break;
					case 8:GetAdcData();break;
					default:
						switch (ms_100)
						{
							//!<每200ms一个循环
							case 0:can_process1();break;
							case 1:can_process3();break;
							case 2:can_process4();break;
							case 3:can_process5();break;
							case 4:can_process6();break;
							case 5:can_process7();break;
							case 6:can_process8();break;
							case 7:can_process9();break;
							case 8:can_processA();break;
							case 9:can_processB();break;
							case 10:break;
							case 11:break;
							case 12:break;
							case 13:break;
							case 14:break;
							case 15:break;
							case 16:break;
							case 17:break;
							case 18:break;
							default:
								break;
					  }
				   break;
				}
		}
	}
}


static int Task = 0;
#define TASK_IDLE		    0
#define TASK_RUN		    1
#define TASK_DORMANT_READY	2
#define TASK_DORMANT	    3

#define SetTaskMode(mod)	do{Task = mod;}while(0)


void main(void) {
  GlobalParaInit();
  DisableInterrupts;
  CPMUFLG_PORF = 1;//清楚上电复位标志;
  MCU_init();      
  SELECT_INPUT_MC(); 
  fir_err.McErr1 = mc33978_Input_Init();
  SELECT_ADC0_MC();
  fir_err.McErr2 = mc33978_Adc_Init();
  SELECT_ADC1_MC();
  fir_err.McErr3 = mc33978_Adc_Init();
  CANCEL_ALL();
  POWER_CTRL_5V = 1;
  POWER_CTRL_12V =1;
  Ctrl_ctr = 0;
  delay_nms(10);
  //ID_Select(0);//!<默认选择地址，否者容易地址为0时无法输出电阻
  //(void)hal_read_adc();//丢弃一组数据  保证数据准确
#ifndef DEBUG
  for(;;)
  {
  	switch(Task)
  	{
		case TASK_IDLE:
			if ((Ctrl_In1 == 0)||(Ctrl_In2 == 0))
			{
				SetTaskMode(TASK_RUN);
				POWER_CTRL_5V = 1;
  				POWER_CTRL_12V =1;
				Ctrl_ctr = 0;
				ID_Select(0);//!<默认选择地址，否者容易地址为0时无法输出电阻
				CANCEL_ALL();
				(void)hal_read_adc();//丢弃一组数据  保证数据准确
				SELECT_ADC0_MC();
				GlobalParaInit();
				delay_nms(10);
				EnableInterrupts;
			}

			break;
		case TASK_RUN:
			polling();
			if ((Ctrl_In1 != 0)&&(Ctrl_In2 != 0))
			{
				SetTaskMode(TASK_DORMANT_READY);
			}
			break;
		case TASK_DORMANT_READY:
			if (Select_addr != FRONT_MODULE_ADDR)
			{
				DisableInterrupts;
				SetTaskMode(TASK_DORMANT);
			}
			else
			{
				if (HOME_VOL) {
					if ((RAIN_HIGH_OUT == 0) && (RAIN_SLOW_OUT == 0)) {
						if (RAIN_INTERVAL_CTR == 1) {
							DisableInterrupts;
							delay_nms(50);
							SetTaskMode(TASK_DORMANT);
						}
					}
				}
				polling();

			}
			break;
		case TASK_DORMANT:
			DisableInterrupts;
			InitOutput();
			RAIN_INTERVAL_CTR = 0;
			POWER_CTRL_5V = 0;
 			POWER_CTRL_12V =0;
			SetTaskMode(TASK_IDLE);
			//DisableInterrupts;
			break;
  	}
	
	if (ExecutiveEraseFlashConfig == 1)
	{
		//!<收到更新程序命令
		DisableInterrupts;
		memset(&ID_72x_data,0,8);
		InitOutput();
		asm call 0xf000,00
	}
  }
#else
	Ctrl_Out1 = 1;Ctrl_Out2 = 1;Ctrl_Out3 = 1;Ctrl_Out4 = 1;Ctrl_Out5 = 1;Ctrl_Out6 = 1;Ctrl_Out7 = 1;Ctrl_Out8 = 1;Ctrl_Out9 = 1;Ctrl_Out10 = 1;
	Ctrl_Out11 = 1;Ctrl_Out12 = 1;Ctrl_Out13 = 1;Ctrl_Out14 = 1;Ctrl_Out15 = 1;Ctrl_Out16 = 1;Ctrl_Out17 = 1;Ctrl_Out18 = 1;Ctrl_Out19 = 1;Ctrl_Out20 = 1;
	Ctrl_Out21 = 1;Ctrl_Out22 = 1;Ctrl_Out23 = 1;Ctrl_Out24 = 1;Ctrl_Out25 = 1;Ctrl_Out26 = 1;Ctrl_Out27 = 1;Ctrl_Out28 = 1;Ctrl_Out29 = 1;Ctrl_Out30 = 1;
	Ctrl_Out31 = 1;Ctrl_Out32 = 1;Ctrl_Out33 = 1;Ctrl_Out34 = 1;Ctrl_Out35 = 1;Ctrl_Out36 = 1;

	for(;;)
	{
		

		
		
	}

#endif

} 

                        
