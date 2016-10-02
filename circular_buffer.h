/*
 ***********************************************************************************
 * Description	: Header file for circular_buffer.c
 * Author	: Tarun
 * Date		: 25 September 2016
 * File name	: circular_buffer.h
 *
 ***********************************************************************************
 */

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#define MAX_BUFFER_LENGTH 10
#include <stdint.h>

typedef enum
{
	e_buffer_full,
	e_buffer_empty,
	e_success,
	e_buffer_not_full,
	e_buffer_not_empty

} Status;

typedef struct
{
	uint8_t front;
	uint8_t rear;
	uint8_t * buffer;

} C_Buffer;

/* Function prototypes */
void initialize(C_Buffer * c_buffer);
Status isBufferEmpty(C_Buffer * c_buffer);
Status isBufferFull(C_Buffer * c_buffer);
Status insertElement(C_Buffer * c_buffer, uint8_t element);
Status deleteElement(C_Buffer * c_buffer, uint8_t * element);

#endif
