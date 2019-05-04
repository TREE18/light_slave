#include "myconf.h"

void Red_Deal()
{
	if(1==red_flag && 1==GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2) && 0==red_temp)
	{
		red_temp = 1;
		if(1 == red_temp)zigbee_send_cmd("open_red","0",0);
	}
	else if(1==red_temp && 0==GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)){
		zigbee_send_cmd("down_red","0",0);
		red_temp=0;
	}
}

void Posture_Deal()
{
		if(posture_flag == 1)
		 {	  
				mpu_dmp_get_data(&pitch, &roll, &yaw);
			 
				key = KEY_Scan(0);
				if(key == KEY0_PRES)
				{//按下按键后才记录端正的姿态
				
					posture_key = 1;

					cmd_temp = 3;//灯闪烁
					
					if(mpu_dmp_get_data(&pitch, &roll, &yaw) == 0)
					{
							First_Posture[0] = pitch;
							First_Posture[1] = roll;
							First_Posture[2] = yaw;
							printf("x=%.2f.y=%.2f.z=%.2f\n\r", pitch, roll, yaw);
					}
					
					printf("over");
				}
					
			if(posture_key == 1)Judge_Pesture(&p, &y, &r);//检测是否姿势不端 p y r 为标准差距
		}
}

void Homework_Deal()
{
		if(homework_flag==1)		
		{
		   distance_judge(distancevalue);
//			printf("distancevalue:%d\r\n",distancevalue);
//			delay_ms(500);
		}
		
}

