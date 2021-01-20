#include "../YTGLib_Dev/YTGLib_Dev.h"

//��ʼ��IIC�ӿ�
void AT24CXX_Init(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	IIC_Init(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);//IIC��ʼ��
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr,GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{				  
	uint8_t temp=0;		  	    																 
  
	IIC_Start(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);  
	IIC_Send_Byte(0XA0,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);   //����������ַ0XA0,д���� 	   
	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA); 
  IIC_Send_Byte(ReadAddr,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);   //���͵͵�ַ
	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);	    
	IIC_Start(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);  	 	   
	IIC_Send_Byte(0XA1,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);           //�������ģʽ			   
	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);	 
  temp=IIC_Read_Byte(0,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);		   
  IIC_Stop(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);//����һ��ֹͣ����	
//	IIC_Start(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Send_Byte(0xA0,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Send_Byte(ReadAddr,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Start(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Send_Byte(0xA1,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	temp=IIC_Read_Byte(0,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA); //������ַ�е�ֵ
//	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Send_Byte(1,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Stop(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite,GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{				   	  	    																 
	IIC_Start(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);  
	IIC_Send_Byte(0XA0,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);   //����������ַ0XA0,д���� 	 
	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);	   
	IIC_Send_Byte(WriteAddr,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);   //���͵͵�ַ
	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA); 	 										  		   
	IIC_Send_Byte(DataToWrite,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);     //�����ֽ�							   
	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);  		    	   
	IIC_Stop(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);//����һ��ֹͣ���� 
	delay_ms(10);

//	IIC_Start(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Send_Byte(0xA0,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA); //������ַ��0Ϊд���� 
//	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Send_Byte(WriteAddr,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA); //Ҫ��ĵ�ַ
//	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Send_Byte(DataToWrite,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA); //Ҫ�������
//	IIC_Wait_Ack(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	IIC_Stop(GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
//	delay_ms(10);		
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len,GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len,GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
uint8_t AT24CXX_Check(GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(255,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X55,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
	    temp=AT24CXX_ReadOneByte(255,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead,GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite,GPIO_TypeDef* GPIO_SCL, uint16_t GPIO_Pin_SCL, GPIO_TypeDef* GPIO_SDA, uint16_t GPIO_Pin_SDA)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer,GPIO_SCL,GPIO_Pin_SCL,GPIO_SDA,GPIO_Pin_SDA);
		WriteAddr++;
		pBuffer++;
	}
}
