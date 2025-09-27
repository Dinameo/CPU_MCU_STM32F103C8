#include "main.h"
#include "TRANSMIT_UART.h"

/* Data duoc gui di bao gom 8 bit 
	+ 4 bit cao: la vi tri cua button (0->BT1, 1->BT2, 2->BT3, 3->BT4)
	+ 4 bit thap: trang thai cho LED (0x0 OFF, 0xF ON)
*/


void UartTransmit_ButtonState(UART_HandleTypeDef* huart, uint8_t ButtonPos, uint8_t Dat) {
	uint8_t Byte = ((ButtonPos  & 0xF) << 4) | (Dat & 0xF);
	HAL_UART_Transmit(huart, &Byte, 1, HAL_MAX_DELAY);
}
