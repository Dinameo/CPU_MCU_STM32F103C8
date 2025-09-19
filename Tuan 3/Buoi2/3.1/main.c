#include "stdint.h"

#define GPIOA_BASE	0x40010800
#define RCC_BASE		0x40021000
#define GPIOA_CRL				((volatile uint32_t*) (GPIOA_BASE + 0x00))
#define GPIOA_BSRR			((volatile uint32_t*) (GPIOA_BASE + 0x10))
#define RCC_APB2ENR			((volatile uint32_t*) (RCC_BASE+0x18))
typedef enum {
	Pin_1 = 1,
	Pin_2 = 2
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
	*GPIOA_CRL &= ~(0x0F << 1*4); // Clear CNF[1:0], MODE[1:0] PA1
	*GPIOA_CRL &= ~(0x0F << 2*4); // Clear CNF[1:0], MODE[1:0] PA2
	*GPIOA_CRL |= (OUTPUT_PP_2MHZ << 1*4); // PA1 Output pushpull 2MHz
	*GPIOA_CRL |= (OUTPUT_PP_2MHZ << 2*4); // PA2 Output pushpull 2MHz
	
	
	uint32_t led_state = 0x01; // PA1 ON, PA2 OFF, bit 0 - PA1, bit 1 - PA2
	while(1) {
		*GPIOA_BSRR = (1U << (16+Pin_1)); // RESET PA1
		*GPIOA_BSRR = (1U << (16+Pin_2)); // RESET PA2
		
		
		*GPIOA_BSRR = (led_state &0x01)?(1U << Pin_1):(1U << (16+Pin_1)); 				// Output state to PA1
		*GPIOA_BSRR = ((led_state >> 1) &0x01)?(1U << Pin_2):(1U << (16+Pin_2));	// Output state to PA2
		
		Delay_ms(600);
		
		// Toggle led_state between 01 and 10 (binary)
		led_state = (~led_state) & 0x03;
	}
}