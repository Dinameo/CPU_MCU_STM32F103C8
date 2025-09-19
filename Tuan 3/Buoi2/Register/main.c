#include "stdint.h"

#define RCC_BASE           0x40021000
#define GPIOA_BASE         0x40010800
#define GPIO_OUTPUT_2MHZ   0x02  // 0b10
#define GPIO_INPUT         0x08  // 0b0000

#define RCC_APB2ENR        ((volatile uint32_t *)(RCC_BASE+0x18))
#define GPIOA_CRL          ((volatile uint32_t *)(GPIOA_BASE+0x00))
#define GPIOA_ODR          ((volatile uint32_t *)(GPIOA_BASE+0x0C))
#define GPIOA_IDR          ((volatile uint32_t *)(GPIOA_BASE+0x08))

int main() {
    *RCC_APB2ENR |= (1<<2);          // Enable GPIOA clock
    *GPIOA_CRL   = GPIO_OUTPUT_2MHZ<<(1*4);  // PA1 output
    *GPIOA_CRL  &= ~(0x0F<<(2*4));   // Clear CF1:CF0:MODE1:MODE0
    *GPIOA_CRL  |= GPIO_INPUT<<(2*4);      // PA2 input
    *GPIOA_ODR  |= 1<<2;             // PA2 PULL-UP

    while(1) {
        if (*GPIOA_IDR & (1<<2)) {
            *GPIOA_ODR |= 1<<1;
        } else {
            *GPIOA_ODR &= ~(1<<1);
        }
    }
}