#ifndef _MYCONF_
#define _MYCONF_
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "stdio.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include <math.h>
#include "pesture.h"
#include "usart2.h"
#include "wifi.h"
#include "usart3.h"
#include "exti.h"
#include <stdlib.h>
#include "timer.h"

//#define ss 2
#define HOMEWORK_SW 0
//#define aa(bb) if(bb){printf("22");break;}

extern float p,y,r,posvalue;//各种姿态的差 //app传来的角度值
extern char cmd,red_temp,posture_temp,homework_temp;
extern char cmd_temp;
extern float pitch,roll,yaw; 		//欧拉角
extern float First_Posture[3];
extern char posture_flag,key,posture_key,homework_flag;
extern u8 distancevalue;
extern char red_flag;

void Red_Deal(void);
void Homework_Deal(void);
void Posture_Deal(void);

#endif

