#ifndef __COMMON_H
#define __COMMON_H

#include "sys.h"
#include "usart2.h"
#include "usart.h"	
#include "delay.h"
#include "string.h"



u8* atk_8266_check_cmd(u8 *str);

u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);

extern const u8* wifista_ssid;		//WIFI STA SSID
//extern const u8* wifista_encryption;//WIFI STA º”√‹∑Ω Ω
extern const u8* wifista_password; 	//WIFI STA √‹¬Î
extern const u8* bssid;
#endif


