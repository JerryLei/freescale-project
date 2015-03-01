#ifndef _SETBUS_H
#define _SETBUS_H

/*--------------------------------------
* ��������Ƶ��
* Jerry Lei
* 2015.3.1
--------------------------------------*/

typedef enum PLLx{
	PLL16,
	PLL32,
	PLL40,
	PLL48,
	PLL64,
	PLL80,
	PLL88,
	PLL96	
} PLLx;

void INIT_PLL(PLLx pllx);
#endif