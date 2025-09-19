#include "stdint.h"

#define GPIOA_BASE	0x40010800
#define GPIOB_BASE 	0x40010C00


#define RCC_BASE		0x40021000
#define GPIOA_CRL				((volatile uint32_t*) (GPIOA_BASE + 0x00))
#define GPIOA_ODR			  ((volatile uint32_t*) (GPIOA_BASE + 0x0C))
#define RCC_APB2ENR			((volatile uint32_t*) (RCC_BASE+0x18))

#define GPIOB_CRL		((volatile uint32_t*) (GPIOB_BASE+0x00))
#define GPIOB_IDR		((volatile uint32_t*) (GPIOB_BASE+0x08))
#define GPIOB_ODR		((volatile uint32_t*)	(GPIOB_BASE+0x0C))


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
	
typedef enum {
	BTN_OFF,
	BTN_ON
} ButtonState_t;
#define OUTPUT_PP_2MHZ	0x02
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
	ButtonState_t ButtonState = BTN_OFF;
	*RCC_APB2ENR |= (3U << 2);	// Enable GPIOA, GPIOB Clock
	for(uint8_t pin = Pin_0; pin <= Pin_7; pin++) {
		*GPIOA_CRL &= ~(0x0F << pin*4); // Clear CNF[1:0], MODE[1:0] PAx
		*GPIOA_CRL |= (OUTPUT_PP_2MHZ << pin*4); // PAx Output pushpull 2MHz
	}
	uint32_t led_state = 0x00; // LedState - OFF ALL LED
	*GPIOA_ODR &= (~0xFF);		// OFF ALL LED
	
	
	*GPIOB_CRL &= ~0x0F;						// Clr CNF, MODE
	*GPIOB_CRL |= INPUT_PD_PU;			// INPUT Pull Down, Pull Up
	*GPIOB_ODR &= ~1U;							// Input Pull Down
	
	
	
	
	while(1) {
		if((*GPIOB_IDR & 0x01)) {	
			Delay_ms(5);
			if((*GPIOB_IDR & 0x01)) {	
				ButtonState ^= BTN_ON;	// Toggle led state
				while((*GPIOB_IDR & 0x01));
			}
		}	// Debouncing
		
		
		
		if(ButtonState == BTN_ON) { 
			if(led_state == 0xFF) {
				*GPIOA_ODR &= (~0xFF); 	// OFF ALL LED
				led_state = 0x00;
			} else {
				led_state = (led_state << 1) | 1; // Dich bit bien led_state và | LSB len 1, sang dan led (tu chan PA0 den chan PA7)
				*GPIOA_ODR = led_state;	// Set cac pin theo bien led_state
			}
			Delay_ms(500);						// Delay 0.5s
			
		} else {
			led_state = 0xFF;
			*GPIOA_ODR &= (~0xFF);	// OFF ALL LED
			led_state = 0x00;
			
		}
		
	}
}