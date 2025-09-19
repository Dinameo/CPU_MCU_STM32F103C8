#ifndef __LED14SEG_H
#define __LED14SEG_H


#include "main.h"

typedef struct {
	GPIO_TypeDef* SCK_PORT;
	GPIO_TypeDef* DAT_PORT;
	GPIO_TypeDef* LAT_PORT;
	
	uint16_t SCK_PIN;
	uint16_t DAT_PIN;
	uint16_t LAT_PIN;
	
} HardwareCnf_t;


void SendBit(HardwareCnf_t* Cnf, uint8_t BitDat);
void SendByte(HardwareCnf_t* Cnf, uint8_t ByteDat);
void Send2Byte(HardwareCnf_t* Cnf, uint16_t TwoByteDat);
void LED_DisplayNum(HardwareCnf_t* Cnf, uint8_t Num);
void LED_DisplayChar(HardwareCnf_t* Cnf, uint8_t Ch);
void LED_DisplayString(HardwareCnf_t* Cnf, uint8_t* str);
void Latch(HardwareCnf_t* Cnf);

#endif