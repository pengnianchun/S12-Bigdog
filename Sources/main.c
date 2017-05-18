
#include "MCUinit.h"
#include "global.h"
#include "protocol.h"
#include "Mc33978.h"
#include "ctrlin.h"
#include "ctrlout.h"


void polling(void)
{
	static u16 ms_1=0,ms_10=0,ms_100,adc_time=0;
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
				break;
			case 1:break;
			case 2:break;
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
					case 0:GetAdcData();break;
					case 1:GetInput();break;
					case 2:GetAdcData();break;
					case 3:RenovatingOutput();break;
					case 4:GetAdcData();break;
					case 5:GetPer();break;
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




void main(void) {
  GlobalParaInit();
  DisableInterrupts;
  MCU_init();               
  SELECT_INPUT_MC(); 
  fir_err.McErr1 = mc33978_Input_Init();
  SELECT_ADC0_MC();
  fir_err.McErr2 = mc33978_Adc_Init();
  SELECT_ADC1_MC();
  fir_err.McErr3 = mc33978_Adc_Init();
  CANCEL_ALL();
  delay_1ms();
  {
  	//!<Todo:获取地址
  	int temp = 0;
	//电平需要取反
	temp = Ctrl_In1?0:1;
	temp |= Ctrl_In2?0:2;
	Select_addr = temp;
	ID_Select(Select_addr);
  }
  EnableInterrupts;
  (void)hal_read_adc();//丢弃一组数据  保证数据准确
  for(;;)
  {
	polling();
  }
   
} 

                        
