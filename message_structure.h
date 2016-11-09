/*
 ***********************************************************************************
 * Description	: Header file for message_structure.c
 * Author		: Tarun
 * Date			: 5 November 2016
 * File name	: message_structure.h
 *
 ***********************************************************************************
 */


#ifndef INCLUDES_MESSAGE_STRUCTURE_H_
#define INCLUDES_MESSAGE_STRUCTURE_H_

#define MAX_DATA_SIZE 10

/* Brightness macros */
#define TEN 	0.1
#define TWENTY 	0.2
#define THIRTY 	0.3
#define FORTY 	0.4
#define FIFTY 	0.5
#define SIXTY 	0.6
#define SEVENTY 0.7
#define EIGHTY 	0.8
#define NINTY 	0.9
#define CENT 	1.0

/* This enum has the set of commands to control the LED color and brightness */
typedef enum
{
	LED_ON 			= 0x01,
	BRIGHTNESS_SET 	= 0x02,
	ACK_PACKET 		= 0xA1,
	NACK_PACKET 	= 0xA0
} Command_e;

/* This is the payload structure
 * One command byte
 * Next byte contains the payload length
 * A variable data field
 * 2 bytes of checksum
 */
typedef struct
{
	Command_e 	command; 					// Command operation
	uint8_t 	length; 					// Size of message
	uint8_t 	data[MAX_DATA_SIZE]; 		// Variable size data
	uint16_t 	checksum; 					// Error detection checksum
} CI_Msg_t;

CI_Msg_t received_msg;

/* This enum has the DATA to indicate different brightness levels */
typedef enum
{
	TEN_PERCENT 	= 0x10,
	TWENTY_PERCENT 	= 0x20,
	THIRTY_PERCENT 	= 0x30,
	FORTY_PERCENT 	= 0x40,
	FIFTY_PERCENT 	= 0x50,
	SIXTY_PERCENT 	= 0x60,
	SEVENTY_PERCENT = 0x70,
	EIGHTY_PERCENT 	= 0x80,
	NINTY_PERCENT 	= 0x90,
	HUNDRED_PERCENT = 0xFF

} LED_brightness_e;

/* This enum selects which LED to blink */
typedef enum
{
	RED_ON 		= 0x01,
	GREEN_ON 	= 0x02,
	BLUE_ON 	= 0x03,
} LED_select_e;

typedef enum
{
	CHKSUM_FAIL = 0xE0,
	CHKSUM_PASS = 0xE1
} CHKSUM_Status_e;

uint16_t checksum_calculator();
void decode_command(CI_Msg_t * msg);
void send_command(CI_Msg_t msg);

#endif /* INCLUDES_MESSAGE_STRUCTURE_H_ */
