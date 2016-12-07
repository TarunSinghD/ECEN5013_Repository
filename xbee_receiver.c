/*
 ***********************************************************************************
 * Description	: This file contains the functions for the operations to be
 *		  		  performed to receive GPS data using Xbee protocol
 * Author		: Tarun
 * Date			: 6 December 2016
 * File name	: xbee_receiver.c
 *
 ***********************************************************************************
 */

#include "xbee_receiver.h"

void uart_init()
{
	/* Enabling UART 1 */
	/* UART 1 is connected to the Xbee module */
	system("echo BB-UART1 >> /sys/devices/bone_capemgr.9/slots");
}

uint8_t main()
{
	/* Local variables */
	uint8_t buffer[200];

	/* UART 1 file pointer, File pointer for Xbee device */
	FILE *fp;
	fp = fopen("/dev/ttyO1", "r");

	while (1)
	{
		/* Get the NMEA strings from Xbee module */
		if (fgets(buffer, 100, fp) == NULL) 
		{
			printf("Got NULL\n");
			break;
		}

		/* Check if there is error reading from the device */
		if (ferror(fp)) 
		{
			printf ("Error Reading\n");
			break;
		}
		
		/* Print the GPS coordinates received from the Xbee module */
		fputs(buffer);
	}

	/* Close open file */
	fclose(fp);
}
