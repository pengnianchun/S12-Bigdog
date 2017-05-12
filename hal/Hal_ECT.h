#ifndef HAL_etc__
   #define HAL_etc__


#define TIME_CLK_SEL_1          0
#define TIME_CLK_SEL_2          1
#define TIME_CLK_SEL_4          2
#define TIME_CLK_SEL_8          3
#define TIME_CLK_SEL_16         4
#define TIME_CLK_SEL_32         5
#define TIME_CLK_SEL_64         6
#define TIME_CLK_SEL_128        7

//TIME CLK = BUS CLK/ TIMER_PRESCALER_SEL = 24M/32 = 750KHZ
#define TIMER_PRESCALER_SEL		TIME_CLK_SEL_32
//定时时间 = ECT_TC1_IDX/TIME CLK S = 0.1MS
#define ECT_TC1_IDX				75
extern void initialize_TIM(void);

#endif
