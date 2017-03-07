#ifndef _HAL_INT_
#define _HAL_INT_

void hal_irq_init(void) ;
void hal_api_init(void) ;
void pulse_count(void);

void fre_200ms_process(void);
void can_50ms_process0(void);
void can_500ms_process1(void);
void can_100ms_process2(void);
void can_100ms_process3(void);
void can_100ms_process4(void);

#endif
