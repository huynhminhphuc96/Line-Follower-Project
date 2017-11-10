/******************** (C) 1209 Lab **************************
 * �ļ���  : HC-SR04.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Mini STM32������  STM32F103RBT6
 * Ӳ�����ӣ�------------------
 *          | PC8  - TRIG      |
 *          | PC7  - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��Lee 
*********************************************************************************/

#include "HC-SR04.h"
//#include "timers.h"
#include "delay.h"

  
#define UltrasonicWave_DISTANCE_MAX  350

/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
    
    RCC_APB2PeriphClockCmd(HCSR04_TRIG_RCC_Periph|HCSR04_ECHO_RCC_Periph|RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG_PIN;			//PC8��TRIG
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//��Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
    GPIO_Init(HCSR04_TRIG_PORT, &GPIO_InitStructure);	     //��ʼ������GPIO 

    GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO_PIN;				     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //��Ϊ����
    GPIO_Init(HCSR04_ECHO_PORT,&GPIO_InitStructure);	//��ʼ��GPIOA
    
    TIM4_Cap_Channel_1_Init(0xFFFF,720-1);
}



/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(HCSR04_TRIG_PORT,HCSR04_TRIG_PIN); 		  //��>10US�ĸߵ�ƽ
  Delay_NOP_us(20);		                      //��ʱ20US
  GPIO_ResetBits(HCSR04_TRIG_PORT,HCSR04_TRIG_PIN); 
}


uint16_t UltrasonicWave_GetDistance(void)
{
    uint16_t distance;
    distance = Channel_1_UpTime * 17/100;
    
    return (distance < UltrasonicWave_DISTANCE_MAX) ? distance : 0;
}


/******************* (C) 1209 Lab *****END OF FILE************/
