#ifndef __BUZZER_H
#define __BUZZER_H	 
#include "sys.h"
#include "key.h"

#define BUZZERPORT	GPIOB	//����IO�ӿ�
#define BUZZER	GPIO_Pin_10	//����IO�ӿ�



void BUZZER_Init(void);//��ʼ��
void BUZZER_BEEP1(void);//��һ��
void MIDI_PLAY(void);
		 				    
#endif
