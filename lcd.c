/*
 ***********************************************************************************
 * Description	: This file contains the main file for LCD operations
 * Author	: Tarun
 * Date		: 6 December 2016
 * File name	: lcd.c
 *
 ***********************************************************************************
 */

#include "lcd.h"

int16_t main()
{
	uint8_t c = 0x30;
	uint8_t buf[] = "Hello World";
	int16_t i = 0;

	//configure the pins for the lcd
	configLCD();
	printf("lcd configured\n");

	//initialize screen and settings
	initLCD();

	//Clear display
	writeCMD(0x01);
	printf("LCD init\n");

	/* Write H at a time */
	lcdgotoxy(1, 1);
	pauseSec(2);
	writeChar('H');
	printf("write H\n");

	/*
	   for(i = 0; i < strlen(buf); i++)
	   writeChar(buf[i]);
	 */

	//write the string hello to the screen
	writeString(buf, strlen(buf));

	while(1);
	{
		lcdgotoxy(1, 1);
		writeChar('H');
	}

	return 0;
}

/* Description:
 * This function is used to configure the GPIO pins
 *
 * Inputs:
 * NA
 *
 * Output/ Return value:
 * NA
 */
void configLCD()
{
	//first we need to apply the overlay so the pins are
	//configured to be gpio
	FILE *cfg;

	cfg = fopen("/sys/devices/bone_capemgr.9/slots", "w");

	if(cfg == NULL)
	{
		 printf("Slots failed to open\n");
	}

	fseek(cfg,0,SEEK_SET);
	fprintf(cfg, "BBB-LCD");
	fflush(cfg);
	fclose(cfg);

	//now they are gpio so we need to export the pins
	initPin(RW);
	initPin(RS);
	initPin(E);
	initPin(D4);
	initPin(D5);
	initPin(D6);
	initPin(D7);
	initPin(D0);
	initPin(D1);
	initPin(D2);
	initPin(D3);

	//now they are exported so we set the direction to out
	setPinDirection(RW,OUT);
	setPinDirection(RS,OUT);
	setPinDirection(E,OUT);
	setPinDirection(D4,OUT);
	setPinDirection(D5,OUT);
	setPinDirection(D6,OUT);
	setPinDirection(D7,OUT);
	setPinDirection(D0, OUT);
	setPinDirection(D1, OUT);
	setPinDirection(D2, OUT);
	setPinDirection(D3, OUT);

	//finally set pins to initial state
	setPinValue(E,OFF);
}

/* Description:
 * This function is used to initialize LCD
 *
 * Inputs:
 * NA
 *
 * Output/ Return value:
 * NA
 */
void initLCD()
{
	setPinValue(E, OFF);
	//2 ms delay
	pauseNanoSec(2000000);

	writeCMD(0x30);

	//5 ms delay
	pauseNanoSec(5000000);

	writeCMD(0x30);

	//100 us delay
	pauseNanoSec(100000);

	writeCMD(0x30);

	//5 ms delay
	pauseNanoSec(5000000);

	//Display off
	writeCMD(0x08);

	//5 ms delay
	pauseNanoSec(5000000);

	//Display Clear
	writeCMD(0x01);

	//5 ms delay
	pauseNanoSec(5000000);

	//Entry mode set
	writeCMD(0x06);

	//100 ms delay
	pauseNanoSec(100000000);

	//Function set
	writeCMD(0x38);

	//100 ms delay
	pauseNanoSec(100000000);

	//Display ON/OFF control
	writeCMD(0x0C);

	//100 ms delay
	pauseNanoSec(100000000);

	//Entry mode set
	writeCMD(0x06);
}

void initCMD(uint8_t cmd)
{
	//bring rs low for command
	setPinValue(RS,OFF);
	pauseNanoSec(500000);

	//send highest nibble first
	setPinValue(E,ON);
	setPinValue(D7,((cmd >> 7) & 1));
	setPinValue(D6,((cmd >> 6) & 1));
	setPinValue(D5,((cmd >> 5) & 1));
	setPinValue(D4,((cmd >> 4) & 1));
	pauseNanoSec(500000);
	setPinValue(E,OFF);
	pauseNanoSec(500000);
}

void writeChar(uint8_t data)
{
	//bring rs high for int16_t8_tacter
	pauseNanoSec(500000);
	setPinValue(RS,ON);
	setPinValue(RW, OFF);
	pauseNanoSec(500000);

	//send highest nibble first
	setPinValue(D7,((data >> 7) & 1));
	setPinValue(D6,((data >> 6) & 1));
	setPinValue(D5,((data >> 5) & 1));
	setPinValue(D4,((data >> 4) & 1));
	setPinValue(D3,((data >> 3) & 1));
	setPinValue(D2,((data >> 2) & 1));
	setPinValue(D1,((data >> 1) & 1));
	setPinValue(D0,(data & 1));
	pauseNanoSec(1000000);
	setPinValue(E,ON);
	pauseNanoSec(1000000);
	setPinValue(E, OFF);
	pauseNanoSec(1000000);

}

void writeCMD(uint8_t cmd)
{
	//bring rs low for command
	pauseNanoSec(500000);
	setPinValue(RS,OFF);
	setPinValue(RW, OFF);
	pauseNanoSec(500000);

	setPinValue(D7,((cmd >> 7) & 1));
	setPinValue(D6,((cmd >> 6) & 1));
	setPinValue(D5,((cmd >> 5) & 1));
	setPinValue(D4,((cmd >> 4) & 1));
	setPinValue(D3,((cmd >> 3) & 1));
	setPinValue(D2,((cmd >> 2) & 1));
	setPinValue(D1,((cmd >> 1) & 1));
	setPinValue(D0,(cmd & 1));
	pauseNanoSec(1000000);
	setPinValue(E,ON);
	pauseNanoSec(1000000);
	setPinValue(E, OFF);
	pauseNanoSec(1000000);
}

void writeString(int8_t* str, int16_t len)
{
	int16_t i;

	for(i = 0; i < len; i++)
	{
		writeChar(str[i]);
	}
}

/* Description  : This function goes to specific location on LCD
 * Input        : DDRAM Address of LCD
 * Return       : NA
 */
void lcdgotoaddr(int8_t x)
{
	/* Command 0x80 to set address */
	writeCMD(0x80 + x);
}



/* Description  : This function goes to a particular cursor location
 * Input        : Line number, and Character number within the line
 * Return       : NA
 */
void lcdgotoxy(int8_t x, int8_t y)
{
	if (x == 1)
	{
		lcdgotoaddr(0x00 + y - 1);
	}

	else if (x == 2)
	{
		lcdgotoaddr(0x40 + y - 1);
	}

	else if (x == 3)
	{
		lcdgotoaddr(0x10 + y - 1);
	}
	else if (x == 4)
	{
		lcdgotoaddr(0x50 + y - 1);
	}
}
