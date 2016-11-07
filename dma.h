/*
 ***********************************************************************************
 * Description	: Header file for dma.c
 * Author		: Tarun
 * Date			: 1 November 2016
 * File name	: dma.h
 *
 ***********************************************************************************
 */

#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_

#include "main.h"

uint8_t dma_flag;
void DMA_init(void);
void start_dma(void);
void DMA_transfer(uint8_t * source, uint8_t * destination, uint8_t length);

#endif /* INCLUDES_DMA_H_ */
