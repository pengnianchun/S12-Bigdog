
#include "MCUinit.h"
#include "global.h"
#include "time_base.h"
#include "time_base.h"
#include "protocol.h"
#include "Mc33978.h"



void polling(void)
{
	static u16 ms_1=0,ms_10=0,ms_100,ms_1000,adc_time=0;
	if (TimeOutConfig)
	{
		TimeOutConfig = 0;
		if (++ms_1>=10)
		{
			ms_1 = 0;
			if (++ms_10>=10)
			{
				ms_10 = 0;
				if (++ms_100>10)
				{
					ms_100 = 0;
					if (++ms_1000>=10){
						ms_1000 = 0;
					}
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
			case 0:break;
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
					case 1:break;
					case 2:break;
					case 3:break;
					case 4:break;
					case 5:break;
					case 6:break;
					case 7:break;
					case 8:break;
					default:
						switch (ms_100)
						{
							//!<每100ms一个循环
							case 0:
								can_50ms_process0();
								break;
							case 1:
								
								mc33978_ReadSwtichStatus();break;
							case 2:break;
							case 3:break;
							case 4:break;
							case 5:break;
							case 6:break;
							case 7:break;
							case 8:break;
							default:
								switch (ms_1000)
								{
									//!<每1000ms一个循环
									case 0:break;
									case 1:break;
									case 2:break;
									case 3:break;
									case 4:break;
									case 5:break;
									case 6:break;
									case 7:break;
									case 8:break;
									default:
										break;
								}
								break;
					  }
				   break;
				}
		}
	}
}

void main(void) {
  GlobalParaInit();
  MCU_init();
  SELECT_INPUT_MC();
  fir_err.McErr1 = mc33978_Input_Init();
  SELECT_ADC0_MC();
  fir_err.McErr2 = mc33978_Adc_Init();
  SELECT_ADC1_MC();
  fir_err.McErr3 = mc33978_Adc_Init();
  CANCEL_ALL();
  hal_read_adc();//丢弃一组数据  保证数据准确

  for(;;)
  {
	polling();
  }
   
} 

                        
