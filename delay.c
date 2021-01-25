#include "../YTGLib_Dev/YTGLib_Dev.h"

//uint32_t fac_us=0;							//us��ʱ������
			   

/**********���������ϵͳ��Ƶ************/
void delay_init()
{
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTickƵ��ΪHCLK
}								    


//��ʱnus
//nusΪҪ��ʱ��us��.	
//nus:0~190887435(���ֵ��2^32/fac_us@fac_us=22.5)	 
//void delay_us(uint32_t nus)
//{		
//	uint32_t ticks;
//	uint32_t told,tnow,tcnt=0;
//	uint32_t reload=SysTick->LOAD;				//LOAD��ֵ	    	 
//	ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
//	told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
//	while(1)
//	{
//		tnow=SysTick->VAL;	
//		if(tnow!=told)
//		{	    
//			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
//			else tcnt+=reload-tnow+told;	    
//			told=tnow;
//			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
//		}  
//	};
//}
//void delay_ms(uint16_t nms)
//{
//	uint32_t i;
//	for(i=0;i<nms;i++) delay_us(1000);
//}

void delay_us(uint32_t usDelay)
{
	uint32_t temp;
	SysTick->LOAD = (HCLKTICK/8)*usDelay;
	SysTick->VAL=0X00;//��ռ�����
	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	do
	{
		temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	SysTick->CTRL=0x00; //�رռ�����
	SysTick->VAL =0X00; //��ռ�����
}

void HAL_Delay(uint32_t Delay)
{
	uint32_t temp;
	SysTick->LOAD = (HCLKTICK/8*1000)*Delay;
	SysTick->VAL=0X00;//��ռ�����
	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	do
	{
		temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	SysTick->CTRL=0x00; //�رռ�����
	SysTick->VAL =0X00; //��ռ�����
}
