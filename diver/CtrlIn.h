#ifndef CTRL_IN__
	#define CTRL_IN__
#include "MCUinit.h"
void GetInput(void);
void GetPer(void);
void GetAdcsingleData(U8 next_ch,u16 *cont,u8 *addr_arr);
#endif