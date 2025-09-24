#ifndef __IC74HC165_H
#define __IC74HC165_H

#include "main.h"
#include "SEVSEG.h"


typedef struct {
	GPIO_TypeDef* SCK_PORT;
	GPIO_TypeDef* LD_PORT;
	GPIO_TypeDef* SO_PORT;
	
	uint16_t SCK_PIN;
	uint16_t LD_PIN;
	uint16_t SO_PIN;
} BUTTON_TypeDef;


uint8_t ReadButton(BUTTON_TypeDef* hButton);
void Pulse_Period(BUTTON_TypeDef* hButton);



/* Ver 1, chi khai bao 1 trong 2
void DisplayButtonNumber(BUTTON_TypeDef* hButton, SevSegCnf_t* Cnf);
*/
// Ver 2, chi khai bao 1 trong 2
uint8_t GetButtonIdx(BUTTON_TypeDef* hButton, SevSegCnf_t* Cnf);
#endif