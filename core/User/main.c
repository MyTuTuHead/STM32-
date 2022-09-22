/*
�ļ�����main
�����ˣ�MiaoA
����ʱ�䣺2022/4/17
���ܣ�


ռ����Դ:



�޸���־��


�������⣺


*/

#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "oled0561.h"
#include "usart.h"
#include "flash.h"
#include "pwm.h"



int main (void){//������
	u8 asr = 0;
	u8 key = 0;
	u32 light = 100;//�ƹ����� ֵԽ��Խ��  0-100
	u32 sys_time = 0;
	u32 time_count = 0;
	u8 delay_led = 0;

	delay_ms(100); //�ϵ�ʱ�ȴ�������������,��Ҫ��ʱ
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ��
		
	LED_Init();//LED_init
	
	KEY_Init();//����1,2,3,4��ʼ��

	ASR_Init();//ASR�ӿڳ�ʼ��

	USART1_Init(115200);

	TIM3_PWM_Init(999,8);//PWM��ʼ�� 50HZ

	printf("MiaoA");
			
	while(1){
		
		asr = Asr_Read();//��ȡ����ʶ����
		key = Key_Read();//��ȡ��������

//		if(asr != 0)//����ʹ��
//			printf("asr:%d		",asr);

		if(asr == 1 || led_flag == 1 || key == 1){//����
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));//�򿪰��صƹ�
			
			printf("LED ON");
			light = 50;
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 7 || led_flag == 2 || key == 2){//�ص�
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));//�رհ��صƹ�
			light = 100;
			printf("LED OFF");
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 2 || led_flag == 3 || key == 3){//��������
			printf("Light up");
			if(light > 10)
				light -= 10;
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 3 || led_flag == 4 || key == 4){//��С����
			if(light < 90)
				light += 10;
			printf("Light down");
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 4 || led_flag == 5){//��ʱ�ر�
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));
			printf("Delay off");
			light = 50;
			delay_led = 1;
			sys_time = 0;
			time_count = 0;
			led_flag = 0;
		}

		if(asr == 5 || led_flag == 6){//һ���Ӻ�ر�
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));
			printf("Close in a minute");
			light = 50;
			delay_led = 1;
			sys_time = 0;
			time_count = 0;
			led_flag = 0;
		}

		if(asr == 6 || led_flag == 7){//����Ӻ�ر�
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
			delay_ms(500);
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));
			printf("Close in five minutes");
			light = 50;
			delay_led = 2;
			sys_time = 0;
			time_count = 0;
			led_flag = 0;
		}
		
		if(delay_led == 1){
			if(sys_time >= 1500){
				time_count++;
				sys_time = 0;
			}
			else
				sys_time++;
			if(time_count > 1500){//������ʱ�رյ�ʱ�����
				GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
				time_count = 0;
				sys_time = 0;
				delay_led = 0;
				light = 100;
			}
		}

		if(delay_led == 2){
			if(sys_time >= 1500){
				sys_time = 0;
				time_count++;
			}
			else
				sys_time++;
			if(time_count > 5000){//������ʱ�رյ�ʱ�����
				GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
				time_count = 0;
				sys_time = 0;
				delay_led = 0;
				light = 100;
			}
		}

		TIM_SetCompare3(TIM3,light * 10);//��������
	}
}
/*

u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED����

*/



