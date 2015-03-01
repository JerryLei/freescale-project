/*--------------------------------------
* 串口通信设置
* Jerry Lei
* 2015.3.1
--------------------------------------*/

#include "main.h"

#define BAUD 115200     // 波特率
extern long BUS_CLOCK;


/** 
* SCI 串口申明
*/
void initSCI(){
  SCI0BD = BUS_CLOCK/16/BAUD;  //设置SCI0波特率为9600
  SCI0CR1 = 0x00;              // 7:LOOPS=0 正常模式
                               // 6：SCISWAI=0：在等待模式下允许 SCI
                               // 5：RSRC=0：当 LOOPS=1 时，接收器信号源选择位
                               // 4：M=0：方式选择位 0：1 个起始位，8 个数据位，1 个停止位
                               // 3：WAKE=0：唤醒选择位0：介质空闲唤醒
                               // 2：ILT=0：空闲检测方式选择位0：快速检测
                               // 1：PE=0：奇偶校验允许位0：禁止奇偶校验
                               // 0: PT=0：奇／偶校验选择位（在PE=1时有效）
                               //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI0CR2 = 0x08;              //允许发送数据，禁止中断功能 
                               //7:TIE=0：发送中断允许位 0:禁止
                               //6:TCIE=0：发送结束中断允许位0：禁止
                               //5:RIE=0：接收中断允许位 0：禁止
                               //4:ILIE=0：空闲中断允许位 0:禁止
                               //3:TE=1：发送允许位 1:允许 SCI 发送部分工作，TxD 引脚(PSl／PS3)用于发送
                               //2:RE=0：接收允许位 0:禁止接收
                               //1:RWU=0：接收器唤醒控制位 0：正常模式
                               //0:SBK=0：中止符发送允许位 0： 中止符产生器关闭
}

/** 
* SCI发送一个字节
*/
void sendSCI(unsigned char data){
  while(!SCI0SR1_TDRE);       //等待发送数据寄存器（缓冲器）为空
  SCI0DRL = data;             //把数据放入SCI数据存储器
}

/**
* SCI发送字符串
*/ 
void sendString(unsigned char *str){
   while(str != 0x00){    // 判断字符串是否发送完毕
      sendSCI(*str++);    // 发送字符串
   }
}