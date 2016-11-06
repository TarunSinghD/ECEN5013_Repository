/*
 * uart.c
 *
 *  Created on: Oct 9, 2016
 *      Author: dtaru
 */
#include "main.h"
#include "data.h"
#include "led.h"

uint8_t c;
uint8_t count = 0;

void check(uint8_t ch)
{
	switch (ch)
	{
		case 'r':
					UART0_putStr(" You entered r\n\r");
					prev_led = 'r';
					//timer 2 channel 0 is red
					TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD * red;
					//timer 2 channel 0 is green
					TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->MOD * green;
					//timer 0 channel 1 is blue
					TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD * blue;
					break;

		case 'g':
					UART0_putStr(" You entered g\n\r");
					prev_led = 'g';
					//timer 2 channel 0 is red
					TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD * red;
					//timer 2 channel 0 is green
					TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->MOD * green;
					//timer 0 channel 1 is blue
					TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD * blue;
					break;

		case 'b':
					UART0_putStr(" You entered b\n\r");
					prev_led = 'b';
					//timer 2 channel 0 is red
					TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD * red;
					//timer 2 channel 0 is green
					TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->MOD * green;
					//timer 0 channel 1 is blue
					TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD * blue;
					break;

		case 'i':
					UART0_putStr(" You entered i\n\r");
					if ((prev_led == 'r') && (red < 0.95))
					{
						red = red + 0.05;
					}
					if ((prev_led == 'g') && (green < 0.95))
					{
						green = green + 0.05;
					}
					if ((prev_led == 'b') && (blue < 0.95))
					{
						blue = blue + 0.05;
					}
					//timer 2 channel 0 is red
					TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD * red;
					//timer 2 channel 0 is green
					TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->MOD * green;
					//timer 0 channel 1 is blue
					TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD * blue;
					break;

		case 'd':
					UART0_putStr(" You entered d\n\r");
					if ((prev_led == 'r') && (red > 0.05))
					{
						red = red - 0.05;
					}
					if ((prev_led == 'g') && (green > 0.05))
					{
						green = green - 0.05;
					}
					if ((prev_led == 'b') && (blue > 0.05))
					{
						blue = blue - 0.05;
					}
					//timer 2 channel 0 is red
					TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD * red;
					//timer 2 channel 0 is green
					TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->MOD * green;
					//timer 0 channel 1 is blue
					TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD * blue;
					break;

		default:
					UART0_putStr(" You entered invalid character\n\r");

	}
}

void log_string_param(uint8_t * str, uint8_t length, uint8_t * num, uint8_t num_size)
{
	UART0_putStr(str);
	log_string(num, num_size);
}

void log_string(uint8_t * str, uint8_t length)
{
	UART0_putStr(str);
	UART0_putChar('\n');
	UART0_putChar('\r');
}

/*
 * Description	: This function is used to log the incoming data into a circular buffer
 * Input		: Received character from UART0_Rx
 */
void log0(uint8_t ch)
{
	insertElement(&r_buff, ch);
	insertElement(&t_buff, ch);
	count++;

	if (count == 10)
	{
		r_buff.buffer[r_buff.rear + 1] = '\0';
		UART0_putStr("Circular buffer full, Transmitting contents to the Terminal\n\r");
		UART0_putStr(r_buff.buffer);
		UART0_putStr("\n\r");
		initialize(&r_buff);
		initialize(&t_buff);
		count = 0;
	}
}

void UART0_IRQHandler (void)
{
	//checking for receive data register full
	if (UART0_S1 & UART_S1_RDRF_MASK)
  	{
		//Read to clear RDRF flag
		c = UART0_D;
		log0(c);
  	}

	//Check if the transmitter is idle and transmitter register is empty
	if ((UART0_S1 & UART_S1_TDRE_MASK) && (UART0_S1 & UART_S1_TC_MASK))
	{
		//Transmitting data back to the terminal
		UART0_D  = c;
	}

	check(c);
}

void UART0_init()
{
		/*
		 * 	We can choose either the internal or the external reference clock as source.
		 *  Among the internal reference clock sources, we can choose either the high frequency 4 MHz clock or the low frequency 32 KHz clock.
		 *  I will be choosing internal reference clock and enabling it in the following line:
		 */
		//MCG_C1, internal reference clk selected for fll, enable internal reference clock
		MCG_BASE_PTR->C1 |= MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;

		//select slower internal clock, 32KHz
		MCG_BASE_PTR->C2 &= ~MCG_C2_IRCS_MASK;

		/*
		 *  Using the FLL to boost up the internal reference clock of 32 KHz to 48MHz.
		 *  The following 2 lines of code achieve this.
		 */
		//48 MHz frequency for fll
		MCG_BASE_PTR->C4 |= MCG_C4_DMX32(1);
		MCG_BASE_PTR->C4 |= MCG_C4_DRST_DRS(1);


		//Select the clock source for UART0 module. MCGFLLCLK clock or MCGPLLCLK/2 clock
		SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);

		//Select MCGFLLCLK, which is boosted up to 48 MHz
		SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;

		//Enable the clock gates for UART0 and PORTA module
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

		/*
		 * Configure interrupt to be detected on the Tx and Rx pins.
		 * Choose alternate functions for these pins, UART0_Tx and UART0_Rx
		 */
		PORTA_PCR2 |= PORT_PCR_ISF_MASK|PORT_PCR_MUX(0x2);
		PORTA_PCR1 |= PORT_PCR_ISF_MASK|PORT_PCR_MUX(0x2);

		//Disable UART0 interrupts
		UART0_C2 &= ~ (UART0_C2_TE_MASK| UART0_C2_RE_MASK);

		/*
		 * Baud rate calculation:
		 * Baud Rate = 48 Mz / (prescalar(BDH:BDL) * (OSR + 1))
		 * where;
		 * Baud rate = 9600
		 * OSR = 9
		 * prescalar = 500d (0x1f4)
		 */
		UART0_BDH = 0x01;
		UART0_BDL= 0xf4;

		//Over sampling ratio used in baud rate calculation.
		UART0_C4 = 0x09;

		//Frame configuration
		//8 bit frame, no parity
		UART0_C1 = 0x00;

		//Nothing to change here, default settings
		UART0_C3 = 0x00;
		UART0_MA1 = 0x00;
		UART0_MA2 = 0x00;
		UART0_S1 |= 0x1F;
		UART0_S2 |= 0xC0;

		/* Enabling interrupts
		 * This function enables IRQ interrupts by clearing the I-bit in the CPSR
		 */
		 __enable_irq();

		 //The function enables a device-specific interrupt in the NVIC interrupt controller.
		 NVIC_EnableIRQ(UART0_IRQn);

		 //UART0_C2 |= UART0_C2_TIE_MASK; // Transmit Interrupt Enable for TDRE

		 // Receive Interrupt Enable for RDRF
		 UART0_C2 |= UART0_C2_RIE_MASK;

		 //Enable UART0 interrupts
		 UART0_C2 |= (UART0_C2_TE_MASK| UART0_C2_RE_MASK);
}

uint8_t UART0_getChar(void)
{
    /* Wait until character has been received */
    while(!(UART0->S1 & UART0_S1_RDRF_MASK));

    /* Return the 8-bit data from the receiver */
    return UART0->D;
}

void UART0_putChar(uint8_t ch)
{
    /* Wait until space is available in the transmitter register */
    while(!(UART0->S1 & UART0_S1_TDRE_MASK));

    /* Send the char */
    UART0->D = ch;
}

void UART0_putStr(uint8_t *str)
{
	uint8_t i = 0;

    while(*(str + i) != '\0')
    {
        UART0_putChar(*(str + i));
        i++;
    }
}
