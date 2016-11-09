/*
 * led.h
 *
 *  Created on: Oct 10, 2016
 *      Author: dtaru
 */

#ifndef INCLUDES_LED_H_
#define INCLUDES_LED_H_

#include "MKL25Z4.h"
#define RED(x)		TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD * x
#define GREEN(x)	TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->MOD * x
#define BLUE(x)		TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD * x

void led_init(void);

uint8_t prev_led;
float blue, red, green;

#endif /* INCLUDES_LED_H_ */
