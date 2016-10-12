/*
 * uart0.h
 *
 *  Created on: Oct 9, 2016
 *      Author: dtaru
 */

#ifndef INCLUDES_UART0_H_
#define INCLUDES_UART0_H_
#include "MKL25Z4.h"
#include "circular_buffer.h"
C_Buffer r_buff, t_buff;
uint8_t r_array[MAX_BUFFER_LENGTH], t_array[MAX_BUFFER_LENGTH];

void UART0_init();
uint8_t UART0_getChar(void);
void UART0_putChar(uint8_t ch);
void UART0_putStr(uint8_t * str);
void log_string_param(uint8_t * str, uint8_t length, uint8_t * num, uint8_t num_size);
void log_string(uint8_t * str, uint8_t length);
void check(uint8_t ch);

#endif /* INCLUDES_UART0_H_ */
