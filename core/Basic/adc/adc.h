#ifndef __ADC_H
#define __ADC_H 			   
#include "sys.h"


#define ADC1_DR_Address    ((uint32_t)0x4001244C) //ADC1

#define ADCPORT		GPIOA	//����ADC�ӿ�
#define ADC_CH0		GPIO_Pin_0	//����ADC�ӿ� ��ѹ��λ��
#define ADC_CH1		GPIO_Pin_1	//����ADC�ӿ� ��������
#define ADC_CH6		GPIO_Pin_6	//����ADC�ӿ� ҡ��X��
#define ADC_CH4		GPIO_Pin_4	//����ADC�ӿ� ҡ��Y��


extern vu16 ADC_DMA_IN[4]; //声明外部变量


void ADC_DMA_Init(void);//DAM��ʼ������
void ADC_GPIO_Init(void);//GPIO�˿ڳ�ʼ������
void ADC_Configuration(void);/*ADCʹ��ֱ�ӵ��ú������Ѱ����Ϸ�����*/

#endif





























