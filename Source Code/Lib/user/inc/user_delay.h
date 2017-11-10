/*****************************************************************************
  *Ten Tep          :     user_delay.h
  *Tom Tat          :     Khai bao cac ham tao delay
  ******************************************************************************/
#include "stm32f10x.h"  // Device header
#include "stm32f10x_rcc.h" 

/*******************************************************************************
Noi Dung    : Khoi tao Systick.
Tham Bien   : SYSCLK: Tan so hoat dong cua he thong.
Tra Ve      : Khong.
********************************************************************************/

void delay_init(uint8_t SYSCLK);

/*******************************************************************************
Noi Dung    : Tao dinh thoi theo don vi ms.
Tham Bien   : nms: Thoi gian can dinh thoi.
Tra Ve      : Khong.
********************************************************************************/

void delay_ms(uint16_t nms);

/*******************************************************************************
Noi Dung    : Tao dinh thoi theo don vi us.
Tham Bien   : nus: Thoi gian can dinh thoi.
Tra Ve      : Khong.
********************************************************************************/

void delay_us(uint32_t nus);

/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/

