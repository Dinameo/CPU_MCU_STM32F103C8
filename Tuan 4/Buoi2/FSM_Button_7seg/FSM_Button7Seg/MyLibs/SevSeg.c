#include "SevSeg.h"


const uint8_t SevSegCode[] = {
	0x3F,	// Num 0
	0x06,	// Num 1
	0x5B,	// Num 2
	0x4F,	// Num 3
	0x66,	// Num 4
	0x6D,	// Num 5
	0x7D,	// Num 6
	0x07,	// Num 7
	0x7F,	// Num 8
	0x6F,	// Num 9
	0x00,	// 7Seg OFF
	0x7F	// 7Seg ON
};



void SevSeg_Display(SevSeg_Conf* SevSegInf, SevSeg_t* SevSeg) {
	HAL_GPIO_WritePin(SevSegInf->SEG_A_PORT, SevSegInf->SEG_A_PIN, (GPIO_PinState) SevSeg->Bits.SEG_A);
	HAL_GPIO_WritePin(SevSegInf->SEG_B_PORT, SevSegInf->SEG_B_PIN, (GPIO_PinState) SevSeg->Bits.SEG_B);
	HAL_GPIO_WritePin(SevSegInf->SEG_C_PORT, SevSegInf->SEG_C_PIN, (GPIO_PinState) SevSeg->Bits.SEG_C);
	HAL_GPIO_WritePin(SevSegInf->SEG_D_PORT, SevSegInf->SEG_D_PIN, (GPIO_PinState) SevSeg->Bits.SEG_D);
	HAL_GPIO_WritePin(SevSegInf->SEG_E_PORT, SevSegInf->SEG_E_PIN, (GPIO_PinState) SevSeg->Bits.SEG_E);
	HAL_GPIO_WritePin(SevSegInf->SEG_F_PORT, SevSegInf->SEG_F_PIN, (GPIO_PinState) SevSeg->Bits.SEG_F);
	HAL_GPIO_WritePin(SevSegInf->SEG_G_PORT, SevSegInf->SEG_G_PIN, (GPIO_PinState) SevSeg->Bits.SEG_G);
	//HAL_GPIO_WritePin(SevSegInf->SEG_DP_PORT, SevSegInf->SEG_DP_PIN, (GPIO_PinState) SevSeg->Bits.SEG_DP);
}
void SevSeg_DisplayDigit(SevSeg_Conf* SevSegInf, SevSegDigit_t Digit) {
	SevSeg_t temp;
	temp.Value = SevSegCode[Digit%SEVSEG_MAX];
	SevSeg_Display(SevSegInf, &temp);
}
void SevSeg_Init(SevSeg_Conf* SevSegInf) {
	SevSeg_DisplayDigit(SevSegInf, DIGIT_0);
}



