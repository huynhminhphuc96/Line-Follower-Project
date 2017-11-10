#include "timer4_cap.h"
#include "stm32f10x_tim.h"

uint8_t  TIM4CH1_CAPTURE_STA = 0;	//ͨ��1���벶���־������λ�������־����6λ�������־		
uint16_t TIM4CH1_CAPTURE_UPVAL;
uint16_t TIM4CH1_CAPTURE_DOWNVAL;


uint32_t Channel_1_UpTime = 0;	//�����ܸߵ�ƽ��ʱ��



//��ʱ��4ͨ��1���벶������

TIM_ICInitTypeDef TIM4_ICInitStructure;

void TIM4_Cap_Channel_1_Init(uint16_t arr, uint16_t psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM4ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  //PB6���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PB6 ���� 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//PB6  ����

	//��ʼ����ʱ��4 TIM4���ò���������Ҫ��ΪPWM������� 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM4���벶����� ͨ��1
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x0F;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//�жϷ����ʼ��
    NVIC_IRQChannel_Configuration_Set(TIM4_IRQn, 0, 0, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC1,ENABLE);   //����������жϣ�����CC1IE,CC2IE,CC3IE,CC4IE�����ж�	

	TIM_Cmd(TIM4, ENABLE); 		//ʹ�ܶ�ʱ��4

}

//��ʱ��4�жϷ������,��CH1��Ϊ������ת����ͨ�� ��PB6�˿�
void TIM4_IRQHandler(void)
{
	if ((TIM4CH1_CAPTURE_STA & 0x80) == 0) 		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); 		//����жϱ�־λ
			if (TIM4CH1_CAPTURE_STA & 0X40)		//����һ���½���
			{
                Channel_1_UpTime = 0;
				TIM4CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM4);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM4CH1_CAPTURE_DOWNVAL > TIM4CH1_CAPTURE_UPVAL)/* �����������ʼֵ����ĩβֵ��˵������������� �����ڲ�����*/
				{
					Channel_1_UpTime = TIM4CH1_CAPTURE_DOWNVAL - TIM4CH1_CAPTURE_UPVAL;		//�õ��ܵĸߵ�ƽ��ʱ��
				}
				TIM4CH1_CAPTURE_STA = 0;//�����־λ���㣬��һ������Ҫ��
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM4CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM4);		//��ȡ����������
				TIM4CH1_CAPTURE_STA |= 0x40;		//����Ѳ���������
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}
}
