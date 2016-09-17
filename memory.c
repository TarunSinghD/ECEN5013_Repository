#include "memory.h"

/* Description:
 * This function moves "length" number of bytes of data starting from memory location pointed by src to memory location pointed by dst
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

	/* A loop variable */
	uint8_t i = 0;

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

	return 0;
}
