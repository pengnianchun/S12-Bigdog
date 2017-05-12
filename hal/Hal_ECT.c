#include <MC9S12G128.h>   
#include "hal_system.h"
#include "Hal_ect.h"
#include "Hal_system.h"

#if (CLOCK_BUS != 24000000)
#error("时钟不匹配需要重新配置寄存器");
#endif


/************************************************************/
/*                    初始化TIM模块                         */
/************************************************************/
void initialize_TIM(void)
{
  DDRT_DDRT0 = 0;//设置T0为输入
  DDRT_DDRT1 = 0;//设置T1为输入
  //!<定时时间为0.1ms
  PACTL = 0x50;          //始能脉冲累加器，累加上升沿
  TSCR1_TFFCA = 1;         // 定时器标志位快速清除
  TSCR1_TEN = 1;           // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
  TIOS  = 0xff;      
  TIOS_IOS0 = 0;	       //指定通道0为输入捕捉方式
  TIOS_IOS1 = 0;	       //指定通道1为输入捕捉方式
  TCTL4_EDG0x = 0x02;	   // 设置通道0为捕捉上升沿方式
  TCTL4_EDG1x = 0x02;	   // 设置通道0为捕捉上升沿方式
  TCTL1 = 0x00;	           // 后四个通道设置为定时器与输出引脚断开
  TCTL2 = 0x00;            // 前四个通道设置为定时器与输出引脚断开
  TIE   = TIE_C0I_MASK|TIE_C1I_MASK|TIE_C2I_MASK; 		// 开启中断0,1,2
  TSCR2 = TIMER_PRESCALER_SEL;	    // 预分频系数pr2-pr0:101,时钟周期为 1/750000S
  TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
  TFLG2 = 0xff;     // 清除自由定时器中断标志位
  TC1 = TCNT + 75;  
  
}


