/*
文件名 ui.c
创建人：妙啊
创建时间：2022/3/22
功能：


修改日志：


现有问题：



*/
#include "oled0561.h"
#include "sys.h"
#include "key.h"
#include "adc.h"
#include "buzzer.h"
#include "delay.h"
#include "led.h"
#include "encoder.h"
#include "flash.h"
#include "drv_RF24L01.h"

float speed_ud,speed_lr;
float dir_ud,dir_lr;

u8 led_state = 0;
u8 BP_flag = 0;
u8 LED_flag = 0;
u8 key1_flag = 0;
u8 key3_flag = 0;
u16 set_vel[4] = {1740,1920,2010,2010};
u8 ch_last = 0;

u8 encoder_flag = 0;
u8 encoder_light = 100;

char channel[][16]={"ch1 < on >    ", "ch2 < off >   ", "ch3 < off >   ", "ch4 < off >   ",
            "ch5 < off >   ", "ch6 < off >   ", "ch7 < off >   ", "ch8 < off >   ", "ch9 < off >   ",
            "ch10 < off >  ", "ch11 < off >  ", "ch12 < off >  ", "ch13 < off >  ", "ch14 < off >  ",
            "ch15 < off >  ", "ch16 < off >  ","               ","               ","              "};

void here(void){
    //分隔符
    OLED_DISPLAY_8x16_BUFFER(0,"MiaoA");
    OLED_DISPLAY_8x16(2,0*7,'-');
    OLED_DISPLAY_8x16(2,1*7,'-');
    OLED_DISPLAY_8x16(2,2*7,'-');
    OLED_DISPLAY_8x16(2,3*7,'-');
    OLED_DISPLAY_8x16(2,4*7,'-');
    OLED_DISPLAY_8x16(2,5*7,'-');
    OLED_DISPLAY_8x16(2,6*7,'-');
    OLED_DISPLAY_8x16(2,7*7,'-');
    OLED_DISPLAY_8x16(2,8*7,'-');
    OLED_DISPLAY_8x16(2,9*7,'-');
    OLED_DISPLAY_8x16(2,10*7,'-');
    OLED_DISPLAY_8x16(2,11*7,'-');
    OLED_DISPLAY_8x16(2,12*7,'-');
    //OLED_DISPLAY_8x16(2,13*7,'-');
    // OLED_DISPLAY_8x16(2,14*7,'-');
    // OLED_DISPLAY_8x16(2,15*7,'-');
    // OLED_DISPLAY_8x16(2,16*7,'-');


}


//主页面显示
//速度推杆，方向摇杆，BP响，LED
void MiaoA_Main(void){
    //OLED_DISPLAY_8x16_BUFFER(0,"MiaoA");

    //右纽子开关 BP响
    if(GPIO_ReadInputDataBit(GPIOB,KEY5_F) == 0){
        OLED_DISPLAY_8x16(0,14*8,'B');
        OLED_DISPLAY_8x16(0,15*8,'P');
        if(BP_flag == 0){ BUZZER_BEEP1();delay_ms(100);BUZZER_BEEP1(); BP_flag = 1;}
    }
    else{
        OLED_DISPLAY_8x16(0,14*8,' ');
        OLED_DISPLAY_8x16(0,15*8,' ');
        BP_flag = 0;
    }

    //左纽子开关 LED
    if(GPIO_ReadInputDataBit(GPIOB,KEY6_F) != 0){
        OLED_DISPLAY_8x16(0,10*8,'L');
        OLED_DISPLAY_8x16(0,11*8,'E');
        OLED_DISPLAY_8x16(0,12*8,'D');
        led_state = 1;
        if(LED_flag == 0){ LED_Flash(LED_BLUE);delay_ms(10);LED_Flash(LED_BLUE); LED_flag = 1;}
    }
    else{
        OLED_DISPLAY_8x16(0,10*8,' ');
        OLED_DISPLAY_8x16(0,11*8,' ');
        OLED_DISPLAY_8x16(0,12*8,' ');
        led_state = 0;
        LED_flag = 0;
    }


    speed_ud = ADC_DMA_IN[1];
    speed_ud = (speed_ud - set_vel[0]) / 4060 * 80;
    if(speed_ud > 40)
        speed_ud = 40;

    OLED_DISPLAY_8x16_BUFFER(4,"----------I     ");
    OLED_DISPLAY_8x16(4,(u8)(speed_ud + 40),'I');
    
    speed_lr = ADC_DMA_IN[0];
    speed_lr = (speed_lr - set_vel[1]) / 4060 * 80;
    // if(speed_lr > 40)
    //     speed_lr = 40;

    OLED_DISPLAY_8x16_BUFFER(6,"----------I     ");
    OLED_DISPLAY_8x16(6,(u8)(speed_lr + 40),'I');

    dir_ud = ADC_DMA_IN[3];
    dir_ud = -(dir_ud - set_vel[2]) / 4060 * 5;
    // if(dir_ud >2)
    //     dir_ud = 2;
    if (dir_ud < -2)
        dir_ud = -2;
    dir_lr = ADC_DMA_IN[2];
    dir_lr = -(dir_lr - set_vel[3]) / 4060 * 30;
    // if(dir_lr > 30)
    //     dir_lr = 30;
    OLED_DISPLAY_8x16(2,11*8,' ');
    OLED_DISPLAY_8x16(2,12*8,' ');
    OLED_DISPLAY_8x16(2,13*8,' ');
    OLED_DISPLAY_8x16(2,14*8,' ');
    OLED_DISPLAY_8x16(2,15*8,' ');
    OLED_DISPLAY_8x16(dir_ud+3+1,dir_lr+88+16,'.');
}

//按键1设置键
//显示摇杆采集值
void set_key1(void){
    OLED_DISPLAY_8x16_BUFFER(0,"      MiaoA");
    OLED_DISPLAY_8x16_BUFFER(2,"UD:     UD:");
    OLED_DISPLAY_8x16_BUFFER(4,"LR:     LR:");
    OLED_DISPLAY_8x16_BUFFER(6,"s3->esc s5->set");
    while(key1_flag){
        OLED_DISPLAY_8x16(2,3*8,ADC_DMA_IN[1]/1000+0x30);
        OLED_DISPLAY_8x16(2,4*8,ADC_DMA_IN[1]/100%10+0x30);
        OLED_DISPLAY_8x16(2,5*8,ADC_DMA_IN[1]/10%10+0x30);
        OLED_DISPLAY_8x16(2,6*8,ADC_DMA_IN[1]%10+0x30);

        OLED_DISPLAY_8x16(2,12*8,ADC_DMA_IN[3]/1000+0x30);
        OLED_DISPLAY_8x16(2,13*8,ADC_DMA_IN[3]/100%10+0x30);
        OLED_DISPLAY_8x16(2,14*8,ADC_DMA_IN[3]/10%10+0x30);
        OLED_DISPLAY_8x16(2,15*8,ADC_DMA_IN[3]%10+0x30);

        OLED_DISPLAY_8x16(4,3*8,ADC_DMA_IN[0]/1000+0x30);
        OLED_DISPLAY_8x16(4,4*8,ADC_DMA_IN[0]/100%10+0x30);
        OLED_DISPLAY_8x16(4,5*8,ADC_DMA_IN[0]/10%10+0x30);
        OLED_DISPLAY_8x16(4,6*8,ADC_DMA_IN[0]%10+0x30);

        OLED_DISPLAY_8x16(4,12*8,ADC_DMA_IN[2]/1000+0x30);
        OLED_DISPLAY_8x16(4,13*8,ADC_DMA_IN[2]/100%10+0x30);
        OLED_DISPLAY_8x16(4,14*8,ADC_DMA_IN[2]/10%10+0x30);
        OLED_DISPLAY_8x16(4,15*8,ADC_DMA_IN[2]%10+0x30);
        if(GPIO_ReadInputDataBit(GPIOA,KEY2) == 0){
            set_vel[0] = ADC_DMA_IN[1];
            set_vel[1] = ADC_DMA_IN[0];
            set_vel[2] = ADC_DMA_IN[2];
            set_vel[3] = ADC_DMA_IN[3];
            BUZZER_BEEP1();
            while(!GPIO_ReadInputDataBit(GPIOA,KEY2));
        }
            
        if(GPIO_ReadInputDataBit(GPIOA,KEY1) == 0){
            OLED_DISPLAY_CLEAR();
            here();
            BUZZER_BEEP1();
            key1_flag = 0;
            while(!GPIO_ReadInputDataBit(GPIOA,KEY1));
        }
    }
}

//按键4
//液晶亮度调节
void set_light_key4(void){
    u8 encoder_rev;
    OLED_DISPLAY_8x16_BUFFER(0,"      MiaoA");
    OLED_DISPLAY_8x16_BUFFER(2,"brightness:");
    OLED_DISPLAY_8x16_BUFFER(6,"s6->esc s4->set");
    OLED_DISPLAY_8x16(2,13*8,encoder_light/100+0x30);
    OLED_DISPLAY_8x16(2,14*8,encoder_light/10%10+0x30);
    OLED_DISPLAY_8x16(2,15*8,encoder_light%10+0x30);
   
    while(encoder_flag){
        encoder_rev = ENCODER_READ();
        if(encoder_rev==1){ encoder_light++;if(encoder_light>255)encoder_light=0; } //分析按键值，并加减计数器值。
        if(encoder_rev==2){ if(encoder_light==0)encoder_light=255;encoder_light--; }
        if(encoder_rev==3)encoder_light=0;
        if(encoder_rev!=0){ //如果有旋转器的操作
            OLED_DISPLAY_8x16(2,13*8,encoder_light/100+0x30);
            OLED_DISPLAY_8x16(2,14*8,encoder_light/10%10+0x30);
            OLED_DISPLAY_8x16(2,15*8,encoder_light%10+0x30);
        }
        if(GPIO_ReadInputDataBit(GPIOA,KEY3)==0){
            OLED_DISPLAY_LIT(encoder_light);
            FLASH_W(FLASH_lIGHT_ADDR,encoder_light);
            BUZZER_BEEP1();
            while(!GPIO_ReadInputDataBit(GPIOA,KEY3));
        }
        if(GPIO_ReadInputDataBit(GPIOB,KEY4)==0){
            BUZZER_BEEP1();
            encoder_flag = 0;
            OLED_DISPLAY_CLEAR();
            while(!GPIO_ReadInputDataBit(GPIOB,KEY4));
        }
    }
    here();
}


//通道切换
//16个通道
void set_channel_key3(){
    u8 ch_ch[] = {0x12,0x01,0x02,0x10,0x11,0x34,0x41,0x32,0x22,0x31,0x42,0x43,0x13,0x03,0x21};
    int temp = 0;
    while(key3_flag){
        // for(j = 0,i = temp;j <= 6;i++,j += 2 ){

            OLED_DISPLAY_8x16_BUFFER(0,(u8*)channel[temp]);
            OLED_DISPLAY_8x16_BUFFER(2,(u8*)channel[temp+1]);
            OLED_DISPLAY_8x16_BUFFER(4,(u8*)channel[temp+2]);
            OLED_DISPLAY_8x16_BUFFER(6,(u8*)channel[temp+3]);
            // if(j == temp){
            OLED_DISPLAY_8x16(0,14*8,'<');
            OLED_DISPLAY_8x16(0,15*8,'-');
            // }
        // }
        if(GPIO_ReadInputDataBit(GPIOA,KEY1) == 0){
            temp++;
            if(temp >= 15)
                temp = 0;
            BUZZER_BEEP1();
            while(!GPIO_ReadInputDataBit(GPIOA,KEY1));
        }
        if(GPIO_ReadInputDataBit(GPIOA,KEY2) == 0){
            temp--;
            if(temp < 0)
                temp = 15;
            BUZZER_BEEP1();
             while(!GPIO_ReadInputDataBit(GPIOA,KEY2));
        }

        if(GPIO_ReadInputDataBit(ENCODER_PORT_B,ENCODER_D) == 0){
            channel[ch_last][6] = 'o';
            channel[ch_last][7] = 'f';
            channel[ch_last][8] = 'f';
            channel[temp][6] = 'o';
            channel[temp][7] = 'n';
            channel[temp][8] = ' ';
            ch_last = temp;
            addr[2] = ch_ch[temp];
            RF24L01_Init();
            BUZZER_BEEP1();
             while(!GPIO_ReadInputDataBit(ENCODER_PORT_B,ENCODER_D));
        }

        if(GPIO_ReadInputDataBit(GPIOA,KEY3) == 0){
            OLED_DISPLAY_CLEAR();
            BUZZER_BEEP1();
            key3_flag = 0;
            while(!GPIO_ReadInputDataBit(GPIOA,KEY3));
        }
    }
    here();
}
