#ifndef _HAL_SYSTEM_
#define   _HAL_SYSTEM_

#ifndef int8_t
typedef signed char int8_t;
#endif
#ifndef int16_t
typedef signed int   int16_t;
#endif
#ifndef int32_t
typedef signed long int    int32_t;
#endif

#ifndef uint8_t
typedef unsigned char       uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int  uint16_t;
#endif
#ifndef uint32_t
typedef unsigned long int   uint32_t;
#endif


void delay_nus(unsigned int n);
void delay_1us(void);
void delay_1ms(void) ;
void delay_nms(unsigned int n) ;
void System_init(void);
#endif
