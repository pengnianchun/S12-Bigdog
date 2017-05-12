#ifndef _HAL_SPI_
#define _HAL_SPI_
#include "hal_system.h"


#define SPI_CS2      PORTB_PB1
#define SPI_CS1      PORTB_PB7
#define SPI_CS0       PTJ_PTJ3

#define MPSCK         PTJ_PTJ2
#define MPMOSI        PTJ_PTJ1
#define MPMISO       PTIJ_PTIJ0  


void Hal_Spi_Init(void);
u8 SPI_Byte(byte value);

#endif
