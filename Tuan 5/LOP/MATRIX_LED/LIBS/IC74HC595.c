// DRIVER FOR IC LATCH 8BIT 74HC595

#include "main.h"
#include "IC74HC595.h"

void HC595_SendBit(Hardware74HC595_Cnf_t *Config, uint8_t bitVal)
{
	HAL_GPIO_WritePin(Config->DAT_PORT, Config->DAT_PIN, (GPIO_PinState) (bitVal & 0x1));
	HAL_GPIO_WritePin(Config->CLK_PORT, Config->CLK_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Config->CLK_PORT, Config->CLK_PIN, GPIO_PIN_SET);
}
void HC595_SendByte(Hardware74HC595_Cnf_t *Config, uint8_t byteVal) {
	for(uint8_t idx = 0; idx < 8; idx++) {
		HC595_SendBit(Config, ((byteVal >> (7-idx)) & 0x1));
	}
}

void HC595_Latch(Hardware74HC595_Cnf_t *Config) {
	HAL_GPIO_WritePin(Config->LATCH_PORT, Config->LATCH_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Config->LATCH_PORT, Config->LATCH_PIN, GPIO_PIN_SET);
}