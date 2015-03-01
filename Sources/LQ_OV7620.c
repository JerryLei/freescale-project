/********************************************
龙丘MC9S12XS128多功能开发板 
Designed by Chiu Sir
E-mail:chiusir@yahoo.cn
软件版本:V2.2
最后更新:2014年1月5日
相关信息参考下列地址:
网站:  http://www.lqist.cn
论坛:  http://smartcar.5d6d.com
淘宝店:http://shop36265907.taobao.com   
------------------------------------
Code Warrior 5.0
Target : MC9S12XS128
Crystal: 16.000Mhz
busclock:32.000MHz
pllclock:64.000MHz 
**********************************************/
#include "main.h"


#define  ROWS   40          //扫描行数
#define  LINES  120         //扫描列数

byte  Line_C=0;
byte  Rows_C=0;
byte  ROW_Space=0;
uchar Line_Cont=0;
byte  Get_Imge_Flog=0;
byte  Image_Data[ROWS][LINES];
/*************************************************************************
*                    北京龙邱智能科技 大家玩开发板           
*
*  函数名称：void LQ_OV7620_Init(void)
*  功能说明：摄像头所用管脚的初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2014年1月5日
*  备    注：
*************************************************************************/
void LQ_OV7620_Init(void)
 {
      DDRA  = 0x00;
      DDRB  = 0xFF;        //
      PORTB = 0xff;
      TIOS  = 0x00;        //场同步的引脚0为输入捕捉
      TSCR2 =0x00;         //div by 1时钟分频
      TCTL3 =0x00;         
      TCTL4 =0x05;         //TI1行同步为上升沿捕捉   TI0场同步为上升沿捕捉 
      TSCR1=0x80;          //时钟打开 
      TIE_C1I= 0x01;      // 关闭场同步输入捕捉中断

 }
/*************************************************************************
*                    北京龙邱智能科技 大家玩开发板           
*
*  函数名称：void SendPicture() 
*  功能说明：摄像头数据发送
*  参数说明：无
*  函数返回：无
*  修改时间：2014年1月5日
*  备    注：
*************************************************************************/
void SendPicture() 
 {
   int i = 0, j = 0;
   SCI_send('S');//发送帧头标志
   for(i=0;i<ROWS;i++) 
   {
     for(j=0;j<LINES;j++)
      {
           
        //if(Image_Data[i][j]<126) 
        //{ 
         SCI_send(Image_Data[i][j]);
        //}      
       
       
      }
     // SCI_send('\r');
      //SCI_send('\n');
   }
  // SCI_send('\r');
   //SCI_send('\n');
 }
 
/*************************************************************************
*                    北京龙邱智能科技 大家玩开发板           
*
*  函数名称：__interrupt 8 void Vsync_INT(void)
*  功能说明：场中断处理函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014年1月5日
*  备    注：
*************************************************************************/
 #pragma CODE_SEG __NEAR_SEG NON_BANKED 

/*备注：进场中断之后需要做的事是
1，关闭场中断，清除场中断标志位
2，打开行中断，清空行计数器
*/
 __interrupt 9 void Vsync_INT(void) 
   {
      
      Line_C    = 0;         //行计数器
      TIE_C1I   = 0x00;      // 关闭场同步输入捕捉中断
      TIE_C0I   = 0x01;      // 关闭场同步输入捕捉中断
      TFLG1_C1F = 0x01;      //清除场同步中断标志 
        
      Rows_C = ++Rows_C;
  }
  
/*************************************************************************
*                    北京龙邱智能科技 大家玩开发板           
*
*  函数名称：__interrupt 9 void CHsync_INT(void) 
*  功能说明：行中断处理函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014年1月5日
*  备    注：
*************************************************************************/
__interrupt 8 void CHsync_INT(void) 
  {
      Line_Cont++;
      if((Line_Cont<50)||(Line_Cont>240))    //
       {
          return;
       }
       
      ROW_Space=3;
      
      if(Line_Cont%ROW_Space==0) 
      {
        Get_Pixel();
        Line_C++;
      }
      
      if(Line_C>=39)
       {
        TIE_C0I   = 0x00;      // 关闭场同步输入捕捉中断
        TIE_C1I   = 0x01;      // 关闭场同步输入捕捉中断
       
         
       }
      TFLG1_C0F = 0x01;   //清除行同步中断标志     
  }
  
#pragma  CODE_SEG DEFAULT 
 
/*************************************************************************
*                    北京龙邱智能科技 大家玩开发板           
*
*  函数名称：void LQ_OV7620_Init(void)
*  功能说明：摄像头所用管脚的初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2014年1月5日
*  备    注：
*************************************************************************/
void Get_Pixel(void)
 {
 
                                        
   Image_Data[Line_C][0]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][1]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][2]   = PORTA;  _asm(nop); _asm(nop); 
   Image_Data[Line_C][3]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][4]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][5]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][6]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][7]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][8]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][9]   = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][10]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][11]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][12]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][13]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][14]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][15]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][16]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][17]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][18]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][19]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][20]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][21]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][22]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][23]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][24]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][25]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][26]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][27]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][28]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][29]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][30]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][31]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][32]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][33]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][34]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][35]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][36]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][37]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][38]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][39]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][40]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][41]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][42]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][43]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][44]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][45]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][46]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][47]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][48]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][49]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][50]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][51]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][52]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][53]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][54]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][55]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][56]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][57]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][58]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][59]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][60]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][61]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][62]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][63]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][64]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][65]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][66]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][67]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][68]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][69]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][70]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][71]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][72]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][73]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][74]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][75]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][76]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][77]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][78]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][79]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][80]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][81]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][82]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][83]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][84]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][85]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][86]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][87]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][88]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][89]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][90]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][91]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][92]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][93]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][94]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][95]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][96]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][97]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][98]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][99]  = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][100] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][101] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][102] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][103] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][104] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][105] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][106] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][107] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][108] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][109] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][110] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][111] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][112] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][113] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][114] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][115] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][116] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][117] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][118] = PORTA;  _asm(nop); _asm(nop);
   Image_Data[Line_C][119] = PORTA; 
   

}

/*************************************************************************
*                    北京龙邱智能科技 大家玩开发板           
*
*  函数名称：void Little_DELAY(uint timer) 
*  功能说明：行中断延时函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014年1月5日
*  备    注：
************************************************************************/
void Little_DELAY(uint timer) 
{
    int i;
    for(i=0;i<timer;i++)
    _asm(nop);
}
