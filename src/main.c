#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "led.h"
#include "diag/trace.h"
#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------
//
// Semihosting STM32F4 empty sample (trace via STDOUT).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the STDOUT output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace-impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

uint8_t queue_a, queue_b, queue_c, queue_d;
uint8_t priority[2] = {0};
//static uint8_t lastButton_A_Status = GPIO_PIN_RESET;
uint8_t quota = 0; //nombre de véhicule qui doit libérer la voie avant de basculer

void Init_PushButton(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef pushButton;

	pushButton.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
	pushButton.Pin |= GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	pushButton.Mode = GPIO_MODE_INPUT;
	pushButton.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &pushButton);
}

void show_quota(){
	trace_printf("quota : %u\n", quota);
}

uint8_t check_value(uint8_t value)
{
	if(value < 0 || value >= 250)
		return quota = 0;
	return value;
}

int
main(int argc, char* argv[])
{
	Init_PushButton();
	blink_led_init(BLINK_PIN_NUMBER_12);
	blink_led_init(BLINK_PIN_NUMBER_13);
	blink_led_init(BLINK_PIN_NUMBER_14);
	blink_led_init(BLINK_PIN_NUMBER_15);

	// simulation ici

	queue_a =12, queue_b =9, queue_c = 8, queue_d = 10;

//	STM32F401VE
	while(1){
		// ====================== Début de la file a ===================================
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
			++queue_a;
			trace_printf("bingo, queue_a = %d\n", queue_a);
		}

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)){
			--queue_a;
			--quota;
			show_quota();
//			timer_sleep(BLINK_OFF_TICKS);
//			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}

		// ====================== Fin de la file a ===================================

		// ====================== Début de la file b ===================================
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)){
			++queue_b;
//			timer_sleep(BLINK_OFF_TICKS);
//			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)){
			--queue_b;
			--quota;
			show_quota();
//			timer_sleep(BLINK_OFF_TICKS);
//			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}
		// ====================== Fin de la file b ===================================

		// ====================== Début de la file C ===================================

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)){
			++queue_c;
//			timer_sleep(BLINK_OFF_TICKS);
//			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)){
			--queue_c;
			--quota;
			show_quota();
//			timer_sleep(BLINK_OFF_TICKS);
//			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}
		// ====================== Fin de la file C ===================================

		// ====================== Début de la file d ===================================

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)){
			++queue_d;
//			timer_sleep(BLINK_OFF_TICKS);
//			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)){
			--queue_d;
			--quota;
			show_quota();
//			timer_sleep(BLINK_OFF_TICKS);
//			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}
		// ====================== Début de la file C ===================================

		if(quota == 0){
			quota = analyse_queues_situation(&queue_a, &queue_b, &queue_c, &queue_d, priority);
			show_quota();
		}

		if(quota == 2){
			blink_orange_led(priority);
		}

		timer_sleep(BLINK_OFF_TICKS);

		quota = check_value(quota);
		queue_a = check_value(queue_a);
		queue_b = check_value(queue_b);
		queue_c = check_value(queue_c);
		queue_d = check_value(queue_d);

		show_quota();
	}
  return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
