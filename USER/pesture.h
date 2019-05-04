#ifndef __PESTURE_H
#define __PESTURE_H
#include <math.h>
#include "mpu6050.h"
#include "stdio.h"
#include "usart.h"
#include <stdlib.h>


void Judge_Pesture(float *p,float *y,float *r);
void Frist_Pesture_key(void );
#endif

