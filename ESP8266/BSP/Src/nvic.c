#include "nvic.h"

#include "TFT_demo.h"
#include "GUI.h"
#include "Lcd_driver.h"



#include "stdio.h"
#include "string.h"

#include "i2c.h"
#include "mpu6050_calculate.h"
#include "mpu6050_driver.h"
#include "adc.h"
#include "MQ135.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"

/*
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}
 

 //@brief 重定向c库函数getchar,scanf到USARTx

int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
    return ch;
}*/

char Buffer[20];

char rxBuf[1];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if(huart->Instance == USART1)

    {
				strcpy(strUSART_Fram_Record .Data_RX_BUF,rxBuf);
				strUSART_Fram_Record .InfBit .FramLength=UART_IT;
				strUSART_Fram_Record .InfBit .FramFinishFlag = 1; 
				strUSART_Fram_Record .Data_RX_BUF[strUSART_Fram_Record .InfBit .FramLength] = '\0';
				HAL_UART_Transmit(&huart3 ,(uint8_t* )strUSART_Fram_Record .Data_RX_BUF,strlen(strUSART_Fram_Record .Data_RX_BUF),HAL_MAX_DELAY);        //数据从ESP8266转发到串口调试助手
				strUSART_Fram_Record .InfBit .FramLength = 0;                                //接收数据长度置零
				strUSART_Fram_Record .InfBit .FramFinishFlag = 0;                            //接收标志置零
			
			
				strcpy(Buffer,"RxCallback");
				Gui_DrawFont_GBK16(6,0,BLUE,GRAY0,(uint8_t*)Buffer);

				printf(Buffer);
				printf(rxBuf);
        //HAL_Delay(10);
				HAL_UART_Receive_IT(&huart1,(uint8_t *)rxBuf,1);
    }
		if(huart->Instance==USART3)
		{
			printf("USART3");
			HAL_UART_Receive_IT(&huart3, (uint8_t *)&(strEsp8266_Fram_Record.Data_RX_BUF) ,strlen(strEsp8266_Fram_Record.Data_RX_BUF));
		}		
}



void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{

    if(huart->Instance == USART1)

    {
				//Buffer="RxHalfCallback";
				strcpy(Buffer,"RxHalfCallback");
				Gui_DrawFont_GBK16(6,0,BLUE,GRAY0,(uint8_t*)Buffer);
				printf(Buffer);
				//HAL_Delay(10);
				HAL_UART_Receive_IT(&huart1,(uint8_t *)rxBuf,UART_IT );
    }
		if(huart->Instance==USART3)
		{
			printf("USART3");
		}
}

/*

*/

int LED = 1;
char str[6];
//中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2){
         if(LED){
					 LED =0;
					 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
         }
         else{
            LED =1;
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
         };
				
    }
		
		else if(htim->Instance == TIM3)
		{
			//ADC_ConvertedValue = HAL_ADC_GetValue(&hadc1);
			/*
			float ppm = MQ135_Get_PPM();
			printf("digital data = %d\n",HAL_GPIO_ReadPin(DO_INPUT_GPIO_PORT,DO_INPUT_GPIO_PIN)); 
      printf("analog data = %d\n",ADC_ConvertedValue);
			printf("ppm = %f\n",ppm);
			sprintf(str, "%.6f",ppm ); // 保留两位小数
			Gui_DrawFont_GBK16(8,0,BLUE,GRAY0,(uint8_t *)str);*/
			/*
			GetMpuData();
			AngleCalculate();
			printf("%f,%f,%f",g_fAccAngle,g_fGyroAngleSpeed,g_fCarAngle);
			*/
			
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

		//Buffer=" man\t ";
		strcpy(Buffer,"man\t");
		
    HAL_UART_Transmit(&huart1, (uint8_t *)Buffer, sizeof(Buffer), 0xffff);
		Gui_DrawFont_GBK16(8,0,BLUE,GRAY0,(uint8_t *)Buffer);
		printf("what can i say");
	}
  else if(GPIO_Pin==GPIO_PIN_1)
	{
		printf("gpio a1\n");
	}
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance==I2C1)
	{
		printf("I2C INT");
		AngleCalculate();
		printf("%f,%f,%f",g_fAccAngle,g_fGyroAngleSpeed,g_fCarAngle);
	}
}


//ADC 中断
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
    /* 获取结果 */
	if(AdcHandle->Instance==ADC1){
		//printf("adc");
    ADC_ConvertedValue = HAL_ADC_GetValue(AdcHandle);
	}
}



