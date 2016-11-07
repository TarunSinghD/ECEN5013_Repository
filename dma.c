/*
 ***********************************************************************************
 * Description	: This file contains the functions for dma operations
 * Author		: Tarun
 * Date			: 1 November 2016
 * File name	: dma.c
 *
 ***********************************************************************************
 */
#include "dma.h"
#include "profiler.h"
#include "data.h"
//#define __32_BIT

//unsigned char src_addr[10] = {1,3,2,4,5,7,8,5,9,6};
//unsigned char dest_addr[10] = {0,0,0,0,0,0,0,0,0,0};
uint8_t dma_complete = 1;
uint8_t dma_flag = 0;

void DMA_init(void)
{
	/* Enable clock for DMA MUX */
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	/* Enable clock for DMA module */
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	/* Enable DMA channel 0 */
	DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_ENBL_MASK);

	/* DMA channel source, choose 60 to DMA mux always enabled
	 * Ideal for memory to memory transfer
	 */
	DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_SOURCE(60));

	/* Auto increment source address by SSize */
	DMA_DCR0 |= DMA_DCR_SINC_MASK;

	/* Auto increment destination address by DSize */
	DMA_DCR0 |= DMA_DCR_DINC_MASK;

	/* 8 KB circular buffers for source and destination */
	DMA_DCR0 |= DMA_DCR_SMOD(10) | DMA_DCR_DMOD(10);

	/* Disable hardware request */
	DMA_DCR0 |= DMA_DCR_D_REQ_MASK;

	/* Enabling interrupts
	 * This function enables IRQ interrupts by clearing the I-bit in the CPSR
	 */
	 __enable_irq();

	 //The function enables a device-specific interrupt in the NVIC interrupt controller.
	 NVIC_EnableIRQ(DMA0_IRQn);

	 /* Enable interrupt on completion of DMA transfer */
	 DMA_DCR0 |= DMA_DCR_EINT_MASK;
}

void start_dma(void)
{
	/* Start timer only during he first DMA call of a block transfer */
	if (dma_complete)
	{
		dma_complete = 0;

		/* Start timer */
		start_time();
	}

	/* Start DMA */
	DMA_DCR0 |= DMA_DCR_START_MASK;
}

void my_dma_memmove(uint8_t * source, uint8_t * destination, uint8_t length)
{
	uint8_t extra_bytes = 0;

	/* Source address */
	DMA_SAR0 = (uint32_t)source;

	/* Destination address */
	DMA_DAR0 = (uint32_t)destination;

#ifdef __32_BIT
	/* 	00 32-bit
		01 8-bit
		10 16-bit
	*/
	if (length / 4)
	{
		extra_bytes = length % 4;

		/* length bytes to be transfered */
		DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(length - extra_bytes);

		/* Source size is 32 bits */
		DMA_DCR0 |= DMA_DCR_SSIZE(0);

		/* Destination size is 32 bits */
		DMA_DCR0 |= DMA_DCR_DSIZE(0);

		start_dma();

		while (dma_complete == 0);

		dma_complete = 0;
		dma_flag = 1;
		/* Extra bytes to be transferred */
		/* length bytes to be transfered */
		DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(extra_bytes);

		/* Source size is 32 bits */
		DMA_DCR0 |= DMA_DCR_SSIZE(1);

		/* Destination size is 32 bits */
		DMA_DCR0 |= DMA_DCR_DSIZE(1);

		dma_flag = 0;
		start_dma();

	}

#else
	/* length bytes to be transfered */
		DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(length);

	/* 	00 32-bit
		01 8-bit
		10 16-bit
	*/
	/* Source size is 8 bits */
	DMA_DCR0 |= DMA_DCR_SSIZE(1);

	/* Destination size is 8 bits */
	DMA_DCR0 |= DMA_DCR_DSIZE(1);

	start_dma();
	char arr1[] = {"\r\nNo of bytes transferred:"};
	my_itoa(temp_buffer, length, 10);
	log_string_param(arr1, string_length(arr1), temp_buffer, string_length(temp_buffer));
#endif

}

void DMA0_IRQHandler(void)
{
	/* Display a message to the user */
	UART0_putStr("\r\n***********************************************");
	UART0_putStr("\r\nDMA0 Complete!!");

	/* DMA transfer completed. Writing a 1 to this bit clears all DMA status bits and should be used in an
	 * interrupt service routine to clear the DMA interrupt and error bits.
	 */
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

	/* Stop  */
	if (dma_flag == 0)
	{
		end_time();
		dma_complete = 1;
		//UART0_putStr("DMA0 Complete!!");
		calc_time();
	}
}



