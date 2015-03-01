#ifndef _OLED_H
#define _OLED_H
#include "derivative.h"  // error c2450

void initLCD(void);
void clsLCD();
void writeCmd(byte cmd);
void writeData(byte data);
void fillLCD(byte data);
void lcdP6x8Str(byte x, byte y, byte ch[]);
void lcdP8x16Str(byte x, byte y, byte ch[]);
void lcdP14x16Str(byte x, byte y, byte ch[]);
void lcdPrint(byte x, byte y, byte ch[]);



#endif