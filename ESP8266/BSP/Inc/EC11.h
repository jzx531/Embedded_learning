#ifndef EC11_H
#define EC11_H
#include "stm32f1xx_hal.h"

#define A_PIN GPIO_PIN_5
#define C_PIN GPIO_PIN_4
#define B_PIN GPIO_PIN_3
#define EC11_PORT GPIOB

#define EC11_DATA_A HAL_GPIO_ReadPin(EC11_PORT,A_PIN) 
#define EC11_DATA_B   HAL_GPIO_ReadPin(EC11_PORT,B_PIN)
#define EC11_DATA_key  HAL_GPIO_ReadPin(EC11_PORT,C_PIN)


int16_t Encoder_EC11_Scan(int16_t key,int16_t EC11_A,int16_t EC11_B); 

#endif

