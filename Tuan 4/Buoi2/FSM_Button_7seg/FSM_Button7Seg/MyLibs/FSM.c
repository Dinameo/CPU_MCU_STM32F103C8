#include "FSM.h"
#include "SevSeg.h"

static State_t B1_State = STATE_0;
static State_t B2_State = STATE_0;
static State_t B3_State = STATE_0;
static State_t B4_State = STATE_0;

static GPIO_PinState B1_Val;
static GPIO_PinState B2_Val;
static GPIO_PinState B3_Val;
static GPIO_PinState B4_Val;

static uint16_t T3 = 0;
static uint16_t T4 = 0;



static SevSegDigit_t Digit = DIGIT_0;


void FSM_Read(FSM_Conf* FSM) {
	B1_Val = HAL_GPIO_ReadPin(FSM->B1_PORT, FSM->B1_PIN);
	B2_Val = HAL_GPIO_ReadPin(FSM->B2_PORT, FSM->B2_PIN);
	B3_Val = HAL_GPIO_ReadPin(FSM->B3_PORT, FSM->B3_PIN);
	B4_Val = HAL_GPIO_ReadPin(FSM->B4_PORT, FSM->B4_PIN);
}

void FSM_LOOP(FSM_Conf* FSM, SevSeg_Conf* SevSeg) {
	FSM_Read(FSM);
	HAL_Delay(1);
	// B1 Count up
	
	// B1 State 0, Init
	if(B1_State == STATE_0) {
		SevSeg_DisplayDigit(SevSeg, DIGIT_0);
		B1_State = STATE_1;
	} 
	// B1 State 1, Cho nut nhan
	else if(B1_State == STATE_1) {
		if(B1_Val == BT_PRESSED) {
			if(Digit < DIGIT_9) {
				B1_State = 2;
			}
		}
	} 
	// B1 State 2, Cho nha nut nhan
	else if(B1_State == STATE_2) {
		if(B1_Val == BT_RELEASE) {
			Digit++;
			SevSeg_DisplayDigit(SevSeg, Digit);
			B1_State = STATE_1;
		}
	} 
	
	
	// B2 Count down
	
	// B2 State 0, Init
	if(B2_State == STATE_0) {
		SevSeg_DisplayDigit(SevSeg, DIGIT_0);
		B2_State = STATE_1;
	} 
	// B2 State 1
	else if(B2_State == STATE_1) {
		if(B2_Val == BT_PRESSED) {
			if(Digit > DIGIT_0) {
				Digit--;
				SevSeg_DisplayDigit(SevSeg, Digit);
				B2_State = 2;
			}
		}
	} 
	// B2 State 2, CHo nha nut nhan
	else if(B2_State == STATE_2) {
		if(B2_Val == BT_RELEASE) {
			B2_State = STATE_1;
		}
	} 

	
	// B3 Automatically counts up
	
	// B3 State 0
	if(B3_State == STATE_0) {
		SevSeg_DisplayDigit(SevSeg, DIGIT_0);
		B3_State = STATE_1;
	} 
	// B3 State 1
	else if(B3_State == STATE_1) {
		if(B3_Val == BT_PRESSED) {
			B3_State = STATE_2;
		}
	} 
	else if(B3_State == STATE_2) {
		if(B3_Val == BT_RELEASE) {
			B3_State = STATE_3;
		}
	} else if(B3_State == STATE_3) {
		if(B3_Val == BT_RELEASE) {
			if(T3 < TIME3_DELAY) {
				T3++;
			} else {
				T3 = 0;
				if(Digit < DIGIT_9) {
					Digit++;
					SevSeg_DisplayDigit(SevSeg, Digit);
				} else {
					B3_State = STATE_1;
				}
			}
		} else {
			B3_State = STATE_4;
		}
	} 
	else if(B3_State == STATE_4) {
		if(B3_Val == BT_RELEASE) {
			T3 = 0;
			B3_State = STATE_1;
		}
	}
	// B3 State 0
//	if(B3_State == STATE_0) {
//		SevSeg_DisplayDigit(SevSeg, DIGIT_0);
//		B3_State = STATE_1;
//	} 
//	// B3 State 1
//	else if(B3_State == STATE_1) {
//		if(B3_Val == BT_PRESSED) {
//			B3_State = STATE_2;
//		}
//	} else if(B3_State == STATE_2) {
//		if(B3_Val == BT_PRESSED) {
//			if(T3 < TIME3_DELAY) {
//				T3++;
//			} else {
//				T3 = 0;
//				if(Digit < DIGIT_9) {
//					Digit++;
//					SevSeg_DisplayDigit(SevSeg, Digit);
//				} else {
//					B3_State = STATE_1;
//				}
//			}
//		} else {
//			B3_State = STATE_3;
//		}
//	} 
//	else if(B3_State == STATE_3) {
//		if(B3_Val == BT_RELEASE) {
//			if(T3 < TIME3_DELAY) {
//				T3++;
//			} else {
//				T3 = 0;
//				if(Digit < DIGIT_9) {
//					Digit++;
//					SevSeg_DisplayDigit(SevSeg, Digit);
//				} else {
//					B3_State = STATE_1;
//				}
//			}
//		} else {
//			B3_State = STATE_4;
//		}
//	}
//	else if(B3_State == STATE_4) {
//		if(B3_Val == BT_RELEASE) {
//			T3 = 0;
//			B3_State = STATE_1;
//		}
//	}
	// B4 Reset
	// B4 State 0
	if(B4_State == 0) {
		SevSeg_DisplayDigit(SevSeg, DIGIT_0);
		B4_State = STATE_1;
	}
	// B4 State 1
	else if(B4_State == STATE_1) {
		if(B4_Val == BT_PRESSED) {
			if(T4 < TIME4_DELAY) {
				T4++;
			} else {
				T4 = 0;
				Digit = 0;
				SevSeg_DisplayDigit(SevSeg, Digit);
				B3_State = STATE_1;
				B4_State = STATE_2;
			}
		} else {
			T4 = 0;
		}
	}
	// B4 State 2
	else if(B4_State ==  STATE_2) {
		if(B4_Val == BT_RELEASE) {
			B4_State = STATE_1;
		}
	}
}