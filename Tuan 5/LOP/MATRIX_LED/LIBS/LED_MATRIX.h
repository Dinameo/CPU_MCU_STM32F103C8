#ifndef __LED_MATRIX_H
#define __LED_MATRIX_H
#include "main.h"
#include "IC74HC138.h"
#include "IC74HC595.h"


typedef struct {
	uint8_t* CharDispNow;
	uint8_t IsIdle;
	uint32_t TimeDisplay;
	Hardware74HC138_Cnf_t* Decoder;
	Hardware74HC595_Cnf_t* ICLatch;
} LedMatrixCnf_t;

void LED_MATRIX_Display(LedMatrixCnf_t* LedMatrix_Cnf, uint8_t* ch, uint8_t  TimeDisplay);





#endif