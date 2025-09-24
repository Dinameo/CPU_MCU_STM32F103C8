#include <stdint.h>


#define GPIO_

#define RCC_BASE					0x40021000
#define RCC_APB2ENR_BASE	RCC_BASE + 0x18

#define RCC 				(volatile uint32_t*) RCC_BASE
#define RCC_APB2ENR	(volatile uint32_t*) RCC_APB2ENR_BASE
	
