#include "main.h"
#include "LED14SEG.h"

const uint16_t Num_Arr[] = {
	~0x0C3F,
	~0x0406,
	~0x00DB,
	~0x008F,
	~0x00E6,
	~0X00ED,
	~0x00FD,
	~0X0007,
	~0X00FF,
	~0X00EF
};
const uint16_t Char_Arr[] = {
	~0X00F7,// A
	~0X128F,// B...
	~0X0039,
	~0X120F,
	~0X0079,
	~0X0071,
	~0X00BD,
	~0X00F6,
	~0X1209,
	~0X001E,
	~0X2470,
	~0X0038,
	~0X0536,
	~0X2136,
	~0X003F,
	~0X00F3,
	~0X203F,
	~0X20F3,
	~0X018D,
	~0X1201,
	~0X003E,
	~0X0C30,
	~0X2836,
	~0X2D00,
	~0X1500,
	~0X0C09//Z

};

void SendBit(HardwareCnf_t* Cnf, uint8_t BitDat) {
	HAL_GPIO_WritePin(Cnf->DAT_PORT, Cnf->DAT_PIN, (GPIO_PinState) (BitDat & 0x1));
	HAL_GPIO_WritePin(Cnf->SCK_PORT, Cnf->SCK_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Cnf->SCK_PORT, Cnf->SCK_PIN, GPIO_PIN_SET);
} 

void SendByte(HardwareCnf_t* Cnf, uint8_t ByteDat) {
	for(uint8_t i = 0; i < 8; i++) {
		SendBit(Cnf, (ByteDat >> (7-i)));
	}
}
void Send2Byte(HardwareCnf_t* Cnf, uint16_t TwoByteDat) {
	SendByte(Cnf, ((TwoByteDat >> 8) & 0xFF));
	SendByte(Cnf, (TwoByteDat & 0xFF));
} 

void Latch(HardwareCnf_t* Cnf) {
	HAL_GPIO_WritePin(Cnf->LAT_PORT, Cnf->LAT_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Cnf->LAT_PORT, Cnf->LAT_PIN, GPIO_PIN_SET);
}
void LED_DisplayNum(HardwareCnf_t* Cnf, uint8_t Num) {
	Send2Byte(Cnf, Num_Arr[Num]);
	Latch(Cnf);
}
void LED_DisplayChar(HardwareCnf_t* Cnf, uint8_t Ch) {
	if(Ch >= 'A' && Ch <= 'Z') {
		Send2Byte(Cnf, Char_Arr[Ch - 'A']);
	}
	else if(Ch >= '0' &&  Ch <= '9') {
		Send2Byte(Cnf, Num_Arr[Ch - '0']);
	}
	Latch(Cnf);
}
void LED_DisplayString(HardwareCnf_t* Cnf, uint8_t* str) {
	while(*str) {
		LED_DisplayChar(Cnf, *str);
		str++;
		HAL_Delay(200);
	}
}