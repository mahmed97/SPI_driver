/*-------------------------------------------------------------------------------
 *
 * Module: SPI
 *
 * File Name: spi.c
 *
 * Description: Header file for the SPI driver
 *
 * Author: Mahmoud Ahmed
 *
 -------------------------------------------------------------------------------*/

#include "spi.h"

void SPI_initMaster(void) {
	/*---------Master Pins Configurations--------------
	 * SS(PB4)----->OUTPUT
	 * MOSI(PB5)--->OUTPUT
	 * MISO(PB6)--->INPUT
	 * SCK(PB7)---->OUTPUT
	 * -----------------------------------------------*/
	SET_BIT(DDRB, PB4);
	SET_BIT(DDRB, PB5);
	CLEAR_BIT(DDRB, PB6);
	SET_BIT(DDRB, PB7);

	/*---------SPCR--------------
	 * SPE = 1 SPI ENABLE
	 * MSTR = 1 Master Select
	 * (SPR1 = 0) (SPR0 = 0) SPI_CLK= F_OSC/4
	 * -----------------------------------------------*/
	SPCR = (1 << SPE) | (1 << MSTR);
	/*---------SPSR--------------
	 * (SPI2X = 0) SPI_CLK= F_OSC/4
	 * -----------------------------------------------*/
}

void SPI_initSlave(void) {
	/*---------Slave Pins Configurations--------------
	 * SS(PB4)----->INPUT
	 * MOSI(PB5)--->INPUT
	 * MISO(PB6)--->OUTPUT
	 * SCK(PB7)---->INPUT
	 * -----------------------------------------------*/
	CLEAR_BIT(DDRB, PB4);
	CLEAR_BIT(DDRB, PB5);
	SET_BIT(DDRB, PB6);
	CLEAR_BIT(DDRB, PB7);

	/*---------SPCR--------------
	 * SPE = 1 SPI ENABLE
	 * MSTR = 0 Slave Select
	 * (SPR1 = 0) (SPR0 = 0) SPI_CLK= F_OSC/4
	 * -----------------------------------------------*/
	SPCR = (1 << SPE);

	/*---------SPSR--------------
	 * (SPI2X = 0) SPI_CLK= F_OSC/4
	 * -----------------------------------------------*/
}

void SPI_sendByte(uint8 data) {
	SPDR = data;
	while (BIT_IS_CLEAR(SPSR, SPIF)) {
		/* Wait until SPIF = 1 */
	}
}

uint8 SPI_receiveByte(void) {
	while (BIT_IS_CLEAR(SPSR, SPIF)) {
		/* Wait until SPIF = 1 */
	}
	/* Return data from SPDR */
	return SPDR;
}

void SPI_sendString(const uint8 *Str, uint8 Str_size) {
	/* Send string length */
	SPI_sendByte(Str_size);
	while (*Str != '\0') {
		SPI_sendByte(*Str);
		Str++;
	}
}

void SPI_receiveString(uint8* Str) {
	uint8 i = 0, length;
	/* Receive string length from other Micro-Controllers */
	length = SPI_receiveByte();
	while (i <= length) {
		*Str = SPI_receiveByte();
		Str++;
		i++;
	}
	*Str = '\0';
}
