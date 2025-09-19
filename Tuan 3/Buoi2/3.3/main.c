#include "stdint.h"

#define GPIOA_BASE	0x40010800
#define GPIOB_BASE 	0x40010C00
#define RCC_BASE    0x40021000


#define RCC_APB2ENR ((volatile uint32_t*) (RCC_BASE+0x18))

#define GPIOA_CRL		((volatile uint32_t*) (GPIOA_BASE+0x00))
#define GPIOB_CRL		((volatile uint32_t*) (GPIOB_BASE+0x00))
	
#define GPIOA_IDR		((volatile uint32_t*) (GPIOA_BASE+0x08))
#define GPIOB_IDR		((volatile uint32_t*) (GPIOB_BASE+0x08))
#define GPIOB_BSRR	((volatile uint32_t*)	(GPIOB_BASE+0x10))
#define GPIOA_ODR		((volatile uint32_t*)	(GPIOA_BASE+0x0C))
	
#define OUTPUT_PP_2MHZ  0x02		// CNF 00, MODE 10
#define INPUT_PD_PU			0x08		// CNF 10, MODE 00
	
void Delay_ms(uint32_t ms) {
    while(ms) {
        for(uint8_t i = 0; i < 4; i++) {
            __asm("nop");
        }
        ms--;
    }
}


int main(void) {
	
	*RCC_APB2ENR |= (3U << 2);	//	Enable GPIOA, GPIOB Clock
	
	
	*GPIOB_CRL &= ~0x0F;						// Reset CNF,MODE Pin0 GPIOB
	*GPIOB_CRL |= OUTPUT_PP_2MHZ;		// Output pp 2MHZ
	*GPIOA_CRL &= ~0x0F;						// Reset CNF,MODE Pin0 GPIOA
	*GPIOA_CRL |= INPUT_PD_PU;			// INPUT Pull Down, Pull Up
	*GPIOA_ODR &= ~1U;							// Input Pull Down
	
	*GPIOB_BSRR = 1U << 16;								// Output state LOW on PB0						
	
	while(1) {
		if((*GPIOA_IDR & 0x01)) {	
			Delay_ms(5);
			if((*GPIOA_IDR & 0x01)) {
				*GPIOB_BSRR = (*GPIOB_IDR & 0x01)?(1U << 16):(1U);		// Toggle LED
				while((*GPIOA_IDR & 0x01));
			}
		}	// Debouncing
		
	}
}