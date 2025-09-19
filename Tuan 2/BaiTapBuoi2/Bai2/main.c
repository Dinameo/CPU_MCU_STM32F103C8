#include "GPIO.h"

void Delay_ms(uint32_t ms) {
	while(ms) {
		for(int i = 0; i < 8000; i++) {
			__asm__("nop");
		}
		ms--;
	}
}

int main(void) {
	// Test
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_0, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_1, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_2, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_3, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_4, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_5, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_6, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_7, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_8, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_9, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_10, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_11, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_12, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_13, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_14, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_15, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_0, PIN_RESET);
	
	uint32_t led = 0x0000; 
	uint8_t flag = 0;
	while(1) {
		portWrite(GPIOA_BASE, led);
		if(flag == 1) {
			led >>= 1; 
		} else {
			led = (led << 1) | 1; 
		}
		
		if(led == 0xFFFF) { 
			flag = 1;		
		} else if(led == 0x0000) {
			flag = 0;
		}
		Delay_ms(10);
	}
}