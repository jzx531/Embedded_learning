#ifndef LED_H
#define LED_H

#include "TFT_demo.h"
#include "GUI.h"
#include "Lcd_driver.h"

#define LED_ON     HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET)
#define LED_OFF    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET)


void LED_toggle(void);


#endif

