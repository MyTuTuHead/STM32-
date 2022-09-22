/*
文件名 led.c
创建人：妙啊
创建时间：2022/3/20
功能：


修改日志：


现有问题：



*/
#include "delay.h"
#include "led.h"

void LED_Init(void){ //LED灯的接口初始化
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE|RCC_APB2Periph_AFIO);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启复用时钟
		
	
    GPIO_InitStructure.GPIO_Pin = LED; //选择端口号（0~15或all）
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择IO接口工作方式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(GPIOC, &GPIO_InitStructure);//PB11端口初始化
	GPIO_WriteBit(GPIOC,LED,(BitAction)(1));
}



/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/
