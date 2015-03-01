 /*--------------------------------------
* 头文件与系统设置
* Jerry Lei
* 2015.3.1
--------------------------------------*/

#ifndef _MAIN_H
#define _MAIN_H
#include <hidef.h>           /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include <math.h>
#include <stdio.h>

#include "setBus.h"
#include "sci.h"
#include "ov7620.h"


#define STEER_CENTER	3000 // 舵机中间值
#define STEER_LEFT 		2600 // 舵机左转最大值
#define STEER_RIGHT		3400 // 舵机右转最大值	

#pragma LINK_INFO DERIVATIVE "MC9S12XS128"	

#endif