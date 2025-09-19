#ifndef __GPIO_H
#define __GPIO_H

#include "stdint.h"


/*
Reset and clock control RCC
RCC_APB2ENR: APB2 peripheral clock enable register
Offset: 0x18
RCC_BASE Address: 0x40021000

General-purpose I/Os GPIO
GPIOA_BASE Address: 0x40010800
GPIOB_BASE Address: 0x40010C00
GPIOC_BASE Address: 0x40011000
GPIOD_BASE Address: 0x40011400

	CRL: Port configuration register low
	Address Offset: 0x00

	CRH: Port configuration register high 
	Address Offset: 0x04

	IDR: Port input data register 
	Address offset: 0x08
	
	ODR: Port output data register 
	Address Offset: 0x0C
	
	BSRR: Port bit set/reset register (x=A..G)
	Address Offset: 0x10

	BRR: Port bit reset register 
	Address Offset: 0x14
	
	LCKR: Port configuration lock register 
	Address Offset: 0x18
	
Output Mode

*/


typedef volatile uint32_t*	reg_ptr;

#define RCC_BASE					((reg_ptr) 0x40021000)
	
#define RCC_APB2ENR_OFFSET			0x18/4

#define GPIOA_BASE					((reg_ptr) 0x40010800)
#define GPIOB_BASE					((reg_ptr) 0x40010C00)
#define GPIOC_BASE					((reg_ptr) 0x40011000)
#define GPIOD_BASE					((reg_ptr) 0x40011400)

*(GPIOA_BASE + 0x04) = 0x40010810

#define CRL_OFFSET					0x00/4

#define CRH_OFFSET					0x04/4
#define IDR_OFFSET					0x08/4
#define ODR_OFFSET					0x0C/4
#define BSRR_OFFSET					0x10/4
#define BRR_OFFSET					0x14/4
#define LCKR_OFFSET					0x18/4

#define INPUT_ANALOG				0x00
#define INPUT_FLOATING			    0x04
#define INPUT_PULL_UP_DOWN			0x08

#define OUTPUT_PP_2MHZ				0x02
#define OUTPUT_PP_10MHZ				0x01
#define OUTPUT_PP_50MHz				0x03

#define OUTPUT_OP_2MHZ				0x06
#define OUTPUT_OP_10MHZ				0x05
#define OUTPUT_OP_50MHZ				0x07



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
	PIN_15
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
void GPIO_EnableClock(reg_ptr Px);
void pinConfig_DigitalOutput(reg_ptr Px, PinNum_t PinNum, uint32_t OutputMode);
void pinConfig_DigitalInput(reg_ptr Px, PinNum_t PinNum, uint32_t InputMode, PullMode_t PullMode);
void pinWrite(reg_ptr Px, PinNum_t PinNum, PinState_t PinValue);
PinState_t pinRead(reg_ptr Px, PinNum_t PinNum);

#endif