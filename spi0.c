/*
 ***********************************************************************************
 * Description	: Contains the functions for SPI operations
 * Author		: Tarun
 * Date			: 5 November 2016
 * File name	: spi0.c
 *
 ***********************************************************************************
 */


#include "spi0.h"
#include "MKL25Z4.h"

void spi0_init(void)
{

	/* SPI0 module initialization */
	/* Turn on clock to SPI0 module */
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	/* Turn on clock to Port D module */
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;


	GPIOC_PSOR |= GPIO_PSOR_PTSO(0x10); // PTD0 = 1 (CS inactive)
	GPIOC_PDDR |= GPIO_PDDR_PDD(0x10); // PTD0 pin is GPIO output

	//Set PTC4 to mux 1 [SPI0_PCS0]
	PORTC_PCR4 = PORT_PCR_MUX(0x1);

	//Set PTC5 to mux 2 [SPI0_SCK]
	PORTC_PCR5 = PORT_PCR_MUX(0x2);

	//Set PTC6 to mux 2 [SPI0_MOSI]
	PORTC_PCR6 = PORT_PCR_MUX(0x2);

	//Set PTC7 to mux 2 [SPIO_MISO]
	PORTC_PCR7 = PORT_PCR_MUX(0x2);


	//SETUP SPI0 PERIPHERAL
	// Enable SPI0 module, master mode //SETS SPI ENABLE AND SPI MASTER BITS
	SPI0_C1 = SPI_C1_SPE_MASK | SPI_C1_MSTR_MASK;

	// BaudRate = BusClock / ((SPPR+1) * 2^(SPR+1)) = 20970000 / ((4+1) * 2^(2+1)) = 524.25 kHz
	SPI0_BR = SPI_BR_SPPR(0x03) | SPI_BR_SPR(0x08) ;
  }

uint8_t spi_send_byte(uint8_t spiMsg)
{
	/* Wait till byte is transmitted */
	SPI_WAIT_TX_DATA;
	SPI_RD_WR_REG = spiMsg;

	/* Wait till byte is received */
	SPI_WAIT_RX_DATA;
	spiMsg = SPI_RD_WR_REG;

	return spiMsg;
}

uint8_t spi_receive_byte()
{
	uint8_t spiMsg;

	SPI_WAIT_RX_DATA;

	/* Read byte from SPI buffer */
	spiMsg = SPI_RD_WR_REG;
	return spiMsg;

}

void spi_flush()
{
	SPI0_C1 &= 0xBF;
	spi0_init();
}



