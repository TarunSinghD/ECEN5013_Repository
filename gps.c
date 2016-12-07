/*
 ***********************************************************************************
 * Description	: This file contains the functions for the operations to be
 *		  		  performed to extract GPS data
 * Author		: Tarun
 * Date			: 6 December 2016
 * File name	: gps.c
 *
 ***********************************************************************************
 */
#include <stdio.h>
#include "gps.h"

// $GPGGA,hhmmss.ss,ddmm.mmm,a,dddmm.mmm,b,q,xx,p.p,a.b,M,c.d,M,x.x,nnnn

// hhmmss.ss   UTC of position
// ddmm.mmm    Latitude of position
// a           N or S, latitutde hemisphere
// dddmm.mmm   Longitude of position
// b           E or W, longitude hemisphere
// q           GPS Quality indicator (0=No fix, 1=Non-differential GPS fix, 2=Differential GPS fix, 6=Estimated fix)
// xx          Number of satellites in use
// p.p         Horizontal dilution of precision
// a.b         Antenna altitude above mean-sea-level
// M           Units of antenna altitude, meters
// c.d         Geoidal height
// M           Units of geoidal height, meters
// x.x         Age of Differential GPS data (seconds since last valid RTCM transmission)
// nnnn        Differential reference station ID, 0000 to 1023


/* Description:
 * This function prints the data received from the GPS module in the required format
 *
 * Inputs:
 * A Struct type pointer to a variable of GPSData structure.
 *
 * Output/ Return value:
 * NA
 */
void printGPSData(GPSData *gpsData)
{
	printf("Lat: %dd %d.%d' %c, Long: %dd %d.%d' %c, Sats: %d, Checksum: %02X\n",
			gpsData->latDM.degrees, gpsData->latDM.mins, gpsData->latDM.minFrac, gpsData->latDM.quadrasphere,
			gpsData->longDM.degrees, gpsData->longDM.mins, gpsData->longDM.minFrac, gpsData->longDM.quadrasphere,
			gpsData->numSats, gpsData->checkSum);
}

/* Description:
 * This function is used to convert a Hex number to integer
 *
 * Inputs:
 * String from which number is to be extracted, the starting position and the number
 * of characters to be extracted.
 *
 * Output/ Return value:
 * NA
 */
int hexStr2Int(char* str, int sPos, int numChars)
{
	int val = 0;
	while (numChars > 0)   
	{
		int d = str[sPos] - 48;
		if (d > 9)
		{
		 	d -= 7;
		}
		val = (val << 4) + (d & 0xF);
		sPos++;
		numChars--;
	}

	return val;
}

/* Description:
 * This function is used to extract a number from the GPS string
 *
 * Inputs:
 * String from which number is to be extracted, the starting position and the number
 * of characters to be extracted.
 *
 * Output/ Return value:
 * Number extracted from the GPS string
 */
int extractNum(char* str, int sPos, int ePos, int *valPtr)
{
	int val = 0;
	for ( ; sPos <= ePos ; sPos++)
	{
		if (str[sPos] > 57 || str[sPos] < 48) return 1;

		val = (val*10) + str[sPos] - 48;
	}

	*valPtr = val;
	return 0;
}

/* Description:
 * Decompose the GPS string into different components 
 *
 * Inputs:
 * GPS string and structure pointer to store the different components
 *
 * Output/ Return value:
 * NA
 */
int decodeGPSString(char *str, GPSData *gpsData)
{
	const char *code = "$GPGGA";
	int i;

	// Check for the correct code
	for (i=0 ; i<6 ; i++) if (str[i] != code[i]) return 1;

	int pos = 1;
	int commaPos[14];
	int commaCount = 0;
	int starPos = 0;
	int nlPos = 0;
	char checkSum = 0;

	// Iterate through string characters
	while (pos < 100) {

		// Check for end of line
		if (str[pos] == '\n') {
			nlPos = pos;
			break;
		}

		// Check for star and update checksum
		if (starPos == 0) {
			if (str[pos] == '*') starPos = pos;
			else checkSum ^= str[pos];
		}

		// Check for comma
		if (str[pos] == ',') {
			if (commaCount < 14) commaPos[commaCount] = pos;
			commaCount ++;
		}

		pos ++;
	}

	// Check for sensible format
	if (starPos==0 || nlPos==0 || commaCount!=14 || (nlPos-starPos)!=4) return 2;

	// Compare Checksums
	gpsData->checkSum = hexStr2Int(str, starPos+1, 2);
	if (checkSum != gpsData->checkSum) return 3;

	// Extract Latitude
	int err = 0;
	err |= extractNum(str, commaPos[1]+1, commaPos[1]+2, &gpsData->latDM.degrees);
	err |= extractNum(str, commaPos[1]+3, commaPos[1]+4, &gpsData->latDM.mins);
	err |= extractNum(str, commaPos[1]+6, commaPos[1]+10, &gpsData->latDM.minFrac);
	gpsData->latDM.quadrasphere = str[commaPos[2]+1];
	if (err) return 3;

	// Extract Longtude
	err = 0;
	err |= extractNum(str, commaPos[3]+1, commaPos[3]+3, &gpsData->longDM.degrees);
	err |= extractNum(str, commaPos[3]+4, commaPos[3]+5, &gpsData->longDM.mins);
	err |= extractNum(str, commaPos[3]+7, commaPos[3]+11, &gpsData->longDM.minFrac);
	gpsData->longDM.quadrasphere = str[commaPos[4]+1];
	if (err) return 4;

	// Extract Quality
	err = extractNum(str, commaPos[6]+1, commaPos[7]-1, &gpsData->quality);
	if (err) return 5;

	// Extract Number of Satelites
	err = extractNum(str, commaPos[6]+1, commaPos[7]-1, &gpsData->numSats);
	if (err) return 6;

	return 0;
}
