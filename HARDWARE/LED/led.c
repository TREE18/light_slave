#include "led.h"
//MINI//�ߵ�ƽ ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��
// GPIO_SetBits(GPIOC,GPIO_Pin_6);						 //PC.6 ����� //���ǵ͵�ƽ��
// GPIO_SetBits(GPIOC,GPIO_Pin_7);						 //PC.6 ����� //���ǵ͵�ƽ��
	LED0 = 1;
	LED1 = 1;
}
 
