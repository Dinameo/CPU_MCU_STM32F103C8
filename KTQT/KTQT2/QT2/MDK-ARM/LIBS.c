#include "LIBS.h"
#include "main.h"


void tensv_74hc595_put(uint8_t ch) {
	for(int8_t i = 7; i >= 0; i--) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, (GPIO_PinState) ((ch >> i) & 0x1));
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
}

uint8_t Num_Arr[] = {
	0x40, // 0
	0xF8, // 1
	0x24, // 2
	0x30, // 3
	0x98, // 4
	0x12, // 5
	0x02, // 6
	0x78, // 7
	0x00, // 8
	0x10 	// 9
};

void tensv_LEDDecode(uint8_t num) {
	tensv_74hc595_put(Num_Arr[num%10]);
}

void tensv_LED7seg_PutNum(uint32_t num) {
	if(num > 999999) {
		for(uint8_t i = 0; i < 6; i++) {
			tensv_74hc595_put(0xFF);
		}	
		return;
	}
	uint8_t count_idx = 0;
	uint8_t flag = 1;
	while(count_idx < 6) {
		if(flag) {
			tensv_LEDDecode((uint8_t) (num%10));
			num /= 10;
			if(num == 0) {
				flag = 0;
			}
		} else {
			tensv_74hc595_put(0xFF);
		}
		
		
		
		count_idx++;
	}
	
	
//	uint8_t count_idx = 0;
//	do {
//		tensv_LEDDecode((uint8_t) (num%10));
//		num/=10;
//		count_idx++;
//	} while(num != 0);
//	
//	for(;count_idx < 6; count_idx++) {
//		tensv_74hc595_put(0xFF);
//	}
//	
	
	
}

void tensv_LED7seg_PutMatrix(uint8_t* str) {
	uint8_t idx = 0;
	uint8_t flag = 0;
	while(str[idx] != '\0') {
		if(str[idx] > '9' || str[idx] < '0') {
			flag = 1;
			break;
		} else if(idx > 5) {
			flag = 1;
			break;
		}
		idx++;
	}
	if(flag) {
		for(uint8_t i = 0; i < 6; i++) {
			tensv_74hc595_put(0xFF);
		}
	} else {
		tensv_LED7seg_PutString(str);
	}
}
void tensv_LED7seg_PutString(uint8_t* str) {
	int8_t len = 0;
	while(str[len] != '\0') {
		len++;
	}
	uint8_t i = 0;
	while(i < 6) {
		if(len != 0) {
			tensv_LEDDecode(str[len-1] - '0');
			len--;
		} else {
			tensv_74hc595_put(0xFF);
		}
		i++;
	}
}

uint8_t ButtonRead(void) {
	uint8_t ButtonByte = 0xFF;
	
	ButtonByte = (ButtonByte << 1) | HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15); // BT4
	ButtonByte = (ButtonByte << 1) | HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12); // BT3
	ButtonByte = (ButtonByte << 1) | HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);  // BT2
	ButtonByte = (ButtonByte << 1) | HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);  // BT1
		
	return (~ButtonByte);
	
}


extern uint8_t BT_Val_Pre;
extern uint8_t BT_Val;
extern uint8_t State_B1;
extern uint8_t State_B4;
extern uint8_t State_B3;
extern uint8_t State_B2;
extern uint32_t n;
extern uint16_t T3;
extern uint8_t Reset_Flag;
void FSM_B1(void) {
	switch(State_B1) {
		case Idle:
			if(BT_COMP(BT1, BT_Val, PRESSED) && BT_COMP(BT1, BT_Val_Pre, RELEASE)) {
				State_B1 = Increment;
			}
		break;
		case Increment:
			if(n < 999999) {
				n++;
				tensv_LED7seg_PutNum(n);
			} 
			State_B1 = Idle;
		break;
	}
}

void FSM_B2(void) {
	switch(State_B2) {
		case Idle:
			if(BT_COMP(BT2, BT_Val, PRESSED) && BT_COMP(BT2, BT_Val_Pre, RELEASE)) {
				State_B2 = Decrement;
			}
		break;
		case Decrement:
			if(n > 0) {
				n--;
				tensv_LED7seg_PutNum(n);
			} 
			State_B2 = Idle;
		break;
	}
}
void FSM_B3() {
	switch(State_B3) {
		case Idle:
			if(BT_COMP(BT3, BT_Val, PRESSED) && BT_COMP(BT3, BT_Val_Pre, RELEASE)) {
				Reset_Flag = 0;
				State_B3 = AutoDec;
			}
		break;
		case AutoDec:
			if(BT_COMP(BT3, BT_Val, PRESSED) && BT_COMP(BT3, BT_Val_Pre, RELEASE)) {
				T3 = 0;
				State_B3 = Idle;
			} else if(Reset_Flag) {
				T3 = 0;
				State_B3 = Idle;
				Reset_Flag = 0;
			} else if(T3 < T3_MAX) {
				T3++;
			} else { 
				T3 = 0;
				if(n > 0) {
					n--;
					tensv_LED7seg_PutNum(n);
				} else {
					State_B3 = Idle;
				}
			}
		break;
	}
}
void FSM_B4(void) {
	switch(State_B4) {
		case Idle:
			if(BT_COMP(BT4, BT_Val, PRESSED) && BT_COMP(BT4, BT_Val_Pre, RELEASE)) {
				State_B4 = Reset;
			}
		break;
		case Reset:
			n 	= 146000;
			State_B4 = Idle;
			Reset_Flag = 1;
			tensv_LED7seg_PutNum(n);
		break;
	}
}
void FSM_LOOP(void) {
	BT_Val_Pre = BT_Val;
	BT_Val = ButtonRead();
	FSM_B1();
	FSM_B2();
	FSM_B3();
	FSM_B4();
	HAL_Delay(1);
} 