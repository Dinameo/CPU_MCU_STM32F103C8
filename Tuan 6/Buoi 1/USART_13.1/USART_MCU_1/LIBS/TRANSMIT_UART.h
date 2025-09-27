#ifndef __TRANSMIT_UART_H
#define __TRANSMIT_UART_H

#include "main.h"
#include "BUTTON.h"



void UartTransmit_ButtonState(UART_HandleTypeDef* huart, uint8_t ButtonPos, uint8_t Dat);

#endif