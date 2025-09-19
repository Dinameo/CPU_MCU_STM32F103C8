#ifndef __LED7SEG_HC595
#define __LED7SEG_HC595

#include "main.h"

typedef struct {
	GPIO_TypeDef* SCK_PORT;
	GPIO_TypeDef* LAT_PORT;
	GPIO_TypeDef* DAT_PORT;
	
	uint16_t SCK_PIN;
	uint16_t LAT_PIN;
	uint16_t DAT_PIN;
} HardwareCnf_t;


void SendBit(HardwareCnf_t* Cnf, uint8_t Bit);
void SendByte(HardwareCnf_t* Cnf, uint8_t Byte);
void Latch(HardwareCnf_t* Cnf);
void LED_Display_Digit(HardwareCnf_t* Cnf, uint8_t Num);

#endif