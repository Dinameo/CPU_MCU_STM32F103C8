#ifndef __GPIO_H
#define __GPIO_H


#include "stdint.h"



typedef struct {
	volatile uint32_t CRL;		// offset 0, 		0x40010800
	volatile uint32_t CRH;		// offset 4, 		0x40010804
	volatile uint32_t IDR;		// offset 8, 		0x40010808
	volatile uint32_t ODR;		// offset 12,		0x4001080C
	volatile uint32_t BSRR;		// offset 16,		0x40010810
	volatile uint32_t BRR;		// offset 20,		0x40010814
	volatile uint32_t LCK;		// offset 24,		0x40010818
} GPIO_typedef;



#define GPIOA_BASE		((GPIO_typedef*) 0x40010800)
#define GPIOB_BASE		((GPIO_typedef*) 0x40010C00)
#define GPIOC_BASE		((GPIO_typedef*) 0x40011000)




#define RCC_BASE			((volatile uint32_t*) 0x40021000)

#define RCC_APB2ENR		((volatile uint32_t*) (0x40021000 + 0x18))
	
typedef enum {
	PIN_0, 
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4, 
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15,
} PinNum_t;

typedef enum {
	PIN_RESET,
	PIN_SET
} PinState_t;

typedef enum {
	PULL_DOWN,
	PULL_UP,
	NO_PULL
} PullMode_t;

#define OUTPUT_PP_2MHZ		0x02 // 0b0010 // 4bit, CNF[1:0] - Che do, MODE[1:0] - Speed
#define OUTPUT_PP_50MHZ		0x03 // 0b0011 /
#define OUTPUT_PP_10MHZ		0x01 // 0b0001 

#define OUTPUT_OD_2MHZ		0x06
#define OUTPUT_OD_50MHZ		0x07
#define OUTPUT_OD_10MHZ		0x05

#define INPUT_AG					0x00
#define INPUT_FLOATING		0x04
#define INPUT_PU_PD				0x08  // ODR == 1 Pull up, ODR ==0 pull down





void GPIO_ENR(GPIO_typedef* Px);
void pinConfig_DigitalOutput(GPIO_typedef* Px, PinNum_t PinNum, uint32_t OutputMode);

void pinConfig_DigitalInput(GPIO_typedef* Px, PinNum_t PinNum, uint32_t InputMode, PullMode_t PullMode);

void pinWrite(GPIO_typedef* Px, PinNum_t PinNum, PinState_t PinValue);
PinState_t pinRead(GPIO_typedef* Px, PinNum_t PinNum);

void portWrite(GPIO_typedef* Px, uint32_t PortValue);
uint32_t portRead(GPIO_typedef* Px);
#endif