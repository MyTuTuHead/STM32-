#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY_PORT	GPIOB
#define KEY1		GPIO_Pin_12//PA9
#define KEY2		GPIO_Pin_13	//PA10
#define KEY3    GPIO_Pin_14//PA12
#define KEY4    GPIO_Pin_15//PB5

#define ASR_PORT GPIOB

#define ASR1    GPIO_Pin_3//PB3 打灯		
#define ASR2    GPIO_Pin_4//PB4 增大亮度
#define ASR3    GPIO_Pin_5//PB5 减小亮度
#define ASR4    GPIO_Pin_6//PB6 延时关闭
#define ASR5    GPIO_Pin_7//PB7 一分钟后关闭
#define ASR6    GPIO_Pin_8//PB8 五分钟后关闭
#define ASR7    GPIO_Pin_9//PB9 关灯

void KEY_Init(void);//四个按键初始化

u8 Key_Read(void);
void ASR_Init(void);//语音识别模块接口初始化
u8 Asr_Read(void);		 				    
#endif
