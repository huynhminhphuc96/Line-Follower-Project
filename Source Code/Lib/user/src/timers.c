#include "timers.h"

uint32_t TM5_CH1_CAPTURE_STA = 0;//8λ0x00~0x80
uint32_t TM5_CH1_CAPTURE_VAL;  //����ߵ�ƽ��ʱ������Ĵ���


//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//autoReload���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3
void Timer2_Init(u16 autoReload,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = autoReload; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���			 
}



void Timer5_Init(u16 autoReload,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
    
    TIM_TimeBaseStructure.TIM_Period = autoReload;              
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, & TIM_TimeBaseStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;     //ͨ��1
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;   //�����ز���
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  //ӳ�䵽TI1
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;  //����Ƶ
    TIM_ICInitStructure.TIM_ICFilter = 0x00;                //���˲�
    TIM_ICInit(TIM5, &TIM_ICInitStructure);    
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                               
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&NVIC_InitStructure);    
    
    TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE );
    TIM_Cmd(TIM5, ENABLE);
}






void TIM2_IRQHandler(void)   //TIM2�ж�
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
    }
}


void TIM5_IRQHandler(void)
{
    if((TM5_CH1_CAPTURE_STA & 0x80) == 0 )  //δ�ɹ�����0x80�������
    {
        if(TIM_GetITStatus(TIM5, TIM_IT_Update) == SET)  //���ݸ����жϲ���
        {
            if(TM5_CH1_CAPTURE_STA & 0x40)     //�Ѿ����񵽸ߵ�ƽ
            {
                if((TM5_CH1_CAPTURE_STA & 0x3f)==0x3f)   //-���
                {
                    TM5_CH1_CAPTURE_STA |= 0x80;  //ǿ�Ʋ���ɹ�
                    TM5_CH1_CAPTURE_VAL = 0xffff;  //��ʱ�ļ���ֵ
                }
                else
                {
                    TM5_CH1_CAPTURE_STA++; 
                }
            
            }
        }
        if(TIM_GetITStatus(TIM5, TIM_IT_CC1) == SET)//��������
        {
            if(TM5_CH1_CAPTURE_STA & 0x40)  //�ɹ�����һ���½��أ������ǵ�һ�β���
            {
            TM5_CH1_CAPTURE_STA |= 0x80;  //����ɹ�
            TM5_CH1_CAPTURE_VAL = TIM_GetCapture1(TIM5);//��ȡ����ֵ
            TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);//Ҫ����Ϊ�����أ��ȴ��½��ص�����
            }
            else  //��һ�β���
            {
                TM5_CH1_CAPTURE_STA = 0;
                TM5_CH1_CAPTURE_VAL = 0;
                TIM_SetCounter(TIM5, 0);  //��û�ȵ��½�����ʱ�����еĶ�����
                TM5_CH1_CAPTURE_STA |= 0x40;
                TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);//Ҫ���ó��½��أ��ȵ������ص�����
            }   
        }
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update);
}









