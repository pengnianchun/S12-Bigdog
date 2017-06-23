#ifndef _PROTOCOL_
#define _PROTOCOL_



#define ID_70x_BASE	0x700
#define ID_71x_BASE	0x710
#define ID_72x_BASE	0x720
#define ID_73x_BASE	0x730
#define ID_74x_BASE	0x740
#define ID_75x_BASE	0x750
#define ID_76x_BASE	0x760
#define ID_77x_BASE	0x770
#define ID_78x_BASE	0x780
#define ID_79x_BASE	0x790
#define ID_7Ax_BASE	0x7A0
#define ID_7Bx_BASE	0x7B0


typedef union {
      uint8_t Byte;
      struct {
        uint8_t bit0         :1;                                     
        uint8_t bit1         :1;                                     
        uint8_t bit2         :1;                                      
        uint8_t bit3         :1;                                       
        uint8_t bit4         :1;                                       
        uint8_t bit5         :1;                                       
        uint8_t bit6         :1;                                       
        uint8_t bit7         :1;                                       
      } Bits;
    } multdata;

typedef struct 
{
   multdata input1;   
   multdata input2;
   multdata input3;
   uint8_t addr_err;
   uint8_t per1[2];
   uint8_t per2[2];
   
}ID_70_TYPE;
typedef struct 
{
   uint8_t AD[8];   
}ID_71_TYPE;

typedef struct 
{
   multdata out[6];    
   uint8_t per[2];
}ID_72_TYPE;
typedef struct 
{
   uint8_t AD[8];   
}ID_73_TYPE;

extern ID_70_TYPE   ID_70x_data;

extern ID_72_TYPE ID_72x_data;
void can_receive_protocol(uint32_t ID,uint8_t mode,uint8_t length,uint8_t *data);
void ID_Select(int addr);
void can_process0(void) ;
void can_process1(void) ;
void can_process3(void) ;
void can_process4(void) ;
void can_process5(void) ;
void can_process6(void) ;
void can_process7(void) ;
void can_process8(void) ;
void can_process9(void) ;
void can_processA(void) ;
void can_processB(void) ;

/*********************************************************/

#define OnlineCheckID       0x131//检测节点是否在线
#define ExcuteAppID         0x139//回退到boot


void ExecutiveCheckHandle(void);
void LockAddr(void);



#endif
