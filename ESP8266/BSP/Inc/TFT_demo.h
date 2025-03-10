#ifndef __TFT_DEMO_H
#define __TFT_DEMO_H 

//STM32F103核心板例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/
#include "stm32f1xx_hal.h"

void Redraw_Mainmenu(void);
void Num_Test(void);
void Font_Test(void);
void Color_Test(void);
void showimage(const unsigned char *p);
void showimage_XY(const unsigned char *p,uint8_t x,uint8_t y);
void showimage_interp_XY(const unsigned char *p,uint8_t x,uint8_t y,uint8_t interp);

void Test_Demo(void);

void Fullscreen_showimage(const unsigned char *p);

#endif
