/*
 ***********************************************************************************
 * Description	: Contains the functions for SPI operations
 * Author		: Tarun
 * Date			: 5 November 2016
 * File name	: spi0.c
 *
 ***********************************************************************************
 */

#include "MKL25Z4.h"
#include "nrf.h"
#include "spi0.h"
#include "led.h"

void nrf_config_write()
{
	/* Need to get the CS pin low, to talk to the slave device */
	CS_LOW;

	/* Send the address of NRF config register to write data to it */
	nrf_write_register(NORDIC_CONFIG_REG);

	/* Configure the module to power up, and enable receive mode */
	spi_send_byte(0x03);

	/* Get the CS pin high, communication done */
	CS_HIGH;
}

void nrf_config_read()
{
	char c;

	/* Need to get the CS pin low, to talk to the slave device */
	CS_LOW;

	/* Send the address of NRF config register to read data from it */
	nrf_read_register(NORDIC_CONFIG_REG);

	/* Send dummy byte to read data from it */
    c = spi_send_byte(0xFF);

    /* Get the CS pin high, communication done */
	CS_HIGH;

	/* Read and compare if we receive the same byte that we sent */
	if (c == 0x03)
	{
		/* Glow the LED to be white, as an indicator that SPI write and read was successful */
	    RED(1);
	    GREEN(1);
	    BLUE(1);
	}
}

void nrf_write_register(uint8_t address)
{
	/* Bit 5 of the command byte should be high to write to the given address */
	spi_send_byte(0x20 | address);
}

void nrf_read_register(uint8_t address) //read command
{
	/* Bit 5 of the command byte should be low to read from the given address */
	spi_send_byte(0x00 | address);
}

void nrf_flush_tx_fifo() //empty the nrf tx buffer
{
	PTD_BASE_PTR->PCOR = 1<<0;
	spi_send_byte(0xE1);
	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_flush_rx_fifo() //empty the nrf rx buffer
{
	PTD_BASE_PTR->PCOR = 1<<0;
	spi_send_byte(0xE2);
	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_transmit_data() //send data to nrf buffer
{
	PTD_BASE_PTR->PCOR = 1<<0;
	spi_send_byte(W_TXPAYLOAD);
	spi_send_byte(0x10);
	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_read_data() //receive data from nrf buffer
{
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	spi_send_byte(R_RXPAYLOAD);
	spi_send_byte(0xff);
	c=spi_receive_byte();
	PTD_BASE_PTR->PSOR = 1<<0;

	nrf_fifostatus_read();

	if (c==0x07) //poll for data 07 from the tx
	{
		PTB_BASE_PTR->PDDR |= 1<<18;

	}
}

void nrf_status_read() //read the status register
{
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_read_register(NORDIC_STATUS_REG);
	spi_send_byte(0xFF);
	c=spi_receive_byte();
	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_rfsetup_transmit() //setup the rf register
{
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_write_register(NORDIC_RF_SETUP_REG);
	spi_send_byte(0x84);
	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_rfsetup_receive() //read the rf register
{
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_write_register(NORDIC_RF_SETUP_REG);
	spi_send_byte(0xff);
	 c=spi_receive_byte();
	PTD_BASE_PTR->PSOR = 1<<0;

}

void nrf_fifostatus_read() //read the fifo register
{
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_read_register(FIFO_STATUS_REG );
	spi_send_byte(0xff);
	 c=spi_receive_byte();
	 PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_tx_addr_read() //read the tx address register
{
	int i;
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_read_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xff);
		 c=spi_receive_byte();
	 }
	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_tx_addr_write() //write the tx address register
{
	int i;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_write_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xBB);
	 }
	 PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_rx_addr_read() //read the rx address register
{
	int i;
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_read_register(RX_ADDR_P0_REG);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xff);
		 c=spi_receive_byte();
	 }
	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_rx_addr_write() //write the rx address register
{
	int i;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_write_register(RX_ADDR_P0_REG);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xE7);
	 }
	 PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_en_rxaddr_write() //write to the datapipe register
{
	int i;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_write_register(NRF_ENRXADDR);

	spi_send_byte(0x01);

	 PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_en_rxaddr_read() //read from the datapipe register
{
	int i;
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_read_register(NRF_ENRXADDR);

	 spi_send_byte(0xff);
	 c=spi_receive_byte();

	 PTD_BASE_PTR->PSOR = 1<<0;
}


void nrf_rx_pipesize_write() //set the data pipe size
{
	int i;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_write_register(NRF_PIPESIZE);

	spi_send_byte(0x01);

	PTD_BASE_PTR->PSOR = 1<<0;
}

void nrf_rx_pipesize_read()  //read the data pipe size
{
	int i;
	char c;
	PTD_BASE_PTR->PCOR = 1<<0;
	nrf_read_register(NRF_PIPESIZE);

	 spi_send_byte(0xff);
	 c=spi_receive_byte();

	 PTD_BASE_PTR->PSOR = 1<<0;
}
