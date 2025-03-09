#ifndef MQ135_H
#define MQ135_H

#include "stm32f1xx_hal.h"

extern __IO uint32_t ADC_ConvertedValue;

// AO ADC GPIO 宏定义
#define MQ135_ADC_GPIO_PORT              GPIOA
#define MQ135_ADC_GPIO_PIN               GPIO_PIN_4
#define MQ135_ADC_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

// DO Input GPIO 定义
#define DO_INPUT_GPIO_PORT               GPIOA
#define DO_INPUT_GPIO_PIN                GPIO_PIN_5
#define DO_INPUT_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
    
// ADC 序号宏定义
#define MQ135_ADC                        ADC1
#define MQ135_ADC_CLK_ENABLE()           __HAL_RCC_ADC1_CLK_ENABLE(); 
#define MQ135_ADC_CHANNEL                ADC_CHANNEL_4

// ADC 中断宏定义
#define MQ135_ADC_IRQ                    ADC1_IRQn
#define MQ135_ADC_INT_FUNCTION           ADC1_IRQHandler


#define RL                               1     /* 根据硬件原理图可知：RL = 1k */ 
#define R0                               2     /* MQ135在洁净空气中的阻值，官方数据手册没有给出，这是实验测试得出，想要准确请多次测试 */ 
#define VC                               5.0   /* MQ135供电电压,根据实际供电修改，默认接5V */
#define A                                4.17  /* y=ax^b 的 a */
#define B                                -2.28 /* y=ax^b 的 b */

void MQ135_Init(void);
float MQ135_Get_PPM(void);

#endif

