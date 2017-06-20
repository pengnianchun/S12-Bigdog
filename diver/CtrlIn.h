#ifndef CTRL_IN__
	#define CTRL_IN__
#include "MCUinit.h"
#include "MC33978.h"
extern volatile SW_STATUS s_input;
#define IN_KL01			(s_input.BITS.SP0)
#define IN_KL02			(s_input.BITS.SP1)
#define IN_KL03			(s_input.BITS.SP2)
#define IN_KL04			(s_input.BITS.SP3)
#define IN_KL20			(s_input.BITS.SP4)
#define IN_KL19			(s_input.BITS.SP5)
#define IN_KL21			(s_input.BITS.SP6)
#define IN_KL22         (s_input.BITS.SP7)
#define IN_KL05			(s_input.BITS.SG0)
#define IN_KL06			(s_input.BITS.SG1)
#define IN_KL07			(s_input.BITS.SG2)
#define IN_KL08			(s_input.BITS.SG3)
#define IN_KL09			(s_input.BITS.SG4)
#define IN_KL10			(s_input.BITS.SG5)
#define IN_KL11			(s_input.BITS.SG6)
#define IN_KL12			(s_input.BITS.SG7)
#define IN_KL15			(s_input.BITS.SG8)
#define IN_KL14			(s_input.BITS.SG9)
#define IN_KL13			(s_input.BITS.SG10)
#define IN_KL18			(s_input.BITS.SG11)
#define IN_KL17			(s_input.BITS.SG12)
#define IN_KL16			(s_input.BITS.SG13)

void GetInput(void);
void GetPer(void);
void GetAdcsingleData(U8 next_ch,u16 *cont,u8 *addr_arr);
unsigned int GetBigdogAddr(void);
#endif