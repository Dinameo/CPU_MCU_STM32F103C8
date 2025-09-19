// DRIVER FOR IC LATCH 8BIT 74HC595

#ifndef __IC74HC595_H
#define __IC74HC595_H

#include "main.h"

typedef struct {
	GPIO_TypeDef* CLK_PORT;
	GPIO_TypeDef* DAT_PORT;
	GPIO_TypeDef* LATCH_PORT;
	
	uint16_t CLK_PIN;
	uint16_t DAT_PIN;
	uint16_t LATCH_PIN;
	
} Hardware74HC595_Cnf_t;

void HC595_SendBit(Hardware74HC595_Cnf_t *Config, uint8_t bitVal);
void HC595_SendByte(Hardware74HC595_Cnf_t *Config, uint8_t byteVal);
void HC595_Latch(Hardware74HC595_Cnf_t *Config);


#endif