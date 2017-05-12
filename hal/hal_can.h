#ifndef _HAL_CAN_
#define _HAL_CAN_
typedef void (*func_type)(uint32_t,uint8_t,uint8_t,uint8_t *);

#define STANDARD     0x0
#define EXTENDED     0x08

#define SRR          0x10

#define NO_ERR 0x00
#define ERR_BUFFER_FULL 0x80 

void     hal_can_init(func_type);
uint8_t  hal_Can_SendData(uint32_t id, uint8_t mode,uint8_t priority, uint8_t length, uint8_t *txdata );
void     hal_can_receive(void);
#endif
