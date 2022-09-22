/*
文件名：main
创建人：MiaoA
创建时间：2022/4/17
功能：


占用资源:



修改日志：


现有问题：


*/

#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "oled0561.h"
#include "usart.h"
#include "flash.h"
#include "pwm.h"



int main (void){//主程序
	u8 asr = 0;
	u8 key = 0;
	u32 light = 100;//灯光亮度 值越大，越暗  0-100
	u32 sys_time = 0;
	u32 time_count = 0;
	u8 delay_led = 0;

	delay_ms(100); //上电时等待其他器件就绪,必要延时
	RCC_Configuration(); //系统时钟初始化
		
	LED_Init();//LED_init
	
	KEY_Init();//按键1,2,3,4初始化

	ASR_Init();//ASR接口初始化

	USART1_Init(115200);

	TIM3_PWM_Init(999,8);//PWM初始化 50HZ

	printf("MiaoA");
			
	while(1){
		
		asr = Asr_Read();//读取语音识别结果
		key = Key_Read();//读取按键输入

//		if(asr != 0)//调试使用
//			printf("asr:%d		",asr);

		if(asr == 1 || led_flag == 1 || key == 1){//开灯
			GPIO_WriteBit(GPIOC,LED,(BitAction)(0));//打开板载灯光
			
			printf("LED ON");
			light = 50;
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 7 || led_flag == 2 || key == 2){//关灯
			GPIO_WriteBit(GPIOC,LED,(BitAction)(1));//关闭板载灯光
			light = 100;
			printf("LED OFF");
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 2 || led_flag == 3 || key == 3){//增大亮度
			printf("Light up");
			if(light > 10)
				light -= 10;
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 3 || led_flag == 4 || key == 4){//减小亮度
			if(light < 90)
				light += 10;
			printf("Light down");
			led_flag = 0;
			asr = 0;
			key = 0;
		}

		if(asr == 4 || led_flag == 5){//延时关闭
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

		if(asr == 5 || led_flag == 6){//一分钟后关闭
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

		if(asr == 6 || led_flag == 7){//五分钟后关闭
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
			if(time_count > 1500){//用于延时关闭的时间调节
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
			if(time_count > 5000){//用于延时关闭的时间调节
				GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
				time_count = 0;
				sys_time = 0;
				delay_led = 0;
				light = 100;
			}
		}

		TIM_SetCompare3(TIM3,light * 10);//调节亮度
	}
}
/*

u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED控制

*/



