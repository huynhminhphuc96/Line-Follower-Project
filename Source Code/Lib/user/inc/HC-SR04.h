#ifndef __HCSR04_H
#define	__HCSR04_H
#include "stm32f10x.h"
#include <stdio.h>
#include <stdbool.h>
#include "timer4_cap.h"

#define	HCSR04_TRIG_PORT        GPIOB		    //TRIG       
#define	HCSR04_TRIG_PIN         GPIO_Pin_0     //TRIG  
#define	HCSR04_TRIG_RCC_Periph  RCC_APB2Periph_GPIOB

#define	HCSR04_ECHO_PORT        GPIOB		    //ECHO 
#define	HCSR04_ECHO_PIN         GPIO_Pin_1	    //ECHO 
#define	HCSR04_ECHO_RCC_Periph  RCC_APB2Periph_GPIOB


void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave_StartMeasure(void);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
uint16_t UltrasonicWave_GetDistance(void);

#endif /* __UltrasonicWave_H */

