/*
 ***********************************************************************************
 * Description	: This file contains the functions for the operations to be
 *		  performed on a circular buffer
 * Author	: Tarun
 * Date		: 25 September 2016
 * File name	: circular_buffer.c
 *
 ***********************************************************************************
 */

/* Brief overview of the implementation:
 * Two variables are used to demarcate the extremities of the buffer:
 * a) front : The front end of the buffer where elements exit the buffer
 * b) rear : The rear end of the buffer where elements can be appended
 *
 * Buffer empty:
 * front = rear = -1
 *
 * Single element:
 * front = rear
 *
 * Inserting element:
 * Done at the rear end, usually by incrementing rear, and appending the element at
 * this incremented new position.
 *
 * Deleting element:
 * Done at front end, usually by incrementing the value of front
 */

#include "circular_buffer.h"

/* Description:
 * Please note that this function needs to be called first before you can use the
 * buffer. This function initializes the circular buffer to be an empty buffer. 
 *
 * Inputs:
 * A Struct type pointer to a variable of C_Buffer.
 *
 * Output/ Return value:
 * NA
 */
void initialize(C_Buffer * c_buffer)
{
	/* Initialize the buffer to empty condition */
	c_buffer->front = -1;
	c_buffer->rear = -1;
}

/* Description:
 * This function checks if the buffer is empty or not  
 *
 * Inputs:
 * A Struct type pointer to a variable of C_Buffer.
 *
 * Output/ Return value:
 * Status indicating whether the buffer is empty or not
 */
Status isBufferEmpty(C_Buffer * c_buffer)
{
	/* Check for the buffer empty condition */
	if (c_buffer->front == -1)
	{
		return e_buffer_empty;
	}

	return e_buffer_not_empty;
}

/* Description:
 * This function checks if the buffer is full or not.  
 *
 * Inputs:
 * A Struct type pointer to a variable of C_Buffer.
 *
 * Output/ Return value:
 * Status indicating whether the buffer is full or not
 */
Status isBufferFull(C_Buffer * c_buffer)
{
	/* Check for the buffer full condition */
	if ((c_buffer->front == 0 && c_buffer->rear == (MAX_BUFFER_LENGTH - 1))
		       	|| (c_buffer->front == (c_buffer->rear + 1)))
	{
		return e_buffer_full;
	}

	return e_buffer_not_full;
}

/* Description:
 * This function inserts an element at the rear end of the buffer  
 *
 * Inputs:
 * A Struct type pointer to a variable of C_Buffer and an element to be inserted
 *
 * Output/ Return value:
 * Status indicating whether the insertion was successful or not
 */
Status insertElement(C_Buffer * c_buffer, uint8_t element)
{
	/* Check if the buffer is full before proceeding with insert */
	if (isBufferFull(c_buffer) == e_buffer_full)
	{
		return e_buffer_full;
	}

	/* Check if the buffer is empty */
	if (isBufferEmpty(c_buffer) == e_buffer_empty)
	{
		c_buffer->front = 0;
	}

	/* Check for the corner condition, if true need to return back to the
	 * beginning of the buffer
       	 */
	if (c_buffer->rear == (MAX_BUFFER_LENGTH - 1))
	{
		c_buffer->rear = 0;
	}

	/* Increment rear to point to the next free location in the memory */
	else
	{
		c_buffer->rear = c_buffer->rear + 1;
	}


	/* Store the required element at the position pointed to by rear */
	*((c_buffer->buffer) + c_buffer->rear) = element;

	/* Successful insertion operation */
	return e_success;
}

/* Description:
 * This function deletes an element at the front end of the buffer.
 *
 * Inputs:
 * A Struct type pointer to a variable of C_Buffer, and a pointer where the 
 * deleted element is stored.
 *
 * Output/ Return value:
 * Status indicating whether the deletion operation was successful or not
 */
Status deleteElement(C_Buffer * c_buffer, uint8_t * element)
{
	/* Check if the queue is empty, if it is empty, then there is nothing 
	 * to delete.
	 */
	if (isBufferEmpty(c_buffer) == e_buffer_empty)
	{
		return e_buffer_empty;
	}

	*element = *((c_buffer->buffer) + c_buffer->front);

	/* Single element condition */
	if (c_buffer->front == c_buffer->rear)
	{
		/* After deletion of single element, need to initialize to single
		 * element condition.  
		 */
		initialize(c_buffer);
	}

	/* Corner condition for deletion */
	else if (c_buffer->front == (MAX_BUFFER_LENGTH - 1 ))
	{
		/* front needs to loop back to zero, as MAX_BUFFER_LENGTH - 1 is the 
		 * last position.  
		 */
		c_buffer->front = 0;
	}

	/* Point to the next element in the buffer, after deleting the current one */
	else
	{
		c_buffer->front = c_buffer->front + 1;
	}
	
	/* Successful deletion */
	return e_success;
}
