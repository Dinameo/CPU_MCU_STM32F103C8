#include "LED.h"


void LED_Init(LEDs_t* Leds) {
	for(uint8_t idx = 0; idx < Leds->Led_Total; idx++) {
		Leds->Leds[idx].LED_State = LED_OFF;
		LED_Ctrl(&Leds->Leds[idx]);
	}
}
void LED_Ctrl(LEDCnf_t* Led) {
	HAL_GPIO_WritePin(Led->LED_Port, Led->LED_Pin, Led->LED_State);
}