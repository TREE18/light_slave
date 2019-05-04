#include "led.h"
//MINI//高电平 灭
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化
// GPIO_SetBits(GPIOC,GPIO_Pin_6);						 //PC.6 输出高 //灯是低电平亮
// GPIO_SetBits(GPIOC,GPIO_Pin_7);						 //PC.6 输出高 //灯是低电平亮
	LED0 = 1;
	LED1 = 1;
}
 
