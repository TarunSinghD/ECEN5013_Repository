#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "data.h"
#define MAX_LENGTH 32
#define STRING_LENGTH 10

int main()
{
	system("clear");

	#if 0
	/* number to be taken as input from the user */
	int32_t num;

	/* string to store the converted number */
	int8_t str[MAX_LENGTH];

	printf("Enter any number!!\n");
	scanf("%d", &num);

	/* Calling itoa function */
	my_itoa(str, num, 10);
	printf("Decimal number: %s\n", str);

	my_itoa(str, -num, 10);
	printf("Decimal number: %s\n", str);

	my_itoa(str, num, 2);
	printf("Binary number: %s\n", str);

	my_itoa(str, num, 16);
	printf("Hex number: %s\n", str);
	#endif

	/* Testing atoi */
	#if 0
	/* Variable to accept user input */
	int8_t str[STRING_LENGTH];	

	/* Variable to store the converted result */
	int32_t result;

	printf("Enter any number in string format:(max 9 characters)\n");
	gets(str);

	result = my_atoi(str);

	printf("Number after conversion is:%d\n", result);

	#endif

	/* Testing for memory dump */
	#if 1
	uint8_t arr[MAX_LENGTH] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88};
	dump_memory(arr, MAX_LENGTH);

	#endif	


	return 0;
}
