#include "user_delay.h"

static u8  fac_us=0;
static u16 fac_ms=0;

/*******************************************************************************
Noi Dung    : Khoi tao Systick.
Tham Bien   : SYSCLK: Tan so hoat dong cua he thong.
Tra Ve      : Khong.
********************************************************************************/

void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}		

/*******************************************************************************
Noi Dung    : Tao dinh thoi theo don vi ms.
Tham Bien   : nms: Thoi gian can dinh thoi.
Tra Ve      : Khong.
********************************************************************************/

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;           
	SysTick->CTRL=0x01 ;         
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); 
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;       	    
}  

/*******************************************************************************
Noi Dung    : Tao dinh thoi theo don vi us.
Tham Bien   : nus: Thoi gian can dinh thoi.
Tra Ve      : Khong.
********************************************************************************/

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;   		 
	SysTick->VAL=0x00;        
	SysTick->CTRL=0x01 ;      	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));   
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;        
}

/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/




































