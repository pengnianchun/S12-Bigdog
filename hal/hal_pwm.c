#include <MC9S12G128.h>   
#include "hal_system.h" 
#include "hal_pwm.h" 
#include "hal_system.h"

#if (CLOCK_BUS != 24000000)
#error("时钟不匹配需要重新配置寄存器");
#endif
void Hal_Pwm_Init(void)
{
 
  /* ### Init_PWM init code */
  /* PWME: PWME7=0,PWME6=0,PWME5=0,PWME4=0,PWME3=0,PWME2=0,PWME1=0,PWME0=0 */
  PWME = 0x00U;                        /* Disable all PWM channels */
  /* PWMPOL: PPOL7=0,PPOL6=0,PPOL5=0,PPOL4=0,PPOL3=0,PPOL2=0,PPOL1=0,PPOL0=0 */
  PWMPOL = 0x00U;                                      
  /* PWMCLK: PCLK7=0,PCLK6=0,PCLK5=0,PCLK4=0,PCLK3=0,PCLK2=0,PCLK1=0,PCLK0=0 */
  PWMCLK = 0x80U;          //选择CLK SB 作为 时钟输入                           
  /* PWMCAE: CAE7=0,CAE6=0,CAE5=0,CAE4=0,CAE3=0,CAE2=0,CAE1=0,CAE0=0 */
  PWMCAE = 0x00U;                                      
  /* PWMCTL: CON67=1,CON45=0,CON23=0,CON01=0,PSWAI=0,PFRZ=0 */
  PWMCTL = 0x80U;                                      
  /* PWMDTY67: PWMDTY67=0x0834 */
  PWMDTY67 = PWM_CH67_DTY;                            
  /* PWMPER67: PWMPER67=0x138A */
  PWMPER67 = PWM_CH67_PER;                            
  /* PWMSCLA: BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  PWMSCLA = 0x00U;           //clk sa = clk a/2/256                           
  /* PWMSCLB: BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  PWMSCLB = 240;          //clk sb = clk b/2/12                             
  /* PWMPRCLK: PCKB2=0,PCKB1=0,PCKB0=0,PCKA2=0,PCKA1=0,PCKA0=0 */
  PWMPRCLK = 0;  	//                                    
  /* PWME: PWME7=1,PWME6=0,PWME5=0,PWME4=0,PWME3=0,PWME2=0,PWME1=0,PWME0=0 */
  PWME = 0x80U;                        /* Enable only configured PWM channels */
  /* ### */
  
 }
//周期 = per * bus clk SB
//占空比 = (per - dty)/per*100%
 void Change_Pwm(uint16_t per,uint16_t dty)
 {
  
  Per_Value=per;
  Dty_Value=dty;
  
 }
 
 