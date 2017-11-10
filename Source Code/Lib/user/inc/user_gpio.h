/*****************************************************************************
  ******************************************************************************
  * Chu Y:
  *		- GPIO_Mode: OUTPUT
  *			GPIO_Mode_Out_PP		--> Output Push Pull
  *			GPIO_Mode_Out_OD		--> Output Open Drain
  *			GPIO_Mode_AF_OD			--> Alternate Function Open Drain
  *			GPIO_Mode_AF_PP			--> Alternate Function Push Pull
  *		- GPIO_Mode: INPUT
  *			GPIO_Mode_AIN			--> Input Analog
  *			GPIO_Mode_IN_FLOATING	--> Input Floating
  *			GPIO_Mode_IPD			--> Input Pull Down
  *			GPIO_Mode_IPU			--> Input Pull Up
  *		- Neu su dung Alternate Function(USART, TIMER, I2C,SPI...) ta phai enable clock cho AFIO:
  *			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  *			Vi Du: Ta cau hinh GPIO su dung USART1
  *				- Enable clock GPIOA	: 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  *				- Enable clock AFIO		:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  *				- Cau hinh PIN TX		:	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         		
  *											GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  *											GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  *											GPIO_Init(GPIOA, &GPIO_InitStructure);
  *				- Cau hinh PIN RX		:	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  *											GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  *											GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  *											GPIO_Init(GPIOA, &GPIO_InitStructure);			
  ******************************************************************************
**/	
/*******************************************************************************
Noi Dung    : Cau hinh GPIO.
Tham Bien   : Khong.
Tra Ve      : Khong.
********************************************************************************/
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"  


void GPIO_Configuration(void);
void GPIO_C_Config(void);

/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/
