#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#define steer_center  3000    //����м�ֵ
#define steer_left    2600    //�����ת���ֵ
#define steer_right   3400    //�����ת���ֵ 

int speed;    // �����������ٶ�


void initGPIO(){
  DDRA = 0x00;    // input
  DDRB = 0xFF;    // output
  DDRE = 0x00;    // input
  
  PORTB = 0XFF;   
}

void setBusCLK_40M(void){
  CLKSEL = 0X00;
  PLLCTL_PLLON = 1;
  SYNR = 0XC0 | 0X04;
  REFDV = 0X80 | 0X01;   // 16*2*5/2=80M    40M Bus
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
  
  PWMCTL = 0XF0;    //01���� ... 67����   
  PWMPRCLK = 0x11;  //CLOCK B,Aʱ��Ƶ��  20M  20M
  PWMCLK = 0xFF;    //ѡ��CLOCK SA SBΪPWMʱ��
  PWMSCLA=5;        //Clock SA = Clock A / (2 * PWMSCLA),��CLOCK A 10��Ƶ��2M
  PWMSCLB=5;        //CLOCK SB��CLOCK B 10��Ƶ ,20M/10=2M;
  PWMCAE=0;         //���ض���

  PWMPER67 = 2000;   //�����ת1kHZ
  PWMDTY67 = 0;     //ռ�ձȲ���
  
  PWMPER45 = 2000;   //�����ת1kHZ
  PWMDTY45 = 0;     //ռ�ձȲ���
  
  PWMPER23 = 40000; //���Ƶ��50HZ
  PWMDTY23 = steer_center;     //ռ�ձȲ���
  
  
  PWME_PWME7 = 1;
  PWME_PWME5 = 1;     //������ʹ��
  PWME_PWME3 = 1;     //������ʹ��
}


/***************
*  ���ת�����
***************/
void steerTurningTest(){
  static int turningFlag = 1;
  unsigned int centerCheck; 
  int i, j;
  for(;;){
    centerCheck = PORTE & 0X01;
    
    if(centerCheck == 0){
      PWMDTY23 = steer_center;        
    } else {      
      if(turningFlag == 1){
        PWMDTY23 = steer_right;
        turningFlag = -1;
      } else {
        PWMDTY23 = steer_left;
        turningFlag = 1;
      }
    }
    
    for(i=0; i < 2000; ++i)
      for(j=0; j < 4000; ++j)
        ;    
  }
}

/***************
*PIT��ʱ�ж�ʱ������
***************/
void interruptTimeInit(){
  PITCFLMT_PITE = 0;    // �ر�PIT
  PITCE_PCE0 = 1;       // ͨ��ʹ��
  
  PITMTLD0 = 40 - 1;    // 8λ��ʱ����ֵ�趨������40��Ƶ
  PITLD0 = 10000 - 1;    //10ms��(PITMTLD0 + 1)*(PITLD0 + 1) / fBUS
  
  PITMUX = 0X00;        // ��΢ʱ��0����
  PITINTE_PINTE0 = 1;   // ��ͨPIT0��ʱ��������ж�
  PITCFLMT_PITE = 1;    // PITʹ��
}

/***************
* ��������ʼ��
***************/
void initPCNT(){
  PACTL = 0X50;         // �˿ڳ�ʼ��
  PACNT = 0X0000;   

}

/***************
* PIT0~3�ж�����Ϊ66 ~ 68
***************/
#pragma CODE_SEG NON_BANKED    // �жϺ������ڷǷ�ҳ������
// ��˼����16λ��Ƭ�����ж�������16λ
// �����жϺ���ֻ�б����ڷǷ�ҳ���ڲ��ܱ�Ѱַ��
void interrupt 66 PIT0Interrupt(){
  speed = PACNT;
  PITTF_PTF0 = 1;
  PACNT = 0X0000;
  PORTB = 0XFE;
}
#pragma CODE_SEG DEFAULT

/***************
*  main
***************/
void main(void) {
  /* put your own code here */

  DisableInterrupts;
  initGPIO();
  setBusCLK_40M();
  //handEncoder();
  initPWM();
  //programForLED();
  //steerTurningTest();
   
  EnableInterrupts;
  
  PWMDTY67 = 1000;    //���PWM���50%ռ�ձ�
  PORTB_PB4 = 1;      //74ls244ʹ��
  
  interruptTimeInit();
  initPCNT();
  
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
