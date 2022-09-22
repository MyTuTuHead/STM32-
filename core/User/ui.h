#ifndef __UI_H
#define __UI_H	 
#include "sys.h"


#define GO  1
#define BACK    0

extern u8 key1_flag;
extern u8 key3_flag;
extern u8 led_state;
extern u8 encoder_flag;
extern u8 encoder_light;

extern float speed_ud,speed_lr;
extern float dir_ud,dir_lr;



void MiaoA_Main(void);
void here(void);
void set_key1(void);
void set_light_key4(void);
void set_channel_key3();


#endif
