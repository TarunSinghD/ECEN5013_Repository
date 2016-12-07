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
	uint16_t degrees;
	uint16_t mins;
	uint16_t minFrac;
	uint8_t quadrasphere;
} DMData;

typedef struct {
	DMData latDM;
	DMData longDM;
	uint16_t quality;
	uint16_t numSats;
	uint16_t checkSum;
} GPSData;

typedef enum
{
	e_gps_success = 1;
	e_gps_failure = 0;
} GPS_Status_t;

void pruint16_tGPSData(GPSData *gpsData);
uint16_t hexStr2Int(uint8_t* str, uint16_t sPos, uint16_t numChars);
uint16_t extractNum(uint8_t* str, uint16_t sPos, uint16_t ePos, uint16_t *valPtr);
uint16_t decodeGPSString(uint8_t *str, GPSData *gpsData);

#endif
