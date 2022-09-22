/*
ÎÄ¼þÃû£ºkey.c
´´½¨ÈË£ºÃî°¡
´´½¨Ê±¼ä£º2022/3/20
¹¦ÄÜ£º

Õ¼ÓÃ×ÊÔ´:

ÐÞ¸ÄÈÕÖ¾£º


ÏÖÓÐÎÊÌâ£º



*/


#include "key.h"
#include "delay.h"

void KEY_Init(void){ //
	GPIO_InitTypeDef  GPIO_InitStructure; //
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE); 
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//Ê§ÄÜJTAG½Ó¿Ú£¬Ê¹ÓÃPA15
      
    GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2 | KEY3 | KEY4; //                     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ÉÏÀ­ÊäÈë        
	GPIO_Init(KEY_PORT,&GPIO_InitStructure);	
}
 
u8 Key_Read(void){

		if(GPIO_ReadInputDataBit(KEY_PORT,KEY1)==0){
			delay_ms(5);
			if(GPIO_ReadInputDataBit(KEY_PORT,KEY1)==0){
				while(!GPIO_ReadInputDataBit(KEY_PORT,KEY1));
				return 1;
			}
		}

		if(GPIO_ReadInputDataBit(KEY_PORT,KEY2)==0){
			delay_ms(5);
			if(GPIO_ReadInputDataBit(KEY_PORT,KEY2)==0){
				while(!GPIO_ReadInputDataBit(KEY_PORT,KEY2));
				return 2;
			}
		}

		if(GPIO_ReadInputDataBit(KEY_PORT,KEY3)==0){
			delay_ms(5);
			if(GPIO_ReadInputDataBit(KEY_PORT,KEY3)==0){
				while(!GPIO_ReadInputDataBit(KEY_PORT,KEY3));
				return 3;
			}
		}

		if(GPIO_ReadInputDataBit(KEY_PORT,KEY4)==0){
			delay_ms(5);
			if(GPIO_ReadInputDataBit(KEY_PORT,KEY4)==0){
				while(!GPIO_ReadInputDataBit(KEY_PORT,KEY4));
				return 4;
			}
		}
	return 0;
}







void ASR_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = ASR1 | ASR2 | ASR3 | ASR4 | ASR5 | ASR6 | ASR7; //                     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //ÏÂÀ­ÊäÈë        
	GPIO_Init(ASR_PORT,&GPIO_InitStructure);	
}


//¶ÁÈ¡Ò»´ÎASR½á¹û
 u8 Asr_Read(void){

		if(GPIO_ReadInputDataBit(ASR_PORT,ASR1)==1){
			while(GPIO_ReadInputDataBit(ASR_PORT,ASR1));
			return 1;
		}

		if(GPIO_ReadInputDataBit(ASR_PORT,ASR2)==1){
			while(GPIO_ReadInputDataBit(ASR_PORT,ASR2));
			return 2;
		}

		if(GPIO_ReadInputDataBit(ASR_PORT,ASR3)==1){
			while(GPIO_ReadInputDataBit(ASR_PORT,ASR3));
			return 3;
		}

		if(GPIO_ReadInputDataBit(ASR_PORT,ASR4)==1){
			while(GPIO_ReadInputDataBit(ASR_PORT,ASR4));
			return 4;
		}

		if(GPIO_ReadInputDataBit(ASR_PORT,ASR5)==1){
			while(GPIO_ReadInputDataBit(ASR_PORT,ASR5));
			return 5;
		}

		if(GPIO_ReadInputDataBit(ASR_PORT,ASR6)==1){
			while(GPIO_ReadInputDataBit(ASR_PORT,ASR6));
			return 6;
		}

		if(GPIO_ReadInputDataBit(ASR_PORT,ASR7)==1){
			while(GPIO_ReadInputDataBit(ASR_PORT,ASR7));
			return 7;
		}
	return 0;
}


/*
Ñ¡ï¿½ï¿½IOï¿½Ó¿Ú¹ï¿½ï¿½ï¿½ï¿½ï¿½Ê½ï¿½ï¿½
GPIO_Mode_AIN Ä£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
GPIO_Mode_IN_FLOATING ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
GPIO_Mode_IPD ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
GPIO_Mode_IPU ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
GPIO_Mode_Out_PP ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
GPIO_Mode_Out_OD ï¿½ï¿½Â©ï¿½ï¿½ï¿?
GPIO_Mode_AF_PP ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
GPIO_Mode_AF_OD ï¿½ï¿½ï¿½Ã¿ï¿½Â©ï¿½ï¿½ï¿?
*/
