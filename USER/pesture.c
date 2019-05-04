#include "pesture.h"
#include "usart3.h"
#include "mpu6050.h"
#include "key.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "inv_mpu.h"
#include "usart.h"
#include "timer.h"

extern char posture_temp,key,posture_key;
extern u8 Flag_firstRcord;
extern float pitch,roll,yaw; 		//欧拉角
extern float First_Posture[3];

char time_flag=0;
void Judge_Pesture(float *p, float *y, float *r)
{
	if(
		((fabs(pitch-First_Posture[0])>(*p))||
		(fabs(roll-First_Posture[1])>(*r))||
		(fabs(yaw-First_Posture[2])>(*y)))//&&(0 == posture_temp)
	  )
	{
		if(time_flag==0)
		{
			zigbee_send_cmd("posture_bad","0",0);
			time_flag=1;//
			TIM_Cmd(TIM3, ENABLE);
		}
		
		printf("bad");
		posture_temp=1;
	}
	else if(!((fabs(pitch-First_Posture[0])>(*p))||
		(fabs(roll-First_Posture[1])>(*r))||
		(fabs(yaw-First_Posture[2])>(*y))))
		{
			
			if(time_flag==0)
			{
				zigbee_send_cmd("posture_good","0",0);
				time_flag=1;
				TIM_Cmd(TIM3, ENABLE);
			}
//			if(posture_temp == 1)
//			{
//				zigbee_send_cmd("posture_good","0",0);
//			}
			posture_temp = 0;//reflash
		}
}


//		fabs(pitch-First_Posture[0])>fabs(First_Posture[0]*(*p))||
//		fabs(roll-First_Posture[2])>fabs(First_Posture[2]*(*r))||
//		fabs(yaw-First_Posture[1])>fabs(First_Posture[1]*(*y))	


void Frist_Pesture_key(void )
{
//封装放在这里储出错  在main中不报错
}
















