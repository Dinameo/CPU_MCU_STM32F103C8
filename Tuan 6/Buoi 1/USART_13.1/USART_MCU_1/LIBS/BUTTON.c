#include "main.h"
#include "BUTTON.h"
#include "TRANSMIT_UART.h"




uint8_t ButtonReadState(ButtonCnf_t* Button) {
	if(HAL_GPIO_ReadPin(Button->BT_Port, Button->BT_Pin) == GPIO_PIN_RESET)
		return 0;
	return 1;
}

void ButtonInit(ButtonGr_t* Buttons, UART_HandleTypeDef* huart) {
	for(uint8_t idx = 0; idx < Buttons->ButtonTotal; idx++) {
		Buttons->Buttons[idx].BT_Val = OFF;
		Buttons->Buttons[idx].BT_PreStat = BUTTON_RELEASED;
		UartTransmit_ButtonState(huart, idx, Buttons->Buttons[idx].BT_Val);
	}
}
void ButtonToggleValue(ButtonCnf_t* Button) {
	if(Button->BT_Val == ON) {
		Button->BT_Val = OFF;
	} else if(Button->BT_Val == OFF) {
		Button->BT_Val = ON;
	}
}
void ButtonSendState(ButtonGr_t* Buttons, UART_HandleTypeDef* huart) {
	for(uint8_t idx = 0; idx < Buttons->ButtonTotal; idx++) {
		if(ButtonReadState(&Buttons->Buttons[idx]) == BUTTON_PRESSED) {
			if(Buttons->Buttons[idx].BT_PreStat == BUTTON_RELEASED) {
				Buttons->Buttons[idx].BT_PreStat = BUTTON_PRESSED;
				ButtonToggleValue(&Buttons->Buttons[idx]);
				UartTransmit_ButtonState(huart, idx, Buttons->Buttons[idx].BT_Val);
			}
		} else {
			Buttons->Buttons[idx].BT_PreStat = BUTTON_RELEASED;
		}
	}
}
	