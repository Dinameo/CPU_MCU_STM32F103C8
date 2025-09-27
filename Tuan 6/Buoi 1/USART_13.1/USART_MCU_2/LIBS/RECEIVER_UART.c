#include "main.h"
#include "RECEIVER_UART.h"
#include "LED.h"

void UartReceiver(UART_HandleTypeDef* huart, LEDs_t* Leds) {
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE)) {
		uint8_t buffer;
		HAL_UART_Receive(huart, &buffer, 1, HAL_MAX_DELAY);
		uint8_t LedPos = (buffer >> 4) & 0x0F;
		uint8_t State  = buffer&0x0F;
		if(State == ON) {
			Leds->Leds[LedPos].LED_State = LED_ON;
		} else if(State == OFF) {
			Leds->Leds[LedPos].LED_State = LED_OFF;
		}
		LED_Ctrl(&Leds->Leds[LedPos]);
	}
}