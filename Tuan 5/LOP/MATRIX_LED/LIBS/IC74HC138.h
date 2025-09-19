// DRIVER FOR DECODER IC 74HC138

#ifndef __IC74HC138_H
#define __IC74HC138_H

#include "main.h"

typedef struct {
	GPIO_TypeDef* A_PORT;
	GPIO_TypeDef* B_PORT;
	GPIO_TypeDef* C_PORT;
	
	uint16_t A_PIN;
	uint16_t B_PIN;
	uint16_t C_PIN;
	
} Hardware74HC138_Cnf_t;

typedef enum {
	CHANNEL_0,
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5,
	CHANNEL_6,
	CHANNEL_7,
	CHANNEL_MAX
} Channel_t;

void HC138_Select(Hardware74HC138_Cnf_t* Hardware_Cnf, Channel_t channel);


#endif