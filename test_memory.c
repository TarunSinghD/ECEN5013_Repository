#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memory.h"
#define LENGTH 10

void print_array(uint8_t * arr, uint8_t length)
{
	uint8_t i = 0;

	for (i = 0; i < length; i++)
	{
		printf("%d ", *(arr + i));
	}

	puts("");
}

int main()
{
	system("clear");

	uint8_t source[LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	uint8_t destination[LENGTH] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	printf("Before memmove:\n");
	printf("Source array:\n");
	print_array(source, LENGTH);
	printf("Destination array:\n");
	print_array(destination, LENGTH);

	my_memmove(source, destination, LENGTH);

	printf("After memmove:\n");
	printf("Source array:\n");
	print_array(source, LENGTH);
	printf("Destination array:\n");
	print_array(destination, LENGTH);

	printf("Source array before reset:\n");
	print_array(source, LENGTH);
	my_memzero(source, LENGTH);
	printf("Source array after reset:\n");
	print_array(source, LENGTH);
		
	printf("Destination array before reset:\n");
	print_array(destination, LENGTH);
	my_reverse(destination, LENGTH);
	printf("Destination array after reset:\n");
	print_array(destination, LENGTH);

	return 0;
}
