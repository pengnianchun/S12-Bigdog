#ifndef _HAL_PWM_
#define _HAL_PWM_

#define Per_Value         PWMPER67

#define Dty_Value         PWMDTY67

void Hal_Pwm_Init(void);

void Change_Pwm(uint16_t per,uint16_t dty);

#endif
