/*
 * led.h
 *
 *  Created on: Oct 10, 2016
 *      Author: dtaru
 */

#ifndef INCLUDES_LED_H_
#define INCLUDES_LED_H_

#include "MKL25Z4.h"
void led_init(void);

uint8_t prev_led;
float blue, red, green;

#endif /* INCLUDES_LED_H_ */
