/*
 ***********************************************************************************
 * Description	: This file contains the main file for GPS operations
 * Author	: Tarun
 * Date		: 6 December 2016
 * File name	: gps.c
 *
 ***********************************************************************************
 */

#include <stdio.h>
#include "gps.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main(void)
{
	/* Local variables */
	uint8_t buffer[200], format[7], latitude[10], longitude[10];
	float longitude_float, latitude_float;
	GPSData gpsData;
	uint16_t i = 0, j = 0, valid = 0, l = 0; 
	uint8_t count = 0;
	uint8_t lat_flag = 0;

	/* Enabling UART 1 */
	/* UART 1 is connected to the GPS module */
	system("echo BB-UART1 >> /sys/devices/bone_capemgr.9/slots");

	/* Enabling UART 2 */
	/* UART 2 is connected to the Xbee tranceiver */
	system("echo BB-UART2 >> /sys/devices/bone_capemgr.9/slots");

	/* UART 1 file pointer, File pointer for GPS device */
	FILE *fp;
	fp = fopen("/dev/ttyO1", "r");

	/* UART 2 file pointer, File pointer for Xbee device */
	FILE *file;
	file = fopen("/dev/ttyO2", "w+");

	while (1)
	{
		/* Get the NMEA strings from GPS module */
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

		/* Start fetching the NMEA strings */
		for (i = 0; i < 100; i++)
		{
			if (buffer[i] == '$')
			{
				/*******************************************************************************
				$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70
              			    1    2    3    4    5     6    7    8      9     10  11   12


				      1   220516     Time Stamp
				      2   A          validity - A-ok, V-invalid
				      3   5133.82    current Latitude
				      4   N          North/South
				      5   00042.24   current Longitude
				      6   W          East/West
				      7   173.8      Speed in knots
				      8   231.8      True course
				      9   130694     Date Stamp
				      10  004.2      Variation
				      11  W          East/West
				      12  *70        checksum
				********************************************************************************/
				for (j = 0; j < 5; j++)
				{
					/* Start storing the first five characters after '$' character into format */
					format[j] = buffer[++i];
				}

				format[j] = '\0';

				/* Compare the string with GPRMC, which contains relevant GPS data */
				if (strcmp(format, "GPRMC") == 0)
				{
					/* Check if valid data is received */
					if (buffer[i + 13] == 'A')
					{
						valid = 1;
						printf("\nValid data received!!\n");
						fprintf(file, "\nValid data received");
					}

					/* Check if GPS is still waiting for a fix */
					else if (buffer[i + 13] == 'V')
					{
						valid = 0;
						printf("\nWaiting for valid data\n");
						fprintf(file, "\nWaiting for valid data");
					}
				}

				/* Start extracting relevant GPS data */
				if ((strcmp(format, "GPGGA")) && (valid == 1))
				{
					for (j = 0, i += 13, l = 0; j < 9; j++, i++)
					{
						if ((buffer[i] >= '0') && (buffer[i] <= '9') || (buffer[i] == '.'))
						{
							latitude[l++] = buffer[i];
							count++;
						}
					}
					latitude[l] = '\0';

					/* Print the extracted latitude information */
					if ((latitude[0] == '4') && (latitude[1] == '0'))
					{
						count = 0;
						printf("Actual Latitude: %s\n", latitude);

						/* Transmit latitude data to the Xbee tranceiver */
						fprintf(file, "Latitude:%s\n", latitude);
						lat_flag = 1;
					}


					/* Extracting longitude */
					for (j = 0, i += 3, l = 0; j < 10; j++, i++)
					{
						if ((buffer[i] >= '0') && (buffer[i] <= '9') || (buffer[i] == '.'))
						{
							longitude[l++] = buffer[i];
						}
					}
					longitude[l] = '\0';

					/* Print the extracted longitude information */
					if (lat_flag)
					{
						printf("Actual Longitude:%s\n", longitude);

						/* Transmit latitude data to the Xbee tranceiver */
						fprintf(file, "Latitude:%s\n", longitude);
						lat_flag = 0;
					}
				}
			}
		}
	}

	/* Close the file pointers */
	fclose(fp);
	fclose(file);

	return 0;
}
