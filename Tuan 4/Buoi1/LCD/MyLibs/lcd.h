#ifndef __LCD_H
#define __LCD_H

#include "main.h"


#define LCD_CLS_DISP							0x01		// Clear display
#define LCD_HOME									0x02		// Return home

#define LCD_ENTR_MD_BASE					0x04		// NO INC, NO SHIFT
#define LCD_ENTR_MD_INC						0x02		// INC
#define LCD_ENTR_MD_SHIFT					0x01		// SHIFT



#define LCD_DISP_BASE							0x08		// Display Off, Cursor off, blink off
#define LCD_DISP_ON								0x04		// Display on
#define LCD_DISP_CURSOR						0x02		// Cursor on
#define LCD_DISP_BLINK						0x01		// Blink Cursor



#define LCD_FUNC_SET_BASE					0x20		// Function set 4bit, 1 line, 5x8 dots
#define LCD_FUNC_SET_8BIT					0x10		// Function set 8 bit
#define LCD_2LINES_5x8						0x08		// Function set 2 lines, 5x8 dots 10
#define LCD_1LINE_5x10						0x04		// Function set 1 line, 5x10 dots 




#define LCD_SET_CGGRAM_ADDR_BASE	0x40		// Set CGRAM ADDRESS






typedef enum {
	LCD4bit,
	LCD8bit
} LCDmode_t;

typedef struct {
	GPIO_TypeDef* D0_Port;
	GPIO_TypeDef* D1_Port;
	GPIO_TypeDef* D2_Port;
	GPIO_TypeDef* D3_Port;
	GPIO_TypeDef* D4_Port;
	GPIO_TypeDef* D5_Port;
	GPIO_TypeDef* D6_Port;
	GPIO_TypeDef* D7_Port;
	
	GPIO_TypeDef* EN_Port;
	GPIO_TypeDef* RS_Port;
	GPIO_TypeDef* RW_Port;
	
	
	uint16_t			D0_Pin;
	uint16_t			D1_Pin;
	uint16_t			D2_Pin;
	uint16_t			D3_Pin;
	uint16_t			D4_Pin;
	uint16_t			D5_Pin;
	uint16_t			D6_Pin;
	uint16_t			D7_Pin;
	
	uint16_t			EN_Pin;
	uint16_t			RS_Pin;
	uint16_t			RW_Pin;
	
}	HardwareInf_t;

void LCD_put(HardwareInf_t* LCDInf, uint8_t data);
void LCD_putString(HardwareInf_t* LCDInf, uint8_t *s);
void LCD_gotoXY(HardwareInf_t* LCDInf, uint8_t X, uint8_t Y);
void LCD_CGinit(HardwareInf_t* LCDInf, uint8_t *CGcode, uint8_t Pos);
void LCD_putcmd(HardwareInf_t* LCDInf, uint8_t cmd);
void LCD_putchar(HardwareInf_t* LCDInf, uint8_t ch);


void Send_8bit(HardwareInf_t* LCDInf, uint8_t bitdata);
void Send_4bit(HardwareInf_t* LCDInf, uint8_t bitdata);


void LCD4bit_Init(HardwareInf_t* LCDInf);
void LCD8bit_Init(HardwareInf_t* LCDInf);

void LCD_init(HardwareInf_t* LCDInf, LCDmode_t LCDmode);



#endif