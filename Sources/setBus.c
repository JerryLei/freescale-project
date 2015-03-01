#include "main.h"

uint synr = 0;
long BUS_CLOCK = 0;   //总线频率

void INIT_PLL(PLLx pllx){
	CLKSEL_PLLSEL = 0;   // CLKSEL.7 =0,  THEN BUSCLOCK = OSCCLK / 2; =1, BUSCLOCK = PLLCLK / 2
	PLLCTL_PLLON = 0;    // PLCTL.6 = 0, 关闭PLL
	switch(pllx){
	case PLL16: {        
		synr = 0x00 | 0x01; BUS_CLOCK = 16000000; break;}
	case PLL32: {
		synr = 0x40 | 0x03; BUS_CLOCK = 32000000; break;}
	case PLL40: {
		synr = 0xc0 | 0x01; BUS_CLOCK = 40000000; break;}
	case PLL48: {
		synr = 0xc0 | 0x05; BUS_CLOCK = 48000000; break;}
	case PLL64: {
		synr = 0xc0 | 0x07; BUS_CLOCK = 64000000; break;}
	case PLL80: {
		synr = 0xc0 | 0x09; BUS_CLOCK = 80000000; break;}
	case PLL88: {
		synr = 0xc0 | 0x0a; BUS_CLOCK = 88000000; break;}
	case PLL96: {
		synr = 0xc0 | 0x0b; BUS_CLOCK = 96000000; break;}
	default : 
		break;
	}
	SYNR = synr;
	REFDV = 0x80 | 0x01;   // pllclock=2*osc*(1+SYNR)/(1+REFDV)
	POSTDIV = 0X00;
	PLLCTL_PLLON = 1;
	_asm(nop);
	_asm(nop);
	while(CRGFLG_LOCK == 0);
	CLKSEL_PLLSEL = 1;
}