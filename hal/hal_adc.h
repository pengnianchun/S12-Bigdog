#ifndef _HAL_ADC_
#define _HAL_ADC_


void hal_adc_init(void);
uint16_t hal_read_adc(void);
void set_adc_ch(uint8_t ch);
uint8_t get_adc_ch(void);

#endif
