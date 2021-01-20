#include "../YTGLib_Dev/YTGLib_Dev.h"

//IIC��ʼ��
void IIC_Init(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
 
	GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL);
	GPIO_SDA->BSRR |= (1<<GPIO_Pin_SDA);
}

//����IIC��ʼ�ź�
void IIC_Start(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	GPIO_SDA->MODER&=~(3<<(GPIO_Pin_SDA*2));
	GPIO_SDA->MODER|=1<<GPIO_Pin_SDA*2;
	
	GPIO_SDA->BSRR |= (1<<GPIO_Pin_SDA);  	  
	GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL);
	delay_us(4);
 	GPIO_SDA->BSRR |= 1<<(GPIO_Pin_SDA+16);
	delay_us(4);
	GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
}	  
//����IICֹͣ�ź�
void IIC_Stop(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	GPIO_SDA->MODER&=~(3<<(GPIO_Pin_SDA*2));
	GPIO_SDA->MODER|=1<<GPIO_Pin_SDA*2;
	
	GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
	GPIO_SDA->BSRR |= 1<<(GPIO_Pin_SDA+16);
 	delay_us(4);
	GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL);
	GPIO_SDA->BSRR |= (1<<GPIO_Pin_SDA); 
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	uint8_t ucErrTime=0;
	GPIO_SDA->MODER&=~(3<<(GPIO_Pin_SDA*2));
	GPIO_SDA->MODER|=0<<GPIO_Pin_SDA*2; 
	
	GPIO_SDA->BSRR |= (1<<GPIO_Pin_SDA);
	delay_us(1);	   
	GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL);
	delay_us(1);	 
	while(GPIO_SDA->IDR & 1<<GPIO_Pin_SDA) //HAL_GPIO_ReadPin(GPIO_SDA,(uint16_t)0x0001<<GPIO_Pin_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
			return 1;
		}
	}
	GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
	
	GPIO_SDA->MODER&=~(3<<(GPIO_Pin_SDA*2));
	GPIO_SDA->MODER|=1<<GPIO_Pin_SDA*2;
	
	GPIO_SDA->BSRR |= 1<<(GPIO_Pin_SDA+16);
	delay_us(2);
	GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL);
	delay_us(2);
	GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
}
//������ACKӦ��		    
void IIC_NAck(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
	GPIO_SDA->MODER&=~(3<<(GPIO_Pin_SDA*2));
	GPIO_SDA->MODER|=1<<GPIO_Pin_SDA*2;
	
	GPIO_SDA->BSRR |= (1<<GPIO_Pin_SDA);
	delay_us(2);
	GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL);
	delay_us(2);
	GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(uint8_t txd,GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{                        
  uint8_t t; 

	GPIO_SDA->MODER&=~(3<<(GPIO_Pin_SDA*2));
	GPIO_SDA->MODER|=1<<GPIO_Pin_SDA*2;
	
  GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
	
	for(t=0;t<8;t++)
	{              
		if(((txd&0x80)>>7) != 0)
		{
			GPIO_SDA->BSRR |= (1<<GPIO_Pin_SDA);
			
		}else{
			GPIO_SDA->BSRR |= 1<<(GPIO_Pin_SDA+16);
		}

		txd<<=1; 	  
		delay_us(2);
		GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL); 
		delay_us(2); 
		GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16); 	
		delay_us(2);
	}	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte(unsigned char ack, GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	unsigned char i,receive=0;
	GPIO_SDA->MODER&=~(3<<(GPIO_Pin_SDA*2));
	GPIO_SDA->MODER|=0<<GPIO_Pin_SDA*2; 
	for(i=0;i<8;i++ )
	{
		GPIO_SCL->BSRR |= 1<<(GPIO_Pin_SCL+16);
		delay_us(2);
		GPIO_SCL->BSRR |= (1<<GPIO_Pin_SCL); 
		receive<<=1;
		if(GPIO_SDA->IDR & 1<<GPIO_Pin_SDA)receive++;   
		delay_us(1); 
	}					 
	if (!ack)
		IIC_NAck(GPIO_SCL, GPIO_Pin_SCL, GPIO_SDA, GPIO_Pin_SDA);//����nACK
	else
		IIC_Ack(GPIO_SCL, GPIO_Pin_SCL, GPIO_SDA, GPIO_Pin_SDA); //����ACK   
	return receive;
}


