#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#define steer_center 1500     //舵机中间值

void initGPIO(){
  DDRA = 0x00;    // input
  DDRB = 0xFF;    // output
  DDRE = 0x00;    // input
  
  PORTB = 0XFF;   
}

void setBusCLK_64M(void){
  CLKSEL = 0X00;
  PLLCTL_PLLON = 1;
  SYNR = 0XC0 | 0X07;
  REFDV = 0X80 | 0X01;
  POSTDIV = 0X00;
  _asm(nop);
  _asm(nop);
  while(!(CRGFLG_LOCK == 1));
  CLKSEL_PLLSEL = 1;    
}


/***************
*  流水灯
***************/
void programForLED(){
  unsigned char tmp1, tmp2;
  unsigned int i, j, k, a, b, c;
  
  for(;;){
    tmp1 = 0X01;
    tmp2 = 0X80;
    for(i=0; i < 8; ++i){
      PORTB = ~tmp1;
      tmp1 *= 2;
      for(j=0; j < 800; ++j)    // for循环时间不准确，需用定时器
        for(k=0; k < 4000; ++k)
          ;    
    }
    
    for(a=0; a < 8; ++a){
      PORTB = ~tmp2;
      tmp2 /= 2;
      for(b=0; b < 800; ++b)
        for(c=0; c < 4000; ++c)
          ;
    }
  }
  
}

/***************
*  拨码盘
***************/
void handEncoder(){
  unsigned char tmp;
  
  for(;;){    
    tmp = PORTE | 0XF0;  // 低电平亮灯
    PORTB = tmp;
  }

}

/***************
*  PWM初始化
***************/
void initPWM(){
  PWME = 0X00;      //关闭所有通道
  PWMPOL = 0XFF;    //极性，高电平开始
  PWMPRCLK = 0X66;  // 总线时钟/64
  PWMCTL = 0XF0;    //01级联 ... 67级联         
  PWMCLK = 0X00;    // 选择 A、B为PWM时钟
  PWMCAE = 0X00;

  PWMPER67 = 200;   //电机正转5kHZ
  PWMDTY67 = 0;     //占空比参数
  
  PWMPER45 = 200;   //电机正转5kHZ
  PWMDTY45 = 0;     //占空比参数
  
  PWMPER23 = 20000; //舵机频率50HZ
  PWMDTY23 = 2000;     //占空比参数
  
  
  PWME_PWME7 = 1;
  PWME_PWME5 = 1;     //电机输出使能
  PWME_PWME3 = 1;     //舵机输出使能
}

/***************
*  main
***************/
void main(void) {
  /* put your own code here */

  DisableInterrupts;
  initGPIO();
  setBusCLK_64M();
  //handEncoder();
  initPWM();
  //programForLED();
  
  
  EnableInterrupts;
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
