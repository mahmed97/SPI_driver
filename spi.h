/*-------------------------------------------------------------------------------
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Header file for the SPI driver
 *
 * Author: Mahmoud Ahmed
 *
 -------------------------------------------------------------------------------*/

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*-----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPES
 -----------------------------------------------------------------------------*/
void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(uint8 data);
uint8 SPI_receiveByte(void);
void SPI_sendString(const uint8 *Str, uint8 Str_size);
void SPI_receiveString(uint8* Str);

#endif /* SPI_H_ */
