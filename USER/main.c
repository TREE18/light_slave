#include "myconf.h"
//局部变量不能有extren声明

/**  
2019-3-4:null

**/
extern u8 USART_RX_BUF[USART_REC_LEN]; 
extern char red_flag;

float p=80,y=80,r=80,posvalue=0;//各种姿态的差 //app传来的角度值
char cmd=0,red_temp=0,posture_temp=0,homework_temp=0;
char cmd_temp = 0;
float pitch,roll,yaw; 		//欧拉角
float First_Posture[3]={0};
char posture_flag=0,key = 0,posture_key=0,homework_flag=0;
u8 distancevalue=2;



 int main(void)
 {	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	delay_init();	//延时初始化 
	uart_init(115200);	 	//串口初始化为115200
	USART2_Init(115200);//usart2 初始化
	usart3_init(115200);
//----------------------------------------------------------------------//
	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键  
	MPU_Init();
	LED0 = 1;
	LED1 = 1;
//---------------------------------------------------------------------//
	TIM3_Int_Init(999,7199);
	TIM2_Int_Init(999,7199);
//	
	printf("slave is inited\n");
	
#if 1
	while(1)
	{	
		cmd=zigbee_check_cmd("night_on","night_off","posture_on","posture_off","homework_on","homework_off","pos1:","pos2:","pos3:","dist:");
		if(cmd)
		{
			cmd_temp = cmd;//blink
		//------------------------------------------//
			if(1==cmd)
			{
				red_flag = 1;
				red_Init();	
			}
			else if(2 == cmd)red_flag = 0;
		//------------------------------------------//	
			if(3==cmd)
			{
					posture_temp = 0;//防止多次播报
					posture_flag = 1;
					printf("MPU_Init:%d", MPU_Init());//返回值:0,成功
					if(!mpu_dmp_init())
					{
						zigbee_send_cmd("posture_OK","0",0);
						printf("mpu_dmp_init:OK");
						cmd_temp = 3;//light blink
					}
					TIM_Cmd(TIM3, ENABLE);   
			}
			else if(4==cmd)
			{
				posture_flag = 0;
				posture_key = 0;
			}
		//------------------------------------------//		
		#if HOMEWORK_SW	
			if(5==cmd){	
				homework_temp=0;
				homework_flag=1;
				connect_sta();
			}
			else if(6==cmd){
				homework_flag=0;
				off_sta();}
		#endif
		}
		//--------------------------------------//
		if(7==cmd){p = posvalue;printf("posvaluep==%f\r\n",p); zigbee_send_cmd("pos1:rev","0",0);}
		else if(8==cmd){y = posvalue;printf("posvaluey==%f\r\n",y); zigbee_send_cmd("pos2:rev","0",0);}
		else if(9==cmd){r = posvalue;printf("posvaluer==%f\r\n",r); zigbee_send_cmd("pos3:rev","0",0);}
		//-------------------------------------------------------------------------------------//red
		Red_Deal();	
		//-------------------------------------------------------------------------------------//posture
		Posture_Deal();
		//-------------------------------------------------------------------------------------//
		#if HOMEWORK_SW 
			Homework_Deal();
		#endif
		//-------------------------------------------------------------------------------------//

  }
	#endif

}




