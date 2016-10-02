/*
 ***********************************************************************************
 * Description	: This file contains the functions for basic data conversion
 *		  operations
 * Author	: Tarun
 * Date		: 17 September 2016
 * File name	: data.c
 *
 ***********************************************************************************
 */

#include "data.h"
#include <stdio.h>
#define INT_MAX 2147483647
#define INT_MIN	-2147483648
#define DECIMAL_BASE 10

/* Description:
 * This function converts the floating point number present in n to a null terminated
 * string in res, conversion is done to precision number of digits after the decimal
 * point.
 *
 * Inputs:
 * a) A pointer to the string that will store the conversted ASCII string, res.
 * b) Floating point data, n.
 * c) The number of digits to be printed after the decimal point, precision.
 *
 * Output/ Return value:
 * NA
 */
void my_ftoa(float n, uint8_t * res, uint8_t precision)
{
	/* Extract the integer part from the floating point number */
	int32_t integer_part = (int32_t) n;
	printf("Integer part:%d\n", integer_part);

	/* Temporary variable to store the string length */
	uint8_t string_length = 0;

	/* Call the itoa function to convert the integer part of the floating
	 * point number to a '\0' terminated string.
	 */
	my_itoa(res, integer_part, DECIMAL_BASE);

	/* Extract the fraction part from the floating point number */
	float f_part = n - (float) integer_part;

	/* Check if the fraction part is negative */
	if (f_part < 0)
	{
		f_part = -f_part;
	}

	/* Calculate the string length */
	while (*(res + string_length) != '\0')
	{
		string_length++;
	}

	if (precision != 0)
	{
		/* Place a decimal point after the integral part */
		*(res + string_length) = '.';

		/* Get precision number of digits after the decimal point */
		while (precision)
		{
			f_part *= DECIMAL_BASE;
			precision--;
		}

		/* Append these fracional digits */
		my_itoa(res + string_length + 1, (int32_t) f_part, DECIMAL_BASE);
	}	
}

/* Description:
 * This function converts the integer present in data to a null terminated string in
 * str, conversion is done based on the base
 *
 * Inputs:
 * a) A pointer to the string that will store the conversted ASCII string, str.
 * b) Signed integer data, data.
 * c) The base on which conversion is to be done, length.
 *
 * Output/ Return value:
 * a) A pointer to the converted string.
 * b) In case of error returns a NULL pointer. 
 * 
 * Note:
 * The function considers a negative number for base 10 only, number is considerd to
 * be unsigned for the rest of the bases.
 */
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base)
{
	/* A variable to keep track of the sign */
	uint8_t sign = 0;

	/* A loop variable */
	uint8_t i = 0;

	/* A variable to store individual digits temporarily */
	uint8_t remainder = 0;

	/* The only bases supported are 2, 10, 16. If any base other than these is
	 * passed, then it is an error */
	/* Check for the validity of the base */
	if ((base != 2) && (base != 10) && (base != 16))
	{
		/* Not a valid base, return error */
		return NULL;
	}

	/* Check if a valid pointer is passed */
	if (str == NULL)
	{
		/* return error */
		return NULL;
	}

	/* If the number is negative and the base is 2 or 16, then it is a error */
	if ((data < 0) && (base == 2))
	{
		/* return error */
		*str = 'E';
		*(str + 1) = '\0';
		return NULL;
	}

	if ((data < 0) && (base == 16))
	{
		/* return error */
		*str = 'E';
		*(str + 1) = '\0';
		return NULL;
	}

	/* Zero will not be handled by the while loop below, need to handle it
	 * seperately */
	if (data == 0)
	{
		str[i++] = '0';
		str[i] = '\0';

		return str;
	}

	/* Negative numbers supported only for base 10 */
	/* Check if the number is negative */
	if ((data < 0) && (base == 10))
	{
		sign = 1;
		data = -data;
	}

	/* Start converting the number, 1 digit at a time from LSB */
	while (data != 0)
	{
		remainder = (data % base);

		/* Converting to a digit, based on the ASCII table, 0x30 or '0'
		 * needs to be added */
		if (remainder <= 9)
		{
			*(str + i) = remainder + '0';
		}

		/* Converting to a hex digit, a-f */
		else
		{
			*(str + i) = (remainder - 10) + 'a';
		}

		data = data / base;
		i++;
	}

	/* Check if a negative sign needs to be added */
	if (sign)
	{
		*(str + i) = '-';
		i++;
	}

	/* Terminating the string with a null character */
	*(str + i) = '\0';

	/* Reversing the string */
	my_reverse_data(str, i);

	return str;
}

/* Description:
 * This function converts a string of numbers to a integer value
 *
 * Inputs:
 * a) A pointer to the string that will store the input ASCII string, str.
 *
 * Output/ Return value:
 * a) Converted integer value in case of successful conversion
 * b) INT_MIN in case of error.
 */
int32_t my_atoi(int8_t * str)
{
	/* A variable to store the return value */
	int32_t result = 0;

	/* A loop variable */
	uint8_t i = 0;

	/* Variable to keep track of the sign */
	uint8_t sign = 0;

	/* Check if a valid pointer is passed */
	if (str == NULL)
	{
		/* return error */
		return INT_MIN;
	}

	/* Check for negative numbers */
	if (*str == '-')
	{
		i++;
		sign = 1;
	}
	
	/* Sweep through the characters of the number, one digit at a time and add
	 * it to result */
	for (; (*(str + i) != '\0'); i++)
	{
		/* Limit the number to 9 digits */
		if (i > 8)
		{
			/* Number is too large, return error */
			return INT_MIN;
		}

		/* Check if the character in the string is a valid digit */
		if ((*(str + i) < '0') || (*(str + i) > '9'))
		{
			/* Invalid number, return error */
			return INT_MIN;
		}

		result = (result * 10) + (*(str + i) - '0');

	}

	/* Check for sign */
	if (sign)
	{
		result = -result;
	}

	return result;
}

/* Description:
 * This takes a pointer to memory and prints the hex output of bytes given a pointer to
 * a memory location and a length of bytes to print
 *
 * Inputs:
 * a) A pointer to memory, str.
 * b) Length of bytes to print, length.
 *
 * Output/ Return value:
 * NA
 */
void dump_memory(uint8_t * start, uint32_t length)
{
	/* A loop variable */
	uint8_t i = 0;
	
	for (i = 0; i < length; i++)
	{
		if (((i) % 8) == 0)
		{
			printf("%p\t", (start + i));
		}

		printf("%x\t", *(start + i));

		if (((i + 1) % 8) == 0)
		{
			puts("");
		}
	} 
}


/* Description:
 * Given data in big endian format, need to convert it to little endian format and
 * return this converted data.
 *
 * Inputs:
 * a) 32 bit data in big endian format.
 *
 * Output/ Return value:
 * a) 32 bit data stored in little endian format.
 */
uint32_t big_to_little(uint32_t data)
{
	/* A loop variable */
	uint8_t i = 0;
	
	/* A variable to store the result */
	uint32_t result = 0;

	uint8_t * result_ptr = (uint8_t *) &result;
	uint8_t * ptr = (uint8_t *) &data;

	/* 4 because there are 4 bytes in 32 bits */
	for (i = 0; i < 4; i++)
	{
		*(result_ptr + 3 - i) = *(ptr + i); 
	}

	return result;
}

/* Description:
 * Given data in little endian format, need to convert it to big endian format and return
 * this converted data.
 *
 * Inputs:
 * a) 32 bit data in little endian format.
 *
 * Output/ Return value:
 * a) 32 bit data stored in big endian format.
 */
uint32_t little_to_big(uint32_t data)
{
	/* A loop variable */
	uint8_t i = 0;
	
	/* A variable to store the result */
	uint32_t result = 0;

	uint8_t * result_ptr = (uint8_t *) &result;
	uint8_t * ptr = (uint8_t *) &data;

	/* 4 because there are 4 bytes in 32 bits */
	for (i = 0; i < 4; i++)
	{
		*(result_ptr + 3 - i) = *(ptr + i);
	}

	return result;
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
uint8_t my_reverse_data(int8_t * src, uint32_t length)
{
	/* Temporary array to store the reversed source array */
	uint8_t temp[length];

	/* A loop variable */
	uint8_t i = 0;

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

	return 0;
}
