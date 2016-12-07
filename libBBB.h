
#ifndef _libBBB_H_
#define _libBBB_H_

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

//Type definitions
typedef struct {
      struct termios u;
}UART;

//Definitions
#define OUT	"out"
#define IN	"in"
#define ON	1
#define OFF	0

#define USR1	"usr1"
#define USR2	"usr2"
#define USR3	"usr3"
#define P8_13	"P8_13"
#define AIN0	"/AIN0"
#define AIN1	"/AIN1"
#define AIN2	"/AIN2"
#define AIN3	"/AIN3"
#define AIN4	"/AIN4"
#define AIN5	"/AIN5"
#define AIN6	"/AIN6"
#define AIN7	"/AIN7"

//USR Prototypes
int setUsrLedValue(char* led, int value);

//GPIO Prototypes
int initPin(int pinnum);
int setPinDirection(int pinnum, char* dir);
int setPinValue(int pinnum, int value);
int getPinValue(int pinnum);

//PWM Prototypes
int initPWM(int mgrnum, char* pin);
int setPWMPeriod(int helpnum, char* pin, int period);
int setPWMDuty(int helpnum, char* pin, int duty);
int setPWMOnOff(int helpnum, char* pin, int run);

//UART Prototypes
int initUART(int mgrnum, char* uartnum);
int configUART(UART u, int property, char* value);
int txUART(int uart, unsigned char data);
unsigned char rxUART(int uart);
int strUART(int uart, char* buf);

//ADC Prototypes
int initADC(int mgrnum);
int readADC(int helpnum, char* ach);

//Time Prototypes
void pauseSec(int sec);
int  pauseNanoSec(long nano);

#endif
