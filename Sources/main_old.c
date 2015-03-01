#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#define steer_center 1500     //����м�ֵ

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
*  ��ˮ��
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
      for(j=0; j < 800; ++j)    // forѭ��ʱ�䲻׼ȷ�����ö�ʱ��
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
*  ������
***************/
void handEncoder(){
  unsigned char tmp;
  
  for(;;){    
    tmp = PORTE | 0XF0;  // �͵�ƽ����
    PORTB = tmp;
  }

}

/***************
*  PWM��ʼ��
***************/
void initPWM(){
  PWME = 0X00;      //�ر�����ͨ��
  PWMPOL = 0XFF;    //���ԣ��ߵ�ƽ��ʼ
  PWMPRCLK = 0X66;  // ����ʱ��/64
  PWMCTL = 0XF0;    //01���� ... 67����         
  PWMCLK = 0X00;    // ѡ�� A��BΪPWMʱ��
  PWMCAE = 0X00;

  PWMPER67 = 200;   //�����ת5kHZ
  PWMDTY67 = 0;     //ռ�ձȲ���
  
  PWMPER45 = 200;   //�����ת5kHZ
  PWMDTY45 = 0;     //ռ�ձȲ���
  
  PWMPER23 = 20000; //���Ƶ��50HZ
  PWMDTY23 = 2000;     //ռ�ձȲ���
  
  
  PWME_PWME7 = 1;
  PWME_PWME5 = 1;     //������ʹ��
  PWME_PWME3 = 1;     //������ʹ��
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
