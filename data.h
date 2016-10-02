/*
 ***********************************************************************************
 * Description	: Header file for data.c
 * Author	: Tarun
 * Date		: 17 September 2016
 * File name	: data.h
 *
 ***********************************************************************************
 */

#ifndef DATA_H
#define DATA_H
#include <stdint.h>

int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);
int32_t my_atoi(int8_t * str);
void dump_memory(uint8_t * start, uint32_t length);
uint32_t big_to_little(uint32_t data);
uint32_t little_to_big(uint32_t data);
uint8_t my_reverse_data(int8_t * src, uint32_t length);
void my_ftoa(float n, uint8_t * res, uint8_t precision);

#endif
