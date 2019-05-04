#include "wifi.h"
#include "stdlib.h"
#include "led.h"
#include "math.h"
#include "string.h"
#include "common.h"
#include "usart2.h"
#include "malloc.h"
#include "usart3.h"

extern char homework_temp;


void off_sta()
{
	atk_8266_send_cmd("AT+CWQAP","OK",10);
}

//void Power_frist_off_sta()
//{
//	
//}

void connect_sta()
{
	u8 *p;
	p=mymalloc(32);
	atk_8266_send_cmd("AT+CWMODE_DEF=1","OK",50);		//����WIFI STAģʽ
	//atk_8266_send_cmd("AT+RST","OK",20);		
	delay_ms(200);        
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWJAP_DEF=\"%s\",\"%s\",\"%s\"",wifista_ssid,wifista_password,bssid);//�������߲���:ssid,����
	printf("%d",atk_8266_send_cmd(p,"WIFI GOT IP",100));
//	if(atk_8266_send_cmd(p,"OK",200))zigbee_send_cmd("wifi_bad","0",0);
//	else zigbee_send_cmd("wifi_OK","0",0);
	myfree(p);
	
	printf("connect_sta");
}

//��ȡrssi
u8 get_rssi()
{
	u8 *p,Rssi;
	atk_8266_send_cmd("AT+CWJAP?","+CWJAP:\"ESP_WIFI\",",50);
	p=atk_8266_check_cmd("-");
	printf("rssi:%s",(p+1));
	Rssi=atoi((p+1));  //���ַ���ת��������
	return Rssi;
}

//ͨ��rssi��ȡ����
double get_distance(void)
{
	double power;
	double d;
	u8 rssi=get_rssi();
	u8 A=55;  //���һ��ʱ�ĸ�rssiֵ
    u8 n=3;   //����˥������
	
	power=(double)(rssi-A)/(10*n);
	d=(double)pow(10,power);
	//printf("\ndistance:%f",d);
	return d;	
}

//���esp8266��״̬
u8 check_state()
{
	u8 *p,State;
	atk_8266_send_cmd("AT+CIPSTATUS","STATUS:",50);
	p=atk_8266_check_cmd(":");
	printf("State:%s",(p+1));
	State=atoi((p+1)); //���ַ���ת��������
	return State;
}

void distance_judge(u8 distance)
{
	double d=0;
	LED1=0;
	
	d=get_distance();
	
	printf("%f",get_distance());

	if(d>=distance&&homework_temp==0)
	{
		LED0=0; 
		printf("-----------------------come on--------------------");
		zigbee_send_cmd("homework_bad","0",0);
		homework_temp=1;
	}
	else if(d<distance&&homework_temp==1){
		LED0=1;
		homework_temp=0;
		zigbee_send_cmd("homework_good","0",0);
	}

}


