#include "lcd.h"

static LCDmode_t LCD_MODE;


void Send_4bit(HardwareInf_t* LCDInf, uint8_t bitdata) {
	HAL_GPIO_WritePin(LCDInf->D4_Port, LCDInf->D4_Pin, (GPIO_PinState) ((bitdata >> 0) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D5_Port, LCDInf->D5_Pin, (GPIO_PinState) ((bitdata >> 1) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D6_Port, LCDInf->D6_Pin, (GPIO_PinState) ((bitdata >> 2) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D7_Port, LCDInf->D7_Pin, (GPIO_PinState) ((bitdata >> 3) & 0x01));
	
	// Start send
	HAL_GPIO_WritePin(LCDInf->EN_Port, LCDInf->EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCDInf->EN_Port, LCDInf->EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}
void Send_8bit(HardwareInf_t* LCDInf, uint8_t bitdata) {
	
	HAL_GPIO_WritePin(LCDInf->D0_Port, LCDInf->D0_Pin, (GPIO_PinState) ((bitdata >> 0) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D1_Port, LCDInf->D1_Pin, (GPIO_PinState) ((bitdata >> 1) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D2_Port, LCDInf->D2_Pin, (GPIO_PinState) ((bitdata >> 2) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D3_Port, LCDInf->D3_Pin, (GPIO_PinState) ((bitdata >> 3) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D4_Port, LCDInf->D4_Pin, (GPIO_PinState) ((bitdata >> 4) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D5_Port, LCDInf->D5_Pin, (GPIO_PinState) ((bitdata >> 5) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D6_Port, LCDInf->D6_Pin, (GPIO_PinState) ((bitdata >> 6) & 0x01));
	HAL_GPIO_WritePin(LCDInf->D7_Port, LCDInf->D7_Pin, (GPIO_PinState) ((bitdata >> 7) & 0x01));
	
	// Start send
	HAL_GPIO_WritePin(LCDInf->EN_Port, LCDInf->EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCDInf->EN_Port, LCDInf->EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void LCD_put(HardwareInf_t* LCDInf, uint8_t data) {
	if(LCD_MODE == LCD4bit) {
		
		Send_4bit(LCDInf, (data >> 4) & 0x0F);
		Send_4bit(LCDInf, data & 0x0F);
	} else {
		Send_8bit(LCDInf, data);
	}
}


void LCD_putcmd(HardwareInf_t* LCDInf, uint8_t cmd) {
	HAL_GPIO_WritePin(LCDInf->RS_Port, LCDInf->RS_Pin, GPIO_PIN_RESET);		// RS LOW
	HAL_GPIO_WritePin(LCDInf->RW_Port, LCDInf->RW_Pin, GPIO_PIN_RESET);		// Write Mode
	
	LCD_put(LCDInf, cmd);
}

void LCD_putchar(HardwareInf_t* LCDInf, uint8_t ch) {
	HAL_GPIO_WritePin(LCDInf->RS_Port, LCDInf->RS_Pin, GPIO_PIN_SET);		  // RS HIGH 
	HAL_GPIO_WritePin(LCDInf->RW_Port, LCDInf->RW_Pin, GPIO_PIN_RESET);		// Write Mode
	
	LCD_put(LCDInf, ch);
}


void LCD_putString(HardwareInf_t* LCDInf, uint8_t* s) {
	while(*s != '\0') {
		LCD_putchar(LCDInf, *s);
		s++;
	}
}
void LCD_gotoXY(HardwareInf_t* LCDInf, uint8_t X, uint8_t Y) {
	Y %= 2; X %= 16;
	if(Y == 0) {	// Y is False | Y == 0
		LCD_putcmd(LCDInf, 0x80 + X);	// Hang 0 cot x
	} else {
		LCD_putcmd(LCDInf, 0xC0 + X);	// Hang 1 cot x
	}
}
void LCD_CGinit(HardwareInf_t* LCDInf, uint8_t *CGcode, uint8_t Pos) {
	
	for(uint8_t i = 0; i < 8; i++) {
		LCD_putcmd(LCDInf, LCD_SET_CGGRAM_ADDR_BASE | (Pos<<3) | i); 
		LCD_putchar(LCDInf, *(CGcode + i)); 
	}
}
void LCD4bit_Init(HardwareInf_t* LCDInf) {
	HAL_Delay(40);
	LCD_putcmd(LCDInf, 0x3);	// 1 lenh 3 
	HAL_Delay(5);
	LCD_putcmd(LCDInf, 0x3);  // 2 lenh 3
	HAL_Delay(1);
	LCD_putcmd(LCDInf, 0x3);	// 3 lenh 3

	LCD_putcmd(LCDInf, 0x2);	// 1 lenh 2
	
	
	LCD_putcmd(LCDInf, LCD_FUNC_SET_BASE | LCD_2LINES_5x8);	// 1 lenh 2, 5x8 2 lines
	LCD_putcmd(LCDInf, LCD_DISP_BASE | LCD_DISP_ON | LCD_DISP_CURSOR | LCD_DISP_BLINK);
	LCD_putcmd(LCDInf, LCD_CLS_DISP);	// Display clear
	LCD_putcmd(LCDInf, LCD_ENTR_MD_BASE | LCD_ENTR_MD_INC);	// Increment
}
void LCD8bit_Init(HardwareInf_t* LCDInf) {
	HAL_Delay(40);
	LCD_putcmd(LCDInf, 0x30);	// 1 lenh 3
	HAL_Delay(5);
	LCD_putcmd(LCDInf, 0x30);  // 2 lenh 3
	HAL_Delay(1);
	LCD_putcmd(LCDInf, 0x30);	// 3 lenh 3
	
	
	LCD_putcmd(LCDInf, LCD_FUNC_SET_BASE | LCD_FUNC_SET_8BIT | LCD_2LINES_5x8);	// 5x8, 2 lines
	LCD_putcmd(LCDInf, LCD_DISP_BASE | LCD_DISP_ON | LCD_DISP_CURSOR | LCD_DISP_BLINK);	// Blink cursor on, cursor on, Display on 
	LCD_putcmd(LCDInf, LCD_CLS_DISP);	// Display clear
	LCD_putcmd(LCDInf, LCD_ENTR_MD_BASE | LCD_ENTR_MD_INC);	// Increment, No shift
}
void LCD_init(HardwareInf_t* LCDInf, LCDmode_t LCDmode) {
	
	if(LCDmode == LCD4bit) {
		LCD_MODE = LCD4bit;
		LCD4bit_Init(LCDInf);
	} else {
		LCD_MODE = LCD8bit;
		LCD8bit_Init(LCDInf);
	}
}