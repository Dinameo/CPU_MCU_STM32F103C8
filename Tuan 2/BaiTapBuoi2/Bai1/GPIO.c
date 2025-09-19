#include "GPIO.h"

void GPIO_EnableClock(reg_ptr Px) {
	if(Px == GPIOA_BASE) {
		*(RCC_BASE + RCC_APB2ENR_OFFSET) |= (1U << 2);
	} else if(Px == GPIOB_BASE) {
		*(RCC_BASE + RCC_APB2ENR_OFFSET) |= (1U << 3);
	} else if(Px == GPIOC_BASE) {
		*(RCC_BASE + RCC_APB2ENR_OFFSET) |= (1U << 4);
	} else if(Px == GPIOD_BASE) {
		*(RCC_BASE + RCC_APB2ENR_OFFSET) |= (1U << 5);
	}
}

void pinConfig_DigitalOutput(reg_ptr Px, PinNum_t PinNum, uint32_t OutputMode) {
	GPIO_EnableClock(Px);
	if(PinNum < PIN_8) {
		*(Px + CRL_OFFSET) &= ~(0x0F << (PinNum*4));
		*(Px + CRL_OFFSET) |= (OutputMode << (PinNum*4));
	} else {
		*(Px + CRH_OFFSET) &= ~(0x0F << ((PinNum-8)*4));
		*(Px + CRH_OFFSET) |= (OutputMode << ((PinNum-8)*4));
	}
}
void pinWrite(reg_ptr Px, PinNum_t PinNum, PinState_t PinValue) {
	if(PinValue == PIN_SET) {
		*(Px+BSRR_OFFSET) = (1U << PinNum);
	} else {
		*(Px+BRR_OFFSET) = (1U << PinNum);
	}
}

PinState_t pinRead(reg_ptr Px, PinNum_t PinNum) {
	return (PinState_t) ((*(Px + IDR_OFFSET) >> PinNum)&0x01)?PIN_SET:PIN_RESET;
}
void pinConfig_DigitalInput(reg_ptr Px, PinNum_t PinNum, uint32_t InputMode, PullMode_t PullMode) {
	GPIO_EnableClock(Px);
	
	if(InputMode == INPUT_PULL_UP_DOWN) {
		if(PullMode == PULL_DOWN) {
			*(Px + ODR_OFFSET) &= ~(1U << PinNum);
		} else if(PullMode == PULL_UP) {
			*(Px + ODR_OFFSET) |= (1U << PinNum);
		} else {
			*(Px + ODR_OFFSET) &= ~(1U << PinNum);
		}
	} else {
		*(Px + ODR_OFFSET) &= ~(1U << PinNum);
	}
	
	if(PinNum < PIN_8) {
		*(Px + CRL_OFFSET) &= ~(0x0F << (PinNum*4));
		*(Px + CRL_OFFSET) |= (InputMode << (PinNum*4));
	} else {
		*(Px + CRH_OFFSET) &= ~(0x0F << ((PinNum-8)*4));
		*(Px + CRH_OFFSET) |= (InputMode << ((PinNum-8)*4));
	}
	
	
}