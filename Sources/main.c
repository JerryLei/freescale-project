#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#define steer_center  3000    //舵机中间值
#define steer_left    2600    //舵机左转最大值
#define steer_right   3400    //舵机右转最大值 

int speed;    // 编码器返回速度


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
  PWMDTY23 = steer_center;     //占空比参数
  
  
  PWME_PWME7 = 1;
  PWME_PWME5 = 1;     //电机输出使能
  PWME_PWME3 = 1;     //舵机输出使能
}


/***************
*  舵机转向测试
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
*PIT定时中断时间设置
***************/
void interruptTimeInit(){
  PITCFLMT_PITE = 0;    // 关闭PIT
  PITCE_PCE0 = 1;       // 通道使能
  
  PITMTLD0 = 40 - 1;    // 8位定时器初值设定，总线40分频
  PITLD0 = 10000 - 1;    //10ms，(PITMTLD0 + 1)*(PITLD0 + 1) / fBUS
  
  PITMUX = 0X00;        // 与微时基0相连
  PITINTE_PINTE0 = 1;   // 开通PIT0定时器的溢出中断
  PITCFLMT_PITE = 1;    // PIT使能
}

/***************
* 计数器初始化
***************/
void initPCNT(){
  PACTL = 0X50;         // 端口初始化
  PACNT = 0X0000;   

}

/***************
* PIT0~3中断向量为66 ~ 68
***************/
#pragma CODE_SEG NON_BANKED    // 中断函数置于非分页区域内
// 飞思卡尔16位单片机的中断向量是16位
// 所以中断函数只有被置于非分页区内才能被寻址到
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
  
  PWMDTY67 = 1000;    //电机PWM输出50%占空比
  PORTB_PB4 = 1;      //74ls244使能
  
  interruptTimeInit();
  initPCNT();
  
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
