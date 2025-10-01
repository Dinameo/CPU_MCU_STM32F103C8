#ifndef __LIBS_H

#include "main.h"
#define BT_COMP(BT_Index, BT_VAL, STAT) (((BT_VAL >> BT_Index) & 0x1) == STAT)
#define PRESSED GPIO_PIN_RESET
#define RELEASE	GPIO_PIN_SET
#define T3_MAX 100

typedef enum {
	Idle,
	Increment,
	Decrement,
	AutoDec,
	WaitePause,
	Reset
} FSM_State_t;
typedef enum {
	BT1,
	BT2,
	BT3,
	BT4
} Button_Idx;
void tensv_74hc595_put (uint8_t ch);
void tensv_LEDDecode(uint8_t num);
void tensv_LED7seg_PutNum(uint32_t num);
void tensv_LED7seg_PutMatrix(uint8_t* str);
void tensv_LED7seg_PutString(uint8_t* str);
uint8_t ButtonRead(void);
void FSM_B1(void);
void FSM_B2(void);
void FSM_B3(void);
void FSM_B4(void);
void FSM_LOOP(void);
#endif