#ifndef __ENCODER_H
#define __ENCODER_H	 
#include "sys.h"
#include "delay.h"

#define ENCODER_PORT_B	GPIOB	//��ת����������
#define ENCODER_D	GPIO_Pin_0	//PB0


#define ENCODER_L	GPIO_Pin_1	//PB1
#define ENCODER_PORT_A  GPIOA
#define ENCODER_R	GPIO_Pin_7	//PA7


void ENCODER_Init(void);//��ʼ��
u8 ENCODER_READ(void);


		 				    
#endif
