#ifndef MC33978_H__
   #define MC33978_H__
#include "error.h"
#include "Hal_spi.h"
/**
 * SPx/SGx selectable wetting current levels
 *	BIT2 BIT1 BIT0 WETTING CURRENT LEVEL
 *	 0    0    0      2.0mA
 *	 0    0    1      6.0mA
 *	 0    1    0      8.0mA
 *	 0    1    1      10 mA
 *	 1    0    0      12 mA
 *	 1    0    1      14 mA
 *	 1    1    0      18 mA
 *	 1    1    1      20 mA
 */
//!< 1#
//Configure the SP pin as Switch to Battery (SB) or Switch to ground (SG)
// 0 - Switch to Ground
// 1 - Switch to Battery
#define MC1_CFG_SP0_7		    0x00		//SP0-7=GND
#define MC1_Tri_state_SP0_7		0x00
#define MC1_Tri_state_SG0_7     0x00
#define MC1_Tri_state_SG8_13    0x00

typedef union {
    struct {
        unsigned SG0 : 1;
        unsigned SG1 : 1;
        unsigned SG2 : 1;
        unsigned SG3 : 1;
        unsigned SG4 : 1;
        unsigned SG5 : 1;
        unsigned SG6 : 1;
        unsigned SG7 : 1;

        unsigned SG8 : 1;
        unsigned SG9 : 1;
        unsigned SG10 : 1;
        unsigned SG11 : 1;
        unsigned SG12 : 1;
        unsigned SG13 : 1;
        unsigned SP0 : 1;
        unsigned SP1 : 1;

        unsigned SP2 : 1;
        unsigned SP3 : 1;
        unsigned SP4 : 1;
        unsigned SP5 : 1;
        unsigned SP6 : 1;
        unsigned SP7 : 1;
        unsigned INTflag : 1;
        unsigned FAULT_STATUS : 1;
    } BITS;
    unsigned char BYTES[3];
} SW_STATUS;




#define SELECT_INPUT_MC()	        do{MC_SELECT = 0;}while(0)
#define SELECT_ADC0_MC()			do{MC_SELECT = 1;}while(0)
#define SELECT_ADC1_MC()            do{MC_SELECT = 2;}while(0)
#define CANCEL_ALL()                do{MC_SELECT = -1;}while(0)

#define ADMUX_CH0			0X00
#define ADMUX_CH1           0X08

ERROR_TYPEDEF mc33978_Input_Init(void) ;
ERROR_TYPEDEF mc33978_Adc_Init(void) ;

void mc33978_DeviceConfiguration(unsigned char mode);
void mc33978_AMUX(unsigned char chs);
void mc33978_ReadSwtichStatus(void) ;
void GetAdcData(void);


#endif
