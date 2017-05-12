#include "MCUinit.h"
#include "CtrlOut.h"


//!<Êä³ö¶Ë×ÓÓ³Éä

#define J2_07     Ctrl_Out32
#define J2_08     Ctrl_Out31
#define J2_09     Ctrl_Out36
#define J2_10     Ctrl_Out26
#define J2_11     Ctrl_Out35
#define J2_12     Ctrl_Out25

#define J3_04     Ctrl_Out34
#define J3_05     Ctrl_Out33
#define J3_07     Ctrl_Out22
#define J3_08     Ctrl_Out21
#define J3_09     Ctrl_Out28
#define J3_10     Ctrl_Out30
#define J3_11     Ctrl_Out29
#define J3_12     Ctrl_Out27
#define J3_13     Ctrl_Out2
#define J3_14     Ctrl_Out23
#define J3_15     Ctrl_Out24
#define J3_16     Ctrl_Out3
#define J3_17     Ctrl_Out4
#define J3_18     Ctrl_Out1

#define J5_16     Ctrl_Out5

#define J6_01     Ctrl_Out10
#define J6_02     Ctrl_Out15
#define J6_03     Ctrl_Out20
#define J6_04     Ctrl_Out6
#define J6_05     Ctrl_Out11
#define J6_06     Ctrl_Out16
#define J6_07     Ctrl_Out7
#define J6_08     Ctrl_Out12
#define J6_09     Ctrl_Out17
#define J6_10     Ctrl_Out8
#define J6_11     Ctrl_Out13
#define J6_12     Ctrl_Out18
#define J6_13     Ctrl_Out9
#define J6_14     Ctrl_Out14
#define J6_15     Ctrl_Out19

#define Set_Ctrl_Out(Jx_y,bCondition)		do{(Jx_y) = (bCondition)?0:1;}while(0)



void RenovatingOutput(void)
{
	Set_Ctrl_Out(J2_07,);
}


































