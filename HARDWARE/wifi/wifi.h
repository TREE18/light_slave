#ifndef __WIFI_H
#define __WIFI_H

#include "common.h"
#include "string.h"
#include "usart2.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 

void connect_sta(void);
u8 get_rssi(void);
double get_distance(void);
u8 check_state(void);
void distance_judge(u8 distance);
void off_sta(void);
#endif

