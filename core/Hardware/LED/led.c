/*
�ļ��� led.c
�����ˣ��
����ʱ�䣺2022/3/20
���ܣ�


�޸���־��


�������⣺



*/
#include "delay.h"
#include "led.h"

void LED_Init(void){ //LED�ƵĽӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE|RCC_APB2Periph_AFIO);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//��������ʱ��
		
	
    GPIO_InitStructure.GPIO_Pin = LED; //ѡ��˿ںţ�0~15��all��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(GPIOC, &GPIO_InitStructure);//PB11�˿ڳ�ʼ��
	GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
}



/*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/
