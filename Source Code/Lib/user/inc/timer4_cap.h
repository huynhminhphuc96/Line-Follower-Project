#ifndef __TIMER4_CAP_H
#define __TIMER4_CAP_H
#include "sys.h"
#include <stdio.h>
#include "NVIC_CONFIG.H"

extern uint32_t Channel_1_UpTime;	//�����ܸߵ�ƽ��ʱ��

void TIM4_Cap_Channel_1_Init(u16 arr, u16 psc);

#endif
