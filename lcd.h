/*
 ***********************************************************************************
 * Description	: Header file for lcd.c
 * Author	: Tarun
 * Date		: 6 December 2016
 * File name	: lcd.h
 *
 ***********************************************************************************
 */

#ifndef _LCD_H
#define _LCD_H
#include "libBBB.h"

/* Pin definitions */
#define RW	63
#define RS	65
#define E	27
#define D4	74
#define D5	75
#define D6	76
#define D7	77
#define D3	73
#define D2	72
#define D1	71
#define D0	70


/* Function prototypes */
void configLCD();
void initLCD();
void initCMD(uint8_t cmd);
void writeChar(uint8_t data);
void writeCMD(uint8_t cmd);
void writeString(int8_t* str, int16_t len);
void lcdgotoaddr(int8_t x);
void lcdgotoxy(int8_t x, int8_t y);

#endif
