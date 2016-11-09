/*
 ***********************************************************************************
 * Description	: Header file for message_structure.c
 * Author		: Tarun
 * Date			: 5 November 2016
 * File name	: message_structure.h
 *
 ***********************************************************************************
 */

#include "main.h"
//#define COMMAND

/* Global variables */
static int i = 0;
CI_Msg_t msg;

int main(void)
{
	uint8_t cmd_option, color, brightness[16], bright_val, temp[16];

	/* Initialization routines */
	UART0_init();
	led_init();

	while (1)
	{
	#if 1
		/* Write your code here */
		/* User menu */
		UART0_putStr("\n\rCommands available:");
		UART0_putStr("\n\r1. LED ON");
		UART0_putStr("\n\r2. Brightness Control");
		UART0_putStr("\n\rPlease choose a command(1 or 2)");
		/* Get user input */
		cmd_option = UART0_getChar();

		/* To turn on LED */
		if (cmd_option == '1')
		{
			while (1)
			{
				/* Choose which color LED to turn on */
				UART0_putStr("\n\rChoose color:");
				UART0_putStr("\n\r1. Red");
				UART0_putStr("\n\r2. Green");
				UART0_putStr("\n\r3. Blue");
				color = UART0_getChar();

				/* Red LED */
				if (color == '1')
				{
					/* Create the message structure */
					msg.command = (uint8_t)LED_ON;
					msg.data[0] = (uint8_t)RED_ON;
					msg.length = 5;
					msg.checksum = checksum_calculator(msg);

	#ifdef COMMAND
					UART0_putStr("\n\rCommand will be of the form:");
					my_itoa(temp, (uint8_t)msg.command, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.length, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.data[0], 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff00) >> 8, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff), 16);
					log_string(temp, string_length(temp));
	#endif
					/* Send command */
					UART0_putStr("\n\rSending command..");
					//send_command(msg);

					/* Decode the command */
					decode_command(&msg);

					break;
				}

				else if (color == '2')
				{

					/* Create the message structure */
					msg.command = (uint8_t)LED_ON;
					msg.data[0] = (uint8_t)GREEN_ON;
					msg.length = 5;
					msg.checksum = checksum_calculator(msg);

#ifdef COMMAND
					UART0_putStr("\n\rCommand will be of the form:");
					my_itoa(temp, (uint8_t)msg.command, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.length, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.data[0], 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff00) >> 8, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff), 16);
					log_string(temp, string_length(temp));
#endif

						/* Send command */
					UART0_putStr("\n\rSending command..");
					//send_command(msg);

					/* Decode the command */
					decode_command(&msg);

					break;
				}

				else if (color == '3')
				{
					/* Create the message structure */
					msg.command = (uint8_t)LED_ON;
					msg.data[0] = (uint8_t)BLUE_ON;
					msg.length = 5;
					msg.checksum = checksum_calculator(msg);
#ifdef COMMAND
					UART0_putStr("\n\rCommand will be of the form:");
					my_itoa(temp, (uint8_t)msg.command, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.length, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.data[0], 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff00) >> 8, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff), 16);
					log_string(temp, string_length(temp));
#endif
						/* Send command */
					UART0_putStr("\n\rSending command..");
					//send_command(msg);

					/* Decode the command */
					decode_command(&msg);


					break;
				}

				else
				{
					UART0_putStr("\n\rInvalid option");
				}
			}
		}

		if (cmd_option == '2')
		{
			if (color == '1')
			{
				UART0_putStr("\n\rEnter a brightness level:(Must be multiple of 5, Range: 0 - 100)");
				UART0_getString(brightness);
				UART0_putStr("\n\rYou entered");
				log_string(brightness, string_length(brightness));

				bright_val = my_atoi(brightness);

				/* Create the message structure */
					msg.command = (uint8_t)BRIGHTNESS_SET;
					msg.data[0] = (uint8_t)bright_val;
					msg.length = 5;
					msg.checksum = checksum_calculator(msg);
#ifdef COMMAND
					UART0_putStr("\n\rCommand will be of the form:");
					my_itoa(temp, (uint8_t)msg.command, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.length, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.data[0], 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff00) >> 8, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff), 16);
					log_string(temp, string_length(temp));
#endif
				/* Send command */
					UART0_putStr("\n\rSending command..");
					//send_command(msg);

					/* Decode the command */
					decode_command(&msg);

			}

			else if (color == '2')
			{
				UART0_putStr("\n\rEnter a brightness level:(Must be multiple of 5, Range: 0 - 100)");
				UART0_getString(brightness);
				UART0_putStr("\n\rYou entered");
				log_string(brightness, string_length(brightness));

				bright_val = my_atoi(brightness);

				/* Create the message structure */
					msg.command = (uint8_t)BRIGHTNESS_SET;
					msg.data[0] = (uint8_t)bright_val;
					msg.length = 5;
					msg.checksum = checksum_calculator(msg);
#ifdef COMMAND
					UART0_putStr("\n\rCommand will be of the form:");
					my_itoa(temp, (uint8_t)msg.command, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.length, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.data[0], 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff00) >> 8, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff), 16);
					log_string(temp, string_length(temp));
#endif
					/* Send command */
					UART0_putStr("\n\rSending command..");
					//send_command(msg);

					/* Decode the command */
					decode_command(&msg);
			}

			else if (color == '3')
			{
				UART0_putStr("\n\rEnter a brightness level:(Must be multiple of 5, Range: 0 - 100)");
				UART0_getString(brightness);
				UART0_putStr("\n\rYou entered");
				log_string(brightness, string_length(brightness));

				bright_val = my_atoi(brightness);

				/* Create the message structure */
					msg.command = (uint8_t)BRIGHTNESS_SET;
					msg.data[0] = (uint8_t)bright_val;
					msg.length = 5;
					msg.checksum = checksum_calculator(msg);
#ifdef COMMAND
					UART0_putStr("\n\rCommand will be of the form:");
					my_itoa(temp, (uint8_t)msg.command, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.length, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)msg.data[0], 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff00) >> 8, 16);
					log_string(temp, string_length(temp));
					UART0_putChar(0x20);

					my_itoa(temp, (uint8_t)(msg.checksum & 0xff), 16);
					log_string(temp, string_length(temp));
#endif

					/* Send command */
					UART0_putStr("\n\rSending command..");
					//send_command(msg);

					/* Decode the command */
					decode_command(&msg);
			}
		}
	#endif
	}


    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {
        i++;
    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
