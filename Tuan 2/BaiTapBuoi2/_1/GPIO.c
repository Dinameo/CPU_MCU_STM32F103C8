#include "stdint.h"

#define GPIOA_BASE	0x40010800
#define RCC_BASE		0x40021000
#define GPIOA_CRL				((volatile uint32_t*) (GPIOA_BASE + 0x00))
#define GPIOA_BSRR			((volatile uint32_t*) (GPIOA_BASE + 0x10))
#define RCC_APB2ENR			((volatile uint32_t*) (RCC_BASE+0x18))
typedef enum {
	Pin_0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7
} PinNum;
	
#define OUTPUT_PP_2MHZ	0x02

void Delay_ms(uint32_t ms) {
	while(ms) {
		for(uint8_t i = 0; i < 4; i++) {
			__asm("nop");
		}
		ms--;
	}
}


int main(void) {
	*RCC_APB2ENR |= (1U << 2);	// Enable GPIOA Clock
	for(uint8_t pin = Pin_0; pin <= Pin_7; pin++) {
		*GPIOA_CRL &= ~(0x0F << pin*4); // Clear CNF[1:0], MODE[1:0] PAx
		*GPIOA_CRL |= (OUTPUT_PP_2MHZ << pin*4); // PAx Output pushpull 2MHz
		*GPIOA_BSRR = (1U << (16+pin)); // RESET PAx
	}
	uint32_t led_state = 0x00; // PA1 ON, PA2 OFF, bit 0 - PA1, bit 1 - PA2
	while(1) {
		if(led_state == 0xFF) {
			*GPIOA_BSRR = (led_state << 16); 	// RESET ALL LED
			led_state = 0x00;
		} else {
			led_state = (led_state << 1) | 1; // Dich bit bien led_state và | LSB len 1, sang dan led (tu chan PA0 den chan PA7)
		}
		*GPIOA_BSRR = led_state;	// Set cac pin theo bien led_state
		Delay_ms(500);						// Delay 0.5s
		
	}
}