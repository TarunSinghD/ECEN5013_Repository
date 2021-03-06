/*
 ***********************************************************************************
 * Description	: This file contains the functions for basic memory manipulation
 *		  operations
 * Author	: Tarun
 * Date		: 17 September 2016
 * File name	: memory.c
 *
 ***********************************************************************************
 */

#include "memory.h"

/* A loop variable */
uint8_t i;

/* Description:
 * This function moves "length" number of bytes of data starting from memory location
 * pointed by src to memory location pointed by dst
 *
 * Inputs:
 * a) A pointer to the source memory location, src.
 * b) A pointer to destination memory location, dst.
 * c) The number of bytes to be moved, length.
 *
 * Output/ Return value:
 * a) Zero to indicate successful completion of memmove.
 * b) Any non zero value to indicate failure.
 */
uint8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length)
{
	/* The memory areas may overlap: copying takes place as
	 * though the bytes in src are first copied into a temporary array that
	 * does not overlap src or dest, and the bytes are then copied from the
	 * temporary array to dest. 
	 */
	/* A temporary array to store n bytes of data from the source location */
	uint8_t temp[length];

	/* Check if either the source or destination pointer is NULL */
	if ((src == NULL) || (dst == NULL))
	{
		/* return error */
		return 1;
	}

	/* Copying the source contents to temporary memory location */
	for (i = 0; i < length; i++)
	{
		*(temp + i) = *(src + i);
	}

	/* Copying from the temporary memory location to destination */
	for (i = 0; i < length; i++)
	{
		*(dst + i) = *(temp + i);
	}

	/* Successful completion */
	return 0;
}

/* Description:
 * This function fills "length" number of bytes of data starting from memory location 
 * pointed by src
 *
 * Inputs:
 * a) A pointer to the source memory location, src.
 * b) The number of bytes to be reset to zero, length.
 *
 * Output/ Return value:
 * a) Zero to indicate successful completion of memmove.
 * b) Any non zero value to indicate failure.
 */
uint8_t my_memzero(uint8_t * src, uint32_t length)
{
	/* Check if the source pointer is NULL */
	if (src == NULL)
	{
		/* return error */
		return 1;
	}

	/* Reset the memory location 1 byte at a time */
	for (i = 0; i < length; i++)
	{
		*(src + i) = 0;
	}

	/* Successful completion */
	return 0;
}
	
/* Description:
 * This function fills "length" number of bytes of data starting from memory location
 * pointed by src
 *
 * Inputs:
 * a) A pointer to the source memory location, src.
 * b) The number of bytes to be considered for reverse, length.
 *
 * Output/ Return value:
 * a) Zero to indicate successful completion of memmove.
 * b) Any non zero value to indicate failure.
 */
uint8_t my_reverse(uint8_t * src, uint32_t length)
{
	/* Temporary array to store the reversed source array */
	uint8_t temp[length];

	/* Check if the source pointer is NULL */
	if (src == NULL)
	{
		/* return error */
		return 1;
	}

	/* Start swapping the characters, first character with the last character, second
	 * character with the second last and so on */
	for (i = 0; i < length; i++)
	{
		*(temp + i) = *(src + length - 1 - i);
	}

	/* String the reversed array back to the source array */
	for (i = 0; i < length; i++)
	{
		*(src + i) = *(temp + i);
	}

	/* Successful completion */
	return 0;
}
