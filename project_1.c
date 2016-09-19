/*
 ***********************************************************************************
 * Description	: This file tests whether all the functions defined in memory.c
 *		  work as per requirement
 * Author	: Tarun
 * Date		: 17 September 2016
 * File name	: project_1.c
 *
 ***********************************************************************************
 */
#include "project_1.h"
#include "memory.h"
#include <stdio.h>
#define INITIAL_ELEMENT 31
#define ARRAY_LENGTH 32

void project_1_report()
{
	/* Loop variable */
	uint8_t i = 0;

	/* Create an array of 32 bytes (unsigned) */
	uint8_t array[ARRAY_LENGTH];

	/* Create 3 different pointers */
	/* First pointer will point to the beginning address of the array */
	uint8_t * aptr_1 = (uint8_t *)array;

	/* Second pointer will point to the 9th element of the array */
	uint8_t * aptr_2 = (uint8_t *)(array + 8);

	/* Third pointer will point to the 17th element of the array */
	uint8_t * aptr_3 = (uint8_t *)(array + 16);

	/* Initializing memory at two of the pointers */
	/* Initialize first 16 blocks in increments of 1 starting from 31 */
	for (i = 0; i < 16; i++)
	{
		*(aptr_1 + i) = (INITIAL_ELEMENT + i);
	}

	printf("Initialize first 16 blocks in increments of 1 starting from 31:\n");
	print_array(array, ARRAY_LENGTH);
	/* Reset all elements from the 17th element to the end of the array using memzero function */
	my_memzero(aptr_3, 16);

	printf("Reset last 16 elements to zero:\n");
	print_array(array, ARRAY_LENGTH);
	/* Use memmove to move 8 bytes from aptr_1 to aptr_3 */
	my_memmove(aptr_1, aptr_3, 8);

	printf("Move 8 elements from index 0 to index 16:\n");
	print_array(array, ARRAY_LENGTH);
	/* Use memmove to move 16 bytes from aptr_2 to aptr_1 */
	my_memmove(aptr_2, aptr_1, 16);

	printf("Move 16 elements from index 8 to index 0:\n");
	print_array(array, ARRAY_LENGTH);
	/* Use reverse on aptr_1 to reverse the entire 32 bytes */
	my_reverse(aptr_1, ARRAY_LENGTH);

	printf("Reverse the entire array:\n");
	/* Use printf to print out the entire 32 byte array in a nicely formatted way */
	print_array(array, ARRAY_LENGTH);

}

void print_array(uint8_t * arr, uint8_t length)
{
	/* Loop variable */
	uint8_t i = 0;

	/* Print the indexes */
	printf("index\t\t");
	for (i = 0; i < length; i++)
	{
		printf("%3d ", i);
	}
	printf("\n");

	printf("elements\t");
	for (i = 0; i < length; i++)
	{
		printf("%3d ", *(arr + i));
	}
	printf("\n");
}
