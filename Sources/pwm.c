 /*--------------------------------------
* 电机和舵机驱动模块
* Jerry Lei
* 2015.3.1
--------------------------------------*/

#include "main.h"
#include "pwm.h"

void initPWM(){
  PWME = 0X00;      //关闭所有通道
  PWMPOL = 0XFF;    //极性，高电平开始
  
  PWMCTL = 0XF0;    //01级联 ... 67级联   
  PWMPRCLK = 0x11;  //CLOCK B,A时钟频率  20M  20M
  PWMCLK = 0xFF;    //选择CLOCK SA SB为PWM时钟
  PWMSCLA=5;        //Clock SA = Clock A / (2 * PWMSCLA),从CLOCK A 10分频，2M
  PWMSCLB=5;        //CLOCK SB从CLOCK B 10分频 ,20M/10=2M;
  PWMCAE=0;         //边沿对齐

  PWMPER67 = 2000;   //电机正转1kHZ
  PWMDTY67 = 0;     //占空比参数
  
  PWMPER45 = 2000;   //电机正转1kHZ
  PWMDTY45 = 0;     //占空比参数
  
  PWMPER23 = 40000; //舵机频率50HZ
  PWMDTY23 = STEER_CENTER;     //占空比参数
    
  PWME_PWME7 = 1;
  PWME_PWME5 = 1;     //电机输出使能
  PWME_PWME3 = 1;     //舵机输出使能
}