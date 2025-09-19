#include "GPIO.h"

int main(void) {
	
	pinConfig_DigitalOutput(GPIOA_BASE, PIN_1, OUTPUT_PP_2MHZ);
	pinWrite(GPIOA_BASE, PIN_1, PIN_RESET);
	pinConfig_DigitalInput(GPIOA_BASE, PIN_0, INPUT_FLOATING, NO_PULL);
	while(1) {
		if(pinRead(GPIOA_BASE, PIN_0) == PIN_SET) {
			pinWrite(GPIOA_BASE, PIN_1, PIN_SET);
		} else if(pinRead(GPIOA_BASE, PIN_0) == PIN_RESET) {
			pinWrite(GPIOA_BASE, PIN_1, PIN_RESET);
		}
	}
	
	return 0;
}