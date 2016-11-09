/*
 ***********************************************************************************
 * Description	: Header file for spi0.c
 * Author		: Tarun
 * Date			: 5 November 2016
 * File name	: spi0.h
 *
 ***********************************************************************************
 */

#ifndef SOURCES_SPI0_H_
#define SOURCES_SPI0_H_
#include <stdint.h>

/* Make the CS pin go low */
#define CS_LOW 				GPIOC_PCOR |= GPIO_PCOR_PTCO(0x10)

/* Make the CS pin go high */
#define CS_HIGH 			GPIOC_PSOR |= GPIO_PSOR_PTSO(0x10)

/* waits for the rx data ready */
#define SPI_WAIT_RX_DATA 	while (!(SPI0_S & SPI_S_SPRF_MASK))

//waits for the txef data ready ready
#define SPI_WAIT_TX_DATA 	while (!(SPI0_S & SPI_S_SPTEF_MASK))

//SPI read write register
#define SPI_RD_WR_REG 		SPI0_D



/* Function prototypes */
void spi0_init(void);
uint8_t spi_send_byte(uint8_t spiMsg);
uint8_t spi_receive_byte();
void spi_flush();



#endif /* SOURCES_SPI0_H_ */
