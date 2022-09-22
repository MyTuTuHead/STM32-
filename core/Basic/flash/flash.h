#ifndef __FLASH_H
#define __FLASH_H 			   
#include "sys.h"
 
#define FLASH_lIGHT_ADDR	0x0801f000


void FLASH_W(u32 add,u16 dat);
u16 FLASH_R(u32 add);

#endif





























