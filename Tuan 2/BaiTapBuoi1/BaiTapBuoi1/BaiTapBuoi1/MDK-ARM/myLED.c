#include "myLED.h"
#include "main.h"

char _7seg_code[] = {
	0x3F, // -> 0
	0x06, // -> 1
	0x5B, // -> 2
	0x4F, // -> 3
	0x66, // -> 4
	0x6D, // -> 5
	0x7D, // -> 6
	0x07, // -> 7
	0x7F, // -> 8
	0x6F, // -> 9
};
_7SEG_PINS L1 = {
	.PORT = GPIOA,
	.SEG_A = L1A_Pin,
	.SEG_B = L1B_Pin,
	.SEG_C = L1C_Pin,
	.SEG_D = L1D_Pin,
	.SEG_E = L1E_Pin,
	.SEG_F = L1F_Pin,
	.SEG_G = L1G_Pin
};
_7SEG_PINS L2 = {
	.PORT = GPIOA,
	.SEG_A = L2A_Pin,
	.SEG_B = L2B_Pin,
	.SEG_C = L2C_Pin,
	.SEG_D = L2D_Pin,
	.SEG_E = L2E_Pin,
	.SEG_F = L2F_Pin,
	.SEG_G = L2G_Pin
};
_7SEG_PINS L3 = {
	.PORT = GPIOB,
	.SEG_A = L3A_Pin,
	.SEG_B = L3B_Pin,
	.SEG_C = L3C_Pin,
	.SEG_D = L3D_Pin,
	.SEG_E = L3E_Pin,
	.SEG_F = L3F_Pin,
	.SEG_G = L3G_Pin
};
_7SEG_PINS L4 = {
	.PORT = GPIOB,
	.SEG_A = L4A_Pin,
	.SEG_B = L4B_Pin,
	.SEG_C = L4C_Pin,
	.SEG_D = L4D_Pin,
	.SEG_E = L4E_Pin,
	.SEG_F = L4F_Pin,
	.SEG_G = L4G_Pin
};

_7SEG_PINS *_7SEG[] = {&L1, &L2, &L3, &L4};

void LED_put(char LED, char num)
{
	HAL_GPIO_WritePin(_7SEG[LED]->PORT, _7SEG[LED]->SEG_A, (GPIO_PinState) (_7seg_code[num]&0x01));
	HAL_GPIO_WritePin(_7SEG[LED]->PORT, _7SEG[LED]->SEG_B, (GPIO_PinState) (_7seg_code[num]&0x02));
	HAL_GPIO_WritePin(_7SEG[LED]->PORT, _7SEG[LED]->SEG_C, (GPIO_PinState) (_7seg_code[num]&0x04));
	HAL_GPIO_WritePin(_7SEG[LED]->PORT, _7SEG[LED]->SEG_D, (GPIO_PinState) (_7seg_code[num]&0x08));
	HAL_GPIO_WritePin(_7SEG[LED]->PORT, _7SEG[LED]->SEG_E, (GPIO_PinState) (_7seg_code[num]&0x10));
	HAL_GPIO_WritePin(_7SEG[LED]->PORT, _7SEG[LED]->SEG_F, (GPIO_PinState) (_7seg_code[num]&0x20));
	HAL_GPIO_WritePin(_7SEG[LED]->PORT, _7SEG[LED]->SEG_G, (GPIO_PinState) (_7seg_code[num]&0x40));
}
uint8_t Split_num(uint32_t *num)
{
	uint8_t digit = *num%10;
	*num /= 10;
	return digit;
}
void LED_display(uint32_t num)
{
	
	LED_put(LED_3, Split_num(&num));
	LED_put(LED_2, Split_num(&num));
	LED_put(LED_1, Split_num(&num));
	LED_put(LED_0, Split_num(&num));
}