#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"


#define BUTTON_PRESSED	GPIO_PIN_RESET
#define BUTTON_RELEASED	GPIO_PIN_SET

#define ON	0xF
#define OFF	0x0

typedef struct {
	GPIO_TypeDef* BT_Port;
	uint16_t			BT_Pin;
	uint8_t 			BT_Val;
	uint8_t				BT_PreStat;
} ButtonCnf_t;

typedef struct {
	ButtonCnf_t* Buttons;
	uint8_t ButtonTotal;
} ButtonGr_t;

void ButtonInit(ButtonGr_t* Buttons, UART_HandleTypeDef* huart);

uint8_t ButtonReadState(ButtonCnf_t* Button);
void ButtonSendState(ButtonGr_t* Buttons, UART_HandleTypeDef* huart);
void ButtonToggleValue(ButtonCnf_t* Button);
#endif