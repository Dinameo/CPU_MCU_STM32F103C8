// DRIVER FOR DECODER IC 74HC138

#include "main.h"
#include "IC74HC138.h"

void HC138_Select(Hardware74HC138_Cnf_t* Hardware_Cnf, Channel_t channel) {
	HAL_GPIO_WritePin(Hardware_Cnf->A_PORT, Hardware_Cnf->A_PIN, (GPIO_PinState) ((channel >> 0) & 0x1));
	HAL_GPIO_WritePin(Hardware_Cnf->B_PORT, Hardware_Cnf->B_PIN, (GPIO_PinState) ((channel >> 1) & 0x1));
	HAL_GPIO_WritePin(Hardware_Cnf->C_PORT, Hardware_Cnf->C_PIN, (GPIO_PinState) ((channel >> 2) & 0x1));
}