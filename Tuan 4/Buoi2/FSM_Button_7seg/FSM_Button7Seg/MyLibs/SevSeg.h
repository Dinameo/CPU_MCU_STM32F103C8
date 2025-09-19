#ifndef SEVSEG_H
#define SEVSEG_H

#include "main.h"

typedef struct {
	GPIO_TypeDef* SEG_A_PORT;
	GPIO_TypeDef* SEG_B_PORT;
	GPIO_TypeDef* SEG_C_PORT;
	GPIO_TypeDef* SEG_D_PORT;
	GPIO_TypeDef* SEG_E_PORT;
	GPIO_TypeDef* SEG_F_PORT;
	GPIO_TypeDef* SEG_G_PORT;
	GPIO_TypeDef* SEG_DP_PORT;
	
	uint16_t SEG_A_PIN;
	uint16_t SEG_B_PIN;
	uint16_t SEG_C_PIN;
	uint16_t SEG_D_PIN;
	uint16_t SEG_E_PIN;
	uint16_t SEG_F_PIN;
	uint16_t SEG_G_PIN;
	uint16_t SEG_DP_PIN;
} SevSeg_Conf;

typedef union {
	struct {
		uint8_t SEG_A	:	1; // LSB 0
		uint8_t SEG_B	:	1;
		uint8_t SEG_C	:	1;
		uint8_t SEG_D	:	1;
		uint8_t SEG_E	:	1;
		uint8_t SEG_F	:	1;
		uint8_t SEG_G	:	1;
		uint8_t SEG_DP:	1; // MSB 7
	} Bits;
	
	uint8_t Value;
} SevSeg_t;




typedef enum {
	DIGIT_0, // 0
	DIGIT_1, // 1
	DIGIT_2, // 2
	DIGIT_3, // 3
	DIGIT_4,
	DIGIT_5,
	DIGIT_6,
	DIGIT_7,
	DIGIT_8,
	DIGIT_9,
	SEVSEG_OFF,
	SEVSEG_ON, // 11
	SEVSEG_MAX // 12
} SevSegDigit_t;
 


void SevSeg_Display(SevSeg_Conf* SevSegInf, SevSeg_t* SevSeg);
void SevSeg_DisplayDigit(SevSeg_Conf* SevSegInf, SevSegDigit_t Digit);
void SevSeg_Init(SevSeg_Conf* SevSegInf);

#endif