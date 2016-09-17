#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "data.h"
#define MAX_LENGTH 32

int main()
{
	system("clear");

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

	return 0;
}
