#ifndef __MYLED_H
#define __MYLED_H

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"

typedef struct 
{
	GPIO_TypeDef* PORT;
	uint16_t SEG_A;
	uint16_t SEG_B;
	uint16_t SEG_C;
	uint16_t SEG_D;
	uint16_t SEG_E;
	uint16_t SEG_F;
	uint16_t SEG_G;
} _7SEG_PINS;

typedef enum {
	LED_0,
	LED_1,
	LED_2,
	LED_3,
} STT_LED;

extern char _7seg_code[];
extern _7SEG_PINS *_7SEG[];

void LED_put(char LED, char num);
void LED_display(uint32_t num);
uint8_t Split_num(uint32_t *num);

#ifdef __cplusplus
}
#endif


#endif