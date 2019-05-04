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
	atk_8266_send_cmd("AT+CWMODE_DEF=1","OK",50);		//设置WIFI STA模式
	//atk_8266_send_cmd("AT+RST","OK",20);		
	delay_ms(200);        
	//设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!! 
	sprintf((char*)p,"AT+CWJAP_DEF=\"%s\",\"%s\",\"%s\"",wifista_ssid,wifista_password,bssid);//设置无线参数:ssid,密码
	printf("%d",atk_8266_send_cmd(p,"WIFI GOT IP",100));
//	if(atk_8266_send_cmd(p,"OK",200))zigbee_send_cmd("wifi_bad","0",0);
//	else zigbee_send_cmd("wifi_OK","0",0);
	myfree(p);
	
	printf("connect_sta");
}

//获取rssi
u8 get_rssi()
{
	u8 *p,Rssi;
	atk_8266_send_cmd("AT+CWJAP?","+CWJAP:\"ESP_WIFI\",",50);
	p=atk_8266_check_cmd("-");
	printf("rssi:%s",(p+1));
	Rssi=atoi((p+1));  //将字符串转换成数字
	return Rssi;
}

//通过rssi获取距离
double get_distance(void)
{
	double power;
	double d;
	u8 rssi=get_rssi();
	u8 A=55;  //相距一米时的负rssi值
    u8 n=3;   //环境衰减因子
	
	power=(double)(rssi-A)/(10*n);
	d=(double)pow(10,power);
	//printf("\ndistance:%f",d);
	return d;	
}

//检查esp8266的状态
u8 check_state()
{
	u8 *p,State;
	atk_8266_send_cmd("AT+CIPSTATUS","STATUS:",50);
	p=atk_8266_check_cmd(":");
	printf("State:%s",(p+1));
	State=atoi((p+1)); //将字符串转换成数字
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


