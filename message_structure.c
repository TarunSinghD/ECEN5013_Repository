/*
 ***********************************************************************************
 * Description	: This file contains the functions for the operations to be
 *		  		  performed using a message structure
 * Author		: Tarun
 * Date			: 5 November 2016
 * File name	: message_structure.c
 *
 ***********************************************************************************
 */

#include "main.h"

uint8_t r, g, b;
float r_val, g_val, b_val;

uint16_t checksum_calculator(CI_Msg_t msg)
{
	return (uint16_t)(msg.command + msg.length + msg.data[0]);
}

void send_command(CI_Msg_t msg)
{
#if 0
	uint8_t i;

		UART0_D = msg.command;
		//checking for receive data register full

		//while (!(UART0->S1 & UART0_S1_RDRF_MASK));

		if (UART0_S1 & UART_S1_RDRF_MASK)
		{
			//Read to clear RDRF flag
			received_msg.command = UART0_D;
			//log0(c);
		}

			UART0_D = msg.length;
		//checking for receive data register full

		if (UART0_S1 & UART_S1_RDRF_MASK)
		{
			//Read to clear RDRF flag
			received_msg.length = UART0_D;
			//log0(c);
		}

			UART0_D = msg.data[0];
		//checking for receive data register full

		if (UART0_S1 & UART_S1_RDRF_MASK)
		{
			//Read to clear RDRF flag
			received_msg.data[0] = UART0_D;
			//log0(c);
		}

			UART0_D = (uint8_t)((msg.checksum & 0xff00) >> 8);
		//checking for receive data register full

		if (UART0_S1 & UART_S1_RDRF_MASK)
		{
			//Read to clear RDRF flag
			received_msg.checksum = UART0_D;
			received_msg.checksum << 8;
			//log0(c);
		}

			UART0_D = (uint8_t)(msg.checksum & 0xff);
		//checking for receive data register full

		if (UART0_S1 & UART_S1_RDRF_MASK)
		{
			//Read to clear RDRF flag
			i = UART0_D;
			received_msg.checksum |= i;
			//log0(c);
		}
#endif
		received_msg.command = UART0_getChar();
		UART0_putChar(received_msg.command);
		received_msg.command -= '0';
		received_msg.length = UART0_getChar();
		UART0_putChar(received_msg.length);
		received_msg.length -= '0';
		received_msg.data[0] = UART0_getChar();
		UART0_putChar(received_msg.data[0]);
		received_msg.data[0] -= '0';
		received_msg.checksum = UART0_getChar();
		UART0_putChar(received_msg.checksum);
		received_msg.checksum -= '0';
		received_msg.checksum <<= 8;
		received_msg.checksum |= UART0_getChar();
		UART0_putChar(received_msg.checksum);
		received_msg.checksum -= '0';
		UART0_putStr("\n\rSending command..");
}

void decode_command(CI_Msg_t * msg)
{
	if (msg->command == LED_ON)
	{
		if (msg->data[0] == RED_ON)
		{
			r = 1;
			g = 0;
			b = 0;
			RED(r_val);
			GREEN(g_val);
			BLUE(b_val);
		}

		else if (msg->data[0] == GREEN_ON)
		{
			g = 1;
			r = 0;
			b = 0;
			RED(r_val);
			GREEN(g_val);
			BLUE(b_val);
		}

		else if (msg->data[0] == BLUE_ON)
		{
			b = 1;
			r = 0;
			g = 0;
			RED(r_val);
			GREEN(g_val);
			BLUE(b_val);
		}
	}

	else if (msg->command == BRIGHTNESS_SET)
	{
		if (r == 1)
		{
			r_val = ((float)msg->data[0] / 100);
			RED(r_val);
			GREEN(g_val);
			BLUE(b_val);
		}

		else if (g == 1)
		{
			g_val = ((float)msg->data[0] / 100);
			RED(r_val);
			GREEN(g_val);
			BLUE(b_val);
		}

		else if (b == 1)
		{
			b_val = ((float)msg->data[0] / 100);
			RED(r_val);
			GREEN(g_val);
			BLUE(b_val);
		}
	}
}
