#ifndef _HAL_PWM_
#define _HAL_PWM_

#define Per_Value         PWMPER67
#define Dty_Value         PWMDTY67

//ռ�ձ�=[(PWM_CH67_PER��PWM_CH67_DTY)/ PWM_CH67_PER]*100%
#define PWM_CH67_DTY		(50000u)	
// PWMx = PWM_CH67_PER * bus clk SB = PWM_CH67_PER * 24M/2/240 = 20ns 50khz
#define PWM_CH67_PER		(50000u)
//!<����ͨ��7ΪPWM���

void Hal_Pwm_Init(void);
//���� = per * bus clk SB
//ռ�ձ� = (per - dty)/per*100%
void Change_Pwm(uint16_t per,uint16_t dty);

#endif
