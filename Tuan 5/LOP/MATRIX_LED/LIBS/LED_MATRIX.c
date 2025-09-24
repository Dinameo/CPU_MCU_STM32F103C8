#include "LED_MATRIX.h"

void LED_MATRIX_Display(LedMatrixCnf_t* LedMatrix_Cnf, uint8_t* ch, uint8_t  TimeDisplay) {
	if(LedMatrix_Cnf->IsIdle == 1) {
		LedMatrix_Cnf->CharDispNow = ch;
		LedMatrix_Cnf->IsIdle = 0;
	} else if(LedMatrix_Cnf->IsIdle == 0) {
		for(uint8_t idx = 0; idx < 7; idx++) {
			HC138_Select(LedMatrix_Cnf->Decoder, idx);      
			HC595_SendByte(LedMatrix_Cnf->ICLatch, *(ch+idx));
			HC595_Latch(LedMatrix_Cnf->ICLatch);
			HAL_Delay(3);
		}
		LedMatrix_Cnf->TimeDisplay += 21;
		if(LedMatrix_Cnf->TimeDisplay >= TimeDisplay) {
			LedMatrix_Cnf->TimeDisplay = 0;
			LedMatrix_Cnf->IsIdle = 1;
		}
	}
}
