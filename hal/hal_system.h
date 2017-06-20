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

typedef unsigned char u8,U8;
typedef signed char s8,S8;
typedef unsigned int u16,U16;
typedef signed int s16,S16;
typedef unsigned long u32,U32;
typedef signed long s32,S32;

typedef volatile unsigned char vu8;
typedef volatile signed char vs8;
typedef volatile unsigned int vu16;
typedef volatile signed int vs16;
typedef volatile unsigned long vu32;
typedef volatile signed long vs32;




//PLLCLK=2¡ÁOSCCLK¡Á(SYNDIV+1)/(REFDIV+1), fbus=PLLCLK/2
#define CLOCK_OSC		(8000000ul)
#define CLOCK_REFDIV	(0x01)
#define CLOCK_SYNDIV	(0x05)
#define CLOCK_BUS		(CLOCK_OSC*(CLOCK_SYNDIV+1)/(CLOCK_REFDIV+1))

void delay_nus(unsigned int n);
void delay_1us(void);
void delay_1ms(void) ;
void delay_nms(unsigned int n) ;
void System_init(void);
#endif
