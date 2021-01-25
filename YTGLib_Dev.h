#ifndef _YTGLib_Dev_H
#define _YTGLib_Dev_H  


/*********************ѡ����Ҫ������ģ��***********************/

#define OLED_INIT_IIC1		//��ʼ��OLED,��ѡ��ΪIIC1����(Ӳ��iic)
#define DELAY_US  				//��ʼ��΢����ʱ
#define MYIIC							//��ʼ��ģ��IIC
#define MPU6050						//��ʼ��MPU6050

/**************************************************************/


#ifdef STM32F407xx
#include "stm32f4xx_hal.h"
#define HCLKTICK 84 
#elif STM32F103xx
#include "stm32f1xx_hal.h"
#define HCLKTICK 72 
#elif STM32H7xx
#include "stm32h7xx_hal.h"
#endif

#ifdef DELAY_US
void delay_init(void);
void delay_us(uint32_t usDelay);
void HAL_Delay(uint32_t Delay);
#endif

#ifdef OLED_INIT_IIC1
#include "i2c.h"

#define IIC_ADRESS &hi2c1
#define OLED0561_ADD	0x78  // OLED��I2C��ַ����ֹ�޸ģ�
#define COM				0x00  // OLED ָ���ֹ�޸ģ�
#define DAT 			0x40  // OLED ���ݣ���ֹ�޸ģ�
void WriteCmd(unsigned char I2C_Command);//д����
void WriteDat(unsigned char I2C_Data);//д����
void OLED_Init(void);//��ʼ��
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);//ȫ�����
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);//��ʾ�ַ���
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);//��ʾ����
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//��ʾͼƬ

void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
uint32_t oled_pow(uint8_t m,uint8_t n);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2);//size2(16|12)
#elif OLED_INIT_IIC2
#include "i2c.h"

#define IIC_ADRESS &hi2c2
#define OLED0561_ADD	0x78  // OLED��I2C��ַ����ֹ�޸ģ�
#define COM				0x00  // OLED ָ���ֹ�޸ģ�
#define DAT 			0x40  // OLED ���ݣ���ֹ�޸ģ�
void WriteCmd(unsigned char I2C_Command);//д����
void WriteDat(unsigned char I2C_Data);//д����
void OLED_Init(void);//��ʼ��
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);//ȫ�����
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);//��ʾ�ַ���
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);//��ʾ����
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//��ʾͼƬ

void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
uint32_t oled_pow(uint8_t m,uint8_t n);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2);//size2(16|12)
#endif

/*********************************************************************/
/*						����Ҫ��ʼ��һ��	
�磺IIC_Init(GPIOB,8,GPIOB,9); //IIC��ʼ��,GPIOB8��ΪSCL,GPIOB9��ΪSDA
		IIC_Start();//����IIC��ʼ�ź�											 
		mpu_dmp_get_data(&pitch,&roll,&yaw);//�õ�MPU6050ŷ����					 */
/*********************************************************************/

#ifdef MYIIC

extern GPIO_TypeDef* GPIO_SCL;
extern uint16_t GPIO_Pin_SCL;
extern GPIO_TypeDef* GPIO_SDA;
extern uint16_t GPIO_Pin_SDA;

void IIC_Init(GPIO_TypeDef* GPIO_SCL_Init, uint16_t GPIO_Pin_SCL_Init, GPIO_TypeDef* GPIO_SDA_Init, uint16_t GPIO_Pin_SDA_Init);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//ָ����ַд��һ���ֽ�
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//ָ����ַ��ʼ��ȡָ����������
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

uint8_t AT24CXX_Check(void);  //�������
void AT24CXX_Init(GPIO_TypeDef* GPIO_SCL_Init, uint16_t GPIO_Pin_SCL_Init, GPIO_TypeDef* GPIO_SDA_Init, uint16_t GPIO_Pin_SDA_Init); //��ʼ��IIC
#endif

#ifdef MPU6050

/*********************************************************************/
/*				����Ҫ��ʼ��һ�Σ���ʹ��������ǰ����Ҫ��ʼ��
			�������ǳ�ʼ���󣬿�ֱ�ӵ���mpu_dmp_init()����DMP��ʼ��
�磺MPU_Init(GPIOB,8,GPIOB,9); //�����ǳ�ʼ����PB8ΪSCL��PB9ΪSDA		*/
/*********************************************************************/

#include "../YTGLib_Dev/eMPL/inv_mpu.h"
#include "../YTGLib_Dev/eMPL/inv_mpu_dmp_motion_driver.h" 

uint8_t MPU_Init(GPIO_TypeDef* GPIO_SCL_Init, uint16_t GPIO_Pin_SCL_Init, GPIO_TypeDef* GPIO_SDA_Init, uint16_t GPIO_Pin_SDA_Init); 								//��ʼ��MPU6050
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);//IIC����д
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf); //IIC������ 
uint8_t MPU_Write_Byte(uint8_t reg,uint8_t data);				//IICдһ���ֽ�
uint8_t MPU_Read_Byte(uint8_t reg);						//IIC��һ���ֽ�

uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr);
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr);
uint8_t MPU_Set_LPF(uint16_t lpf);
uint8_t MPU_Set_Rate(uint16_t rate);
uint8_t MPU_Set_Fifo(uint8_t sens);


short MPU_Get_Temperature(void);			//�õ�MPU6050�¶�
uint8_t MPU_Get_Gyroscope(short *gx,short *gy,short *gz);	//�õ�������ֵ
uint8_t MPU_Get_Accelerometer(short *ax,short *ay,short *az);	//�õ����ٶ�ֵ
#endif

#endif
