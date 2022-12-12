#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----- LED definitions ------------------------------------------------------

// STM32F4DISCOVERY definitions (the GREEN led, D12, active high)
// (SEGGER J-Link device name: STM32F407VG).

#define BLINK_PORT_NUMBER               (3)
#define BLINK_PIN_NUMBER_12             (12)
#define BLINK_PIN_NUMBER_13             (13)
#define BLINK_PIN_NUMBER_14             (14)
#define BLINK_PIN_NUMBER_15             (15)
#define BLINK_ACTIVE_LOW                (0)


#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

// ----------------------------------------------------------------------------

extern
void
blink_led_init(uint16_t pin);

// ----------------------------------------------------------------------------

void
blink_led_on(uint16_t index);

void
blink_led_off(uint16_t index);

void blink_orange_led(uint16_t *);


// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

#endif // BLINKLED_H_
