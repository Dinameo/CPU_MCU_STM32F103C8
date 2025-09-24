#ifndef __SEVSEG_H
#define __SEVSEG_H

#include "main.h"


typedef struct {
	GPIO_TypeDef* SEG_PORT[7];
	uint16_t SEG_PIN[7];
} SevSegCnf_t;
typedef enum {
	SEG_A,
	SEG_B,
	SEG_C,
	SEG_D,
	SEG_E,
	SEG_F,
	SEG_G,
	SEG_DP
} SegIndex_t;
void SevSeg_DisplayDigit(SevSegCnf_t* Cnf, uint8_t Num);
void SevSeg_Display(SevSegCnf_t* Cnf, uint8_t SevSegCode);
#endif