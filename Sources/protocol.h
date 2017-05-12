#ifndef _PROTOCOL_
#define _PROTOCOL_

#define ID_6A4      0x6a4
#define ID_454      0x454
#define ID_681      0x681
#define ID_682      0x682
#define ID_683      0x683
#define ID_671      0x671
#define ID_672      0x672
#define ID_673      0x673
#define ID_561      0x561
#define ID_562      0x562
#define ID_563      0x563
#define ID_451      0x451
#define ID_452      0x452
#define ID_453      0x453

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
   multdata front1;
   multdata front2;
   multdata top1;
   multdata top2;
   multdata block1;
   multdata block2;
}ID_6A4_TYPE;


typedef struct 
{
   uint8_t Totalmil[4];
   uint8_t PulseNum[2];
}ID_454_TYPE;


typedef struct 
{
   multdata input1;
   multdata input2;
   multdata input3;
   uint8_t  frq[2];
   uint8_t  carspeed[2];
   uint8_t  adderr;
}ID_68_TYPE;


typedef struct 
{
   uint8_t num; 
   uint8_t AD[8];   
}ID_67_TYPE;

typedef struct 
{
   uint8_t out[8];    
}ID_56_TYPE;

typedef struct 
{

   uint8_t Totalmil[4]; 
   uint8_t Singlemil[2];
   uint8_t PulseNum[2];
      
}ID_45_TYPE;

extern ID_6A4_TYPE  ID_6A4_data;
extern ID_68_TYPE  ID_681_data;
void can_receive_protocol(uint32_t ID,uint8_t mode,uint8_t length,uint8_t *data);
void ID_Select(void);
#endif
