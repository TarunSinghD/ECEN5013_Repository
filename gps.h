/*
 ***********************************************************************************
 * Description	: Header file for gps.c
 * Author	: Tarun
 * Date		: 6 December 2016
 * File name	: gps.h
 *
 ***********************************************************************************
 */
#ifndef _GPS_H
#define _GPS_H

typedef struct {
	int degrees;
	int mins;
	int minFrac;
	char quadrasphere;
} DMData;

typedef struct {
	DMData latDM;
	DMData longDM;
	int quality;
	int numSats;
	int checkSum;
} GPSData;

typedef enum
{
	e_gps_success = 1;
	e_gps_failure = 0;
} GPS_Status_t;

void printGPSData(GPSData *gpsData);
int hexStr2Int(char* str, int sPos, int numChars);
int extractNum(char* str, int sPos, int ePos, int *valPtr);
int decodeGPSString(char *str, GPSData *gpsData);

#endif
