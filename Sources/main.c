#include <hidef.h>     
#include "derivative.h"      
#include "hal_system.h"  
#include "hal_port.h"  
#include "hal_pwm.h"  
#include "hal_spi.h"
#include "hal_can.h"
#include "hal_int.h"
#include "time_base.h"
#include "time_base.h"
#include "protocol.h"

uint16_t ss,dd;
void main(void) {

 
  System_init(); 
  Hal_Port_Init();
  ID_Select();
  Hal_Pwm_Init();
  Hal_Spi_Init();
  hal_api_init(); 
  hal_adc_init(); 
  hal_can_init(&can_receive_protocol);
  hal_irq_init();
  while(1)
  {
   dd=hal_read_adc(8);
   ss=hal_read_adc(1);
  Update_Out_Ctrl();
  }
   
}

