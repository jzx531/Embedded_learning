#include "nvic.h"

#include "TFT_demo.h"
#include "GUI.h"
#include "Lcd_driver.h"

int LED = 1;

//中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == htim2.Instance){
         if(LED){HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
                            LED =0;
         }
         else{
            LED =1;
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
         }
    }
}


//按键中断
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_0)
	{
		Lcd_Clear(GREEN);
		//Gui_DrawFont_GBK16(8,0,BLUE,GRAY0,"STM32 C8T6");
		Gui_draw_star(RED);
	}
}