 /*--------------------------------------
* ����Ͷ������ģ��
* Jerry Lei
* 2015.3.1
--------------------------------------*/

#include "main.h"
#include "pwm.h"

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
  PWMDTY23 = STEER_CENTER;     //ռ�ձȲ���
    
  PWME_PWME7 = 1;
  PWME_PWME5 = 1;     //������ʹ��
  PWME_PWME3 = 1;     //������ʹ��
}