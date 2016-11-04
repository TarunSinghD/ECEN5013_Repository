#include <stdio.h>
#include <string.h>
#include "data.h"

int main()
{
	int zeros;
       	float	n;
	int array[40];

	printf("Enter any number:\n");
	scanf("%f", &n);

	printf("Enter the number of zeros:\n");
	scanf("%d", &zeros);

	printf("Number = %f", n);

	my_ftoa(n, array, 2);


	printf("NUmber: %s\n", array);

	return 0;
}
