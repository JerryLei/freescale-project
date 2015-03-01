 /*--------------------------------------
* 摄像头模块 龙邱 ov7620
* Jerry Lei
* 2015.3.1
--------------------------------------*/
#include "main.h"

#define rowNum 40			//扫描行数
#define colNum 120			//扫描列数

byte rowsC = 0;
byte linesC = 0;
byte linesCount = 0;
byte interval = 0;
byte curLine = 0;
byte image[rowNum][colNum];

void delayOv7620(int ms){
  int i, j;
  if(ms < 1)
    ms = 1;
  for(i=0; i < ms; ++i)
    for(j=0; j < 1335; ++j)
      ;
}

/*---------------------------------
* 摄像头管脚初始化
*/
void initOv7620(){
  
  TIOS = 0X00;    // 输入捕捉
  TSCR2 = 0X00;   // 1倍时钟分频
  
  TCTL3 = 0X00;
  TCTL4 = 0X05;
  
  TSCR1 = 0X80;   // 打开时钟
  TIE_C1I = 0X01; // 关闭场中断
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
/**
* 场中断处理函数
*/
__interrupt 9 void vsyncINT(){
  
  curLine = 0;
  TIE_C1I = 0X00; // 关闭场中断
  TIE_C0I = 0X01; // 打开行中断
  TFLG1_C1F = 0X01; //清除场同步中断
   
  rowsC++;
}

/**
* 行中断处理函数
*/
__interrupt 8 void chsyncINT(){
   linesCount++;
   if((linesCount < 50) || (linesCount > 240))
      return ;
   
   interval = 3;
   if(linesCount % interval == 0){
   
      getPixel();
      linesC++;
   }
   
   if(linesC >= 39){
      TIE_C0I = 0X00;   //关闭行中断
      TIE_C1I = 0X01;   //打开场中断   
   }
   TFLG1_C0F = 0X01;    //清除行中断标志   
}
#pragma CODE_SEG DEFAULT

/**
* 读取摄像头数据
*  //弃用循环，因为下述方式可以得到严格的时序
*/
void getPixel(){
	image[linesC][0] = PORTA; _asm(nop); _asm(nop);
	image[linesC][1] = PORTA; _asm(nop); _asm(nop);
	image[linesC][2] = PORTA; _asm(nop); _asm(nop);
	image[linesC][3] = PORTA; _asm(nop); _asm(nop);
	image[linesC][4] = PORTA; _asm(nop); _asm(nop);
	image[linesC][5] = PORTA; _asm(nop); _asm(nop);
	image[linesC][6] = PORTA; _asm(nop); _asm(nop);
	image[linesC][7] = PORTA; _asm(nop); _asm(nop);
	image[linesC][8] = PORTA; _asm(nop); _asm(nop);
	image[linesC][9] = PORTA; _asm(nop); _asm(nop);
	image[linesC][10] = PORTA; _asm(nop); _asm(nop);
	image[linesC][11] = PORTA; _asm(nop); _asm(nop);
	image[linesC][12] = PORTA; _asm(nop); _asm(nop);
	image[linesC][13] = PORTA; _asm(nop); _asm(nop);
	image[linesC][14] = PORTA; _asm(nop); _asm(nop);
	image[linesC][15] = PORTA; _asm(nop); _asm(nop);
	image[linesC][16] = PORTA; _asm(nop); _asm(nop);
	image[linesC][17] = PORTA; _asm(nop); _asm(nop);
	image[linesC][18] = PORTA; _asm(nop); _asm(nop);
	image[linesC][19] = PORTA; _asm(nop); _asm(nop);
	image[linesC][20] = PORTA; _asm(nop); _asm(nop);
	image[linesC][21] = PORTA; _asm(nop); _asm(nop);
	image[linesC][22] = PORTA; _asm(nop); _asm(nop);
	image[linesC][23] = PORTA; _asm(nop); _asm(nop);
	image[linesC][24] = PORTA; _asm(nop); _asm(nop);
	image[linesC][25] = PORTA; _asm(nop); _asm(nop);
	image[linesC][26] = PORTA; _asm(nop); _asm(nop);
	image[linesC][27] = PORTA; _asm(nop); _asm(nop);
	image[linesC][28] = PORTA; _asm(nop); _asm(nop);
	image[linesC][29] = PORTA; _asm(nop); _asm(nop);
	image[linesC][30] = PORTA; _asm(nop); _asm(nop);
	image[linesC][31] = PORTA; _asm(nop); _asm(nop);
	image[linesC][32] = PORTA; _asm(nop); _asm(nop);
	image[linesC][33] = PORTA; _asm(nop); _asm(nop);
	image[linesC][34] = PORTA; _asm(nop); _asm(nop);
	image[linesC][35] = PORTA; _asm(nop); _asm(nop);
	image[linesC][36] = PORTA; _asm(nop); _asm(nop);
	image[linesC][37] = PORTA; _asm(nop); _asm(nop);
	image[linesC][38] = PORTA; _asm(nop); _asm(nop);
	image[linesC][39] = PORTA; _asm(nop); _asm(nop);
	image[linesC][40] = PORTA; _asm(nop); _asm(nop);
	image[linesC][41] = PORTA; _asm(nop); _asm(nop);
	image[linesC][42] = PORTA; _asm(nop); _asm(nop);
	image[linesC][43] = PORTA; _asm(nop); _asm(nop);
	image[linesC][44] = PORTA; _asm(nop); _asm(nop);
	image[linesC][45] = PORTA; _asm(nop); _asm(nop);
	image[linesC][46] = PORTA; _asm(nop); _asm(nop);
	image[linesC][47] = PORTA; _asm(nop); _asm(nop);
	image[linesC][48] = PORTA; _asm(nop); _asm(nop);
	image[linesC][49] = PORTA; _asm(nop); _asm(nop);
	image[linesC][50] = PORTA; _asm(nop); _asm(nop);
	image[linesC][51] = PORTA; _asm(nop); _asm(nop);
	image[linesC][52] = PORTA; _asm(nop); _asm(nop);
	image[linesC][53] = PORTA; _asm(nop); _asm(nop);
	image[linesC][54] = PORTA; _asm(nop); _asm(nop);
	image[linesC][55] = PORTA; _asm(nop); _asm(nop);
	image[linesC][56] = PORTA; _asm(nop); _asm(nop);
	image[linesC][57] = PORTA; _asm(nop); _asm(nop);
	image[linesC][58] = PORTA; _asm(nop); _asm(nop);
	image[linesC][59] = PORTA; _asm(nop); _asm(nop);
	image[linesC][60] = PORTA; _asm(nop); _asm(nop);
	image[linesC][61] = PORTA; _asm(nop); _asm(nop);
	image[linesC][62] = PORTA; _asm(nop); _asm(nop);
	image[linesC][63] = PORTA; _asm(nop); _asm(nop);
	image[linesC][64] = PORTA; _asm(nop); _asm(nop);
	image[linesC][65] = PORTA; _asm(nop); _asm(nop);
	image[linesC][66] = PORTA; _asm(nop); _asm(nop);
	image[linesC][67] = PORTA; _asm(nop); _asm(nop);
	image[linesC][68] = PORTA; _asm(nop); _asm(nop);
	image[linesC][69] = PORTA; _asm(nop); _asm(nop);
	image[linesC][70] = PORTA; _asm(nop); _asm(nop);
	image[linesC][71] = PORTA; _asm(nop); _asm(nop);
	image[linesC][72] = PORTA; _asm(nop); _asm(nop);
	image[linesC][73] = PORTA; _asm(nop); _asm(nop);
	image[linesC][74] = PORTA; _asm(nop); _asm(nop);
	image[linesC][75] = PORTA; _asm(nop); _asm(nop);
	image[linesC][76] = PORTA; _asm(nop); _asm(nop);
	image[linesC][77] = PORTA; _asm(nop); _asm(nop);
	image[linesC][78] = PORTA; _asm(nop); _asm(nop);
	image[linesC][79] = PORTA; _asm(nop); _asm(nop);
	image[linesC][80] = PORTA; _asm(nop); _asm(nop);
	image[linesC][81] = PORTA; _asm(nop); _asm(nop);
	image[linesC][82] = PORTA; _asm(nop); _asm(nop);
	image[linesC][83] = PORTA; _asm(nop); _asm(nop);
	image[linesC][84] = PORTA; _asm(nop); _asm(nop);
	image[linesC][85] = PORTA; _asm(nop); _asm(nop);
	image[linesC][86] = PORTA; _asm(nop); _asm(nop);
	image[linesC][87] = PORTA; _asm(nop); _asm(nop);
	image[linesC][88] = PORTA; _asm(nop); _asm(nop);
	image[linesC][89] = PORTA; _asm(nop); _asm(nop);
	image[linesC][90] = PORTA; _asm(nop); _asm(nop);
	image[linesC][91] = PORTA; _asm(nop); _asm(nop);
	image[linesC][92] = PORTA; _asm(nop); _asm(nop);
	image[linesC][93] = PORTA; _asm(nop); _asm(nop);
	image[linesC][94] = PORTA; _asm(nop); _asm(nop);
	image[linesC][95] = PORTA; _asm(nop); _asm(nop);
	image[linesC][96] = PORTA; _asm(nop); _asm(nop);
	image[linesC][97] = PORTA; _asm(nop); _asm(nop);
	image[linesC][98] = PORTA; _asm(nop); _asm(nop);
	image[linesC][99] = PORTA; _asm(nop); _asm(nop);
	image[linesC][100] = PORTA; _asm(nop); _asm(nop);
	image[linesC][101] = PORTA; _asm(nop); _asm(nop);
	image[linesC][102] = PORTA; _asm(nop); _asm(nop);
	image[linesC][103] = PORTA; _asm(nop); _asm(nop);
	image[linesC][104] = PORTA; _asm(nop); _asm(nop);
	image[linesC][105] = PORTA; _asm(nop); _asm(nop);
	image[linesC][106] = PORTA; _asm(nop); _asm(nop);
	image[linesC][107] = PORTA; _asm(nop); _asm(nop);
	image[linesC][108] = PORTA; _asm(nop); _asm(nop);
	image[linesC][109] = PORTA; _asm(nop); _asm(nop);
	image[linesC][110] = PORTA; _asm(nop); _asm(nop);
	image[linesC][111] = PORTA; _asm(nop); _asm(nop);
	image[linesC][112] = PORTA; _asm(nop); _asm(nop);
	image[linesC][113] = PORTA; _asm(nop); _asm(nop);
	image[linesC][114] = PORTA; _asm(nop); _asm(nop);
	image[linesC][115] = PORTA; _asm(nop); _asm(nop);
	image[linesC][116] = PORTA; _asm(nop); _asm(nop);
	image[linesC][117] = PORTA; _asm(nop); _asm(nop);
	image[linesC][118] = PORTA; _asm(nop); _asm(nop);
	image[linesC][119] = PORTA; _asm(nop); _asm(nop);
}

/**
* 摄像头数据发送
*/
void sendPicture(){
  byte i = 0, j = 0;
  sendSCI('s');
  for(i=0; i < rowNum; ++i){
    for(j=0; j < colNum; ++j){
      sendSCI(image[i][j]);   
    }
  }
}