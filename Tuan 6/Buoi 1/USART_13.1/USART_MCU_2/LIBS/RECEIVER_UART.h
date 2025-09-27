#ifndef __RECEIVER_UART_H
#define __RECEIVER_UART_H

#include "main.h"
#include "LED.h"

#define ON 	0xF
#define OFF	0x0

void UartReceiver(UART_HandleTypeDef* huart, LEDs_t* Leds);


#endif