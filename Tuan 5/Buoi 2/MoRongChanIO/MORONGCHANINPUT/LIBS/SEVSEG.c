#include "main.h"
#include "SEVSEG.h"

const uint8_t Digit_Arr[] = {
	0x40,
	0x79,
	0x24,
	0x30,
	0x19,
	0x12,
	0x02,
	0x78,
	0x00,
	0x10
};


void SevSeg_Display(SevSegCnf_t* Cnf, uint8_t SevSegCode) {
	for(uint8_t idx = SEG_A; idx < SEG_DP; idx++) {
		HAL_GPIO_WritePin(Cnf->SEG_PORT[idx], Cnf->SEG_PIN[idx], (GPIO_PinState) ((SevSegCode >> idx) & 0x1));
	}
} 

void SevSeg_DisplayDigit(SevSegCnf_t* Cnf, uint8_t Num) {
	SevSeg_Display(Cnf, Digit_Arr[Num]);
} 