#ifndef ESP_COMMON_H
#define ESP_COMMON_H


#include "stm32f1xx_hal.h"



/******************************* 宏定义 ***************************/
#define            macNVIC_PriorityGroup_x                     NVIC_PriorityGroup_2



/********************************** 函数声明 ***************************************/
void                     USART_printf                       ( USART_TypeDef * USARTx, char * Data, ... );



#endif /* __COMMON_H */


