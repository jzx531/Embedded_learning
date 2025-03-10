#ifndef __DELAY_H
#define __DELAY_H 			   

#include "stm32f1xx_hal.h"
//STM32F103核心板例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif
/*
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
*/



//正点原子教程
void delay_init(uint16_t sysclk);       /* 初始化延迟函数 */
void delay_ms(uint16_t nms);            /* 延时nms */
void delay_us(uint32_t nus);            /* 延时nus */

#if (!SYS_SUPPORT_OS)                   /* 如果不支持OS */
    void HAL_Delay(uint32_t Delay);     /* HAL库的延时函数，HAL库内部用到 */
#endif

#endif





























