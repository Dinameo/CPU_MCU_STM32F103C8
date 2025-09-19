#include "main.h"
#include "LED7SEG_HC595.h"


const uint8_t Num_Arr[] = {
	0x18,//0
	0x3F,//1
	0x94,//2
	0x16,
	0x33,
	0x52,
	0x50,
	0x1F,
	0x10,
	0x12//9
};

void SendBit(HardwareCnf_t* Cnf, uint8_t Bit) {
	HAL_GPIO_WritePin(Cnf->DAT_PORT, Cnf->DAT_PIN, Bit & 0x1);
	HAL_GPIO_WritePin(Cnf->SCK_PORT, Cnf->SCK_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Cnf->SCK_PORT, Cnf->SCK_PIN, GPIO_PIN_SET);
}
void SendByte(HardwareCnf_t* Cnf, uint8_t Byte) {
	for(uint8_t i = 0; i < 8; i++) {
		SendBit(Cnf, (Byte >> i)&0x1);  // Send Low bit to high bit
	}
}
void Latch(HardwareCnf_t* Cnf) {
	HAL_GPIO_WritePin(Cnf->LAT_PORT, Cnf->LAT_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Cnf->LAT_PORT, Cnf->LAT_PIN, GPIO_PIN_SET);
}

void LED_Display_Digit(HardwareCnf_t* Cnf, uint8_t Num) {
	SendByte(Cnf, Num_Arr[Num%10]);
	Latch(Cnf);
}