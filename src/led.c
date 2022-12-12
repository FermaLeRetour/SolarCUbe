/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "led.h"
#include "traffic_manager.h"

// ----------------------------------------------------------------------------

void
blink_led_init(uint16_t pin)
{
  // Enable GPIO Peripheral clock
  SET_BIT(RCC->AHB1ENR, BLINK_RCC_MASKx(BLINK_PORT_NUMBER));

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = BLINK_PIN_MASK(pin);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BLINK_GPIOx(BLINK_PORT_NUMBER), &GPIO_InitStructure);

  // Start with leds turned off
  blink_led_off(12);
  blink_led_off(13);
  blink_led_off(14);
  blink_led_off(15);
}

void
blink_led_on(uint16_t index)
{
	if(index == 0){
		puts("on doit allumer maintenant 12 et 14\n======================================\n");
		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(12U), GPIO_PIN_SET);
		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(14U), GPIO_PIN_SET);

		blink_led_off(13);
		blink_led_off(15);
	} else if(index == 1){
		puts("on doit allumer maintenant 13 et 15\n======================================\n");
		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(13U), GPIO_PIN_SET);
		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(15U), GPIO_PIN_SET);

		blink_led_off(12);
		blink_led_off(14);
	} else{
		puts("Mauvaise valeur comme voie prioritaire, vueillez choisir entre 0 et 1");
	}

}

void blink_orange_led(uint16_t * priority){
	int index = get_queue_big_priority(priority);
	if(index == 0){
		puts("on doit allumerle feux orange sur 12 et 14\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
//		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(12U), GPIO_PIN_SET);
//		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(14U), GPIO_PIN_SET);

		blink_led_off(12);
		blink_led_off(14);
//		blink_led_off(13);
//		blink_led_off(15);

	} else if(index == 1){
		puts("on doit allumerle feux orange sur 13 et 15\n======================================\n");
//		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(13U), GPIO_PIN_SET);
//		HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(15U), GPIO_PIN_SET);

//		blink_led_off(12);
		blink_led_off(13);
//		blink_led_off(14);
		blink_led_off(15);
	} else{
		puts("Mauvaise valeur comme voie prioritaire, vueillez choisir entre 0 et 1");
	}
}

void
blink_led_off(uint16_t index)
{
  HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER), BLINK_PIN_MASK(index), GPIO_PIN_RESET);

}

// ----------------------------------------------------------------------------
