#ifndef __LED_H
#define __LED_H

#include "main.h"
#define LED_ON	GPIO_PIN_SET
#define LED_OFF	GPIO_PIN_RESET

typedef struct {
	GPIO_TypeDef* LED_Port;
	uint16_t			LED_Pin;
	uint8_t LED_State;
} LEDCnf_t;
typedef struct {
	LEDCnf_t* Leds; 
	uint8_t Led_Total;
} LEDs_t;

void LED_Init(LEDs_t* Leds);
void LED_Ctrl(LEDCnf_t* Led);





#endif