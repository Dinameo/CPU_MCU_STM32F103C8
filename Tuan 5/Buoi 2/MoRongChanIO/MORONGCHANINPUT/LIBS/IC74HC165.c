#include "main.h"
#include "IC74HC165.h"
#include "SEVSEG.h"
void Pulse_Period(BUTTON_TypeDef* hButton) {
	HAL_GPIO_WritePin(hButton->SCK_PORT, hButton->SCK_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(hButton->SCK_PORT, hButton->SCK_PIN, GPIO_PIN_SET);
}
uint8_t ReadButton(BUTTON_TypeDef* hButton) {
	HAL_GPIO_WritePin(hButton->LD_PORT, hButton->LD_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(hButton->LD_PORT, hButton->LD_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(hButton->LD_PORT, hButton->LD_PIN, GPIO_PIN_SET);
	uint8_t input_byte = 0x00;
	for(uint8_t i = 0; i < 8; i++) {
		
		uint8_t bit_dat = HAL_GPIO_ReadPin(hButton->SO_PORT, hButton->SO_PIN);
		input_byte |= (bit_dat << (7-i));
		Pulse_Period(hButton);
	}
	return input_byte;
}
/* Version 1 Dùng bien static
void DisplayButtonNumber(BUTTON_TypeDef* hButton, SevSegCnf_t* Cnf) {
	static uint8_t DisplayNumNow = 0;
	uint8_t input_byte = ReadButton(hButton);
	uint8_t num = 1;
	while((input_byte & 0x1) != 0) {
		input_byte >>= 1;
		num++;
		if(num == 9) {
			return;
		}
	}
	DisplayNumNow = num;
	SevSeg_DisplayDigit(Cnf, DisplayNumNow);
} */
// Version 2 Dùng Finite State Machine
uint8_t GetButtonIdx(BUTTON_TypeDef* hButton, SevSegCnf_t* Cnf) {
	uint8_t input_byte = ReadButton(hButton);
	uint8_t num = 1;
	while((input_byte & 0x1) != 0) {
		input_byte >>= 1;
		num++;
		if(num == 9) {
			return 0;
		}
	}
	return num;
}
