#include "GPIO.h"

void GPIO_ENR(GPIO_typedef* Px) {
	if(Px == GPIOA_BASE) { 
		*RCC_APB2ENR |= (1U << 2); 
	} else if(Px == GPIOB_BASE) {
		*RCC_APB2ENR |= (1U << 3);
	} else if(Px == GPIOC_BASE) {
		*RCC_APB2ENR |= (1U << 4);
	}
}

void  pinConfig_DigitalOutput(GPIO_typedef* Px, PinNum_t PinNum, uint32_t OutputMode) {
	GPIO_ENR(Px);
	if(PinNum < PIN_8) {
		Px->CRL &= ~(0x0F << (PinNum*4));	// Clear 4bit CNF, MODE 0b11110010, CNF, MODE 0x0010
		Px->CRL |= (OutputMode << (PinNum*4));
	} else {
		Px->CRH &= ~(0x0F << ((PinNum-8)*4));
		Px->CRH |= (OutputMode << ((PinNum-8)*4));
	}
}
void pinConfig_DigitalInput(GPIO_typedef* Px, PinNum_t PinNum, uint32_t InputMode, PullMode_t PullMode) {
	GPIO_ENR(Px);
	if(InputMode == INPUT_PU_PD) {
		if(PullMode == PULL_DOWN) {
			Px->ODR &= ~(1U << PinNum); 
		} else if(PullMode == PULL_UP) {
			Px->ODR |= (1U << PinNum);
		}
	}
	
	if(PinNum < PIN_8) {
		Px->CRL &= ~(0x0F << (PinNum*4));
		Px->CRL |= (InputMode << (PinNum*4));
	} else {
		Px->CRH &= ~(0x0F << ((PinNum-8)*4));
		Px->CRH |= (InputMode << ((PinNum-8)*4));
	}
}
void pinWrite(GPIO_typedef* Px, PinNum_t PinNum, PinState_t PinValue) {
	if(PinValue == PIN_RESET) {
		Px->BRR = (1U << PinNum);
	} else {
		Px->BSRR = (1U << PinNum);
	}
}

PinState_t pinRead(GPIO_typedef* Px, PinNum_t PinNum) {
	return (((Px->IDR >> PinNum)&0x01) == 0)?PIN_RESET:PIN_SET;
}
void portWrite(GPIO_typedef* Px, uint32_t PortValue) {
	PortValue &= (0x0000FFFF);
	for(uint8_t i = 0; i < 16; i++) {
		if(((PortValue >> i) & 0x01) == 0) {
			pinWrite(Px, i, PIN_RESET);
		} else {
			pinWrite(Px, i, PIN_SET);
		}
	}
}
uint32_t portRead(GPIO_typedef* Px) {
	return (Px->IDR & 0x0000FFFF);
}