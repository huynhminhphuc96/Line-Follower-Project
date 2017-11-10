#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "user_delay.h"


/*define*/	
//-----------sensor----------
#define RCC_sensor							RCC_APB2Periph_GPIOB
#define GPIO_port_sensor 				GPIOB
#define GPIO_left_sensor 				GPIO_Pin_12
#define GPIO_between_sensor 		GPIO_Pin_13
#define GPIO_right_sensor 			GPIO_Pin_14
#define GPIO_distance_sensor 			GPIO_Pin_15

//-----------motor----------
#define RCC_motor								RCC_APB2Periph_GPIOA
#define GPIO_port_motor				  GPIOA
#define GPIO_enA 								GPIO_Pin_8
#define GPIO_enB 								GPIO_Pin_9
#define GPIO_in1 								GPIO_Pin_7
#define GPIO_in2 								GPIO_Pin_6
#define GPIO_in3 								GPIO_Pin_4
#define GPIO_in4 								GPIO_Pin_5


/*functions*/
void gpio_config(void);
void read_sensor(void);
void motor_control_not_pwm(void);
void stop(void);
void go_straight_ahead(void);
void turn_left(void);
void turn_right(void);

/*variables*/
uint8_t sensor[4] = {0,0,0,0};
int temp, value;


/*main*/
int main()
{
	SystemInit();
	gpio_config();
	delay_init(72);

	stop();
  value = temp = 4;
	stop();

	while(1)
	{		
		read_sensor();
		
		if(value != temp)
		{
			stop();
			temp = value;
		}
		motor_control_not_pwm();

	}
	return 0;
}


/*functions*/

//------------------------------
void gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//____________OUTPUT____________
	RCC_APB2PeriphClockCmd(RCC_motor, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_in1 | GPIO_in2 | GPIO_in3 | GPIO_in4;	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_port_motor, &GPIO_InitStructure);
	 
	//__________INPUT__________
	RCC_APB2PeriphClockCmd(RCC_sensor, ENABLE);	
	GPIO_InitStructure.GPIO_Pin = GPIO_left_sensor|GPIO_between_sensor|GPIO_right_sensor|GPIO_distance_sensor;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_port_sensor,&GPIO_InitStructure);
	
}

//-----------------------------
void read_sensor(void)
{
	/*IR*/
	sensor[0] = GPIO_ReadInputDataBit(GPIO_port_sensor, GPIO_left_sensor);
	sensor[1] = GPIO_ReadInputDataBit(GPIO_port_sensor, GPIO_between_sensor);
	sensor[2] = GPIO_ReadInputDataBit(GPIO_port_sensor, GPIO_right_sensor);
	sensor[3] = GPIO_ReadInputDataBit(GPIO_port_sensor, GPIO_distance_sensor);
	
	if		 ((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1) && sensor[3] == 1)
		value=2;
	else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1) && sensor[3] == 1)
		value=1;
	else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0) && sensor[3] == 1)
		value=0;
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0) && sensor[3] == 1)
		value=-1;
	else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0) && sensor[3] == 1)
		value=-2;
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0) && sensor[3] == 1)
	{
		if(value == -2 || value == 2) value = value;
		else value = 3;
	}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1) && sensor[3] == 1)
	{
		if(value == -2 || value == 2 ) value = value;
		else value = 3;
	}
	else if(sensor[3] == 0)
		value = 4;

}

void motor_control_not_pwm(void)
{
	/*IR*/
	if(value == 3)	
		turn_left();
	else if (value == 2 || value == 1)
		turn_right();
	else if (value == -2 || value == -1)
		turn_left();
	else if (value == 0)
		go_straight_ahead();
	else
		stop();
}

void stop(void)
{
	GPIO_WriteBit(GPIO_port_motor, GPIO_in1, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in2, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in3, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in4, Bit_SET);
}
void go_straight_ahead(void)
{
	GPIO_WriteBit(GPIO_port_motor, GPIO_in1, Bit_RESET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in2, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in3, Bit_RESET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in4, Bit_SET);
}
void turn_left(void)
{
	GPIO_WriteBit(GPIO_port_motor, GPIO_in1, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in2, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in3, Bit_RESET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in4, Bit_SET);
}
void turn_right(void)
{
	GPIO_WriteBit(GPIO_port_motor, GPIO_in1, Bit_RESET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in2, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in3, Bit_SET);
	GPIO_WriteBit(GPIO_port_motor, GPIO_in4, Bit_SET);
}
//---------------------------------------------------------
