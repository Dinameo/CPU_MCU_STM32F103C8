#ifndef FSM_H
#define FSM_H

#include "main.h"
#include "SevSeg.h"

#define BT_PRESSED	GPIO_PIN_RESET   
#define BT_RELEASE	GPIO_PIN_SET

#define TIME3_DELAY	1000U
#define TIME4_DELAY 2000U

typedef struct {
	GPIO_TypeDef* B1_PORT;
	GPIO_TypeDef*	B2_PORT;
	GPIO_TypeDef*	B3_PORT;
	GPIO_TypeDef*	B4_PORT;
	
	uint16_t B1_PIN;
	uint16_t B2_PIN;
	uint16_t B3_PIN;
	uint16_t B4_PIN;
	
}	FSM_Conf;

void FSM_LOOP(FSM_Conf* FSM, SevSeg_Conf* SevSeg);
void FSM_Read(FSM_Conf* FSM);


typedef enum {
	STATE_0,
	STATE_1,
	STATE_2,
	STATE_3,
	STATE_4,
	STATE_MAX
} State_t;


#endif