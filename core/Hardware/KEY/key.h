#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY_PORT	GPIOB
#define KEY1		GPIO_Pin_12//PA9
#define KEY2		GPIO_Pin_13	//PA10
#define KEY3    GPIO_Pin_14//PA12
#define KEY4    GPIO_Pin_15//PB5

#define ASR_PORT GPIOB

#define ASR1    GPIO_Pin_3//PB3 ���		
#define ASR2    GPIO_Pin_4//PB4 ��������
#define ASR3    GPIO_Pin_5//PB5 ��С����
#define ASR4    GPIO_Pin_6//PB6 ��ʱ�ر�
#define ASR5    GPIO_Pin_7//PB7 һ���Ӻ�ر�
#define ASR6    GPIO_Pin_8//PB8 ����Ӻ�ر�
#define ASR7    GPIO_Pin_9//PB9 �ص�

void KEY_Init(void);//�ĸ�������ʼ��

u8 Key_Read(void);
void ASR_Init(void);//����ʶ��ģ��ӿڳ�ʼ��
u8 Asr_Read(void);		 				    
#endif
