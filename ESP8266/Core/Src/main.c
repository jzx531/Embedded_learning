#include "main.h"
#include "tim.h"
#include "gpio.h"
//#include "usart.h"
#include "bsp_debug_usart.h"
#include "i2c.h"
#include "adc.h"


#include "delay.h"
#include "GUI.h"
#include "Lcd_driver.h"
#include "TFT_demo.h"

#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "nvic.h"
#include "MQ135.h"
#include "string.h"

#include "led.h"
#include "stdio.h"


void SystemClock_Config(void);

extern char Buffer[20];
extern char rxBuf[UART_IT];


float temperature=0;
/**
  * @brief  The application entry point.
  * @retval int
  */
  /*
void ESP8266_Init(void)
{
    macESP8266_RST_HIGH_LEVEL();

    macESP8266_CH_DISABLE();
}*/


int main(void)
{


  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  SystemClock_Config();

    
  MX_I2C1_Init();  
  MX_GPIO_Init();
   
	DEBUG_USART_Config();
  MX_TIM2_Init();
  MX_TIM3_Init();

 
  /* USER CODE BEGIN 2 */
    delay_init(72);
    Lcd_Init();
    Lcd_Clear(YELLOW);
    LED_toggle();
    MX_ADC1_Init();
    HAL_ADC_Start_IT(&hadc1);
		
    ESP8266_Init ();           //初始化WiFi模块使用的接口和外设
    macESP8266_CH_ENABLE();   //使能 ESP8266
    printf ( "\r\n野火 WF-ESP8266 WiFi模块测试例程\r\n" );                          //打印测试例程提示信息
    printf ( "\r\n在网络调试助手或者串口调试助手上发送以下命令可以控制板载LED灯\r\n" );    //打印测试例程提示信息
    printf ( "\r\nLED1_ON\r\nLED2_ON\r\nLED3_ON\r\nLED_ALLOFF\r\n" );
    
    
    ESP8266_StaTcpClient_Unvarnish_ConfigTest();                          //对ESP8266进行配置
    //ESP8266_StaMQTTClient_Unvarnish_ConfigTest();
    printf ( "\r\n在网络调试助手或者串口调试助手  发送以下命令控制板载LED灯：\r\n" );    //打印测试例程提示信息
    printf ( "\r\nLED1_ON\r\nLED2_ON\r\nLED3_ON\r\nLED_ALLOFF\r\n" );
    printf ( "\r\n观察LED灯的状态变化\r\n" );
    
		
		
    while ( 1 )
    {
			
			if(strUSART_Fram_Record .InfBit .FramFinishFlag)  //如果接收到了串口调试助手的数据
			{

				strUSART_Fram_Record .Data_RX_BUF[strUSART_Fram_Record .InfBit .FramLength] = '\0';
				//HAL_UART_Transmit(&UartHandle ,(uint8_t* )strUSART_Fram_Record .Data_RX_BUF,strlen(strUSART_Fram_Record .Data_RX_BUF),HAL_MAX_DELAY);
				//printf("\n");
				//strcat(strUSART_Fram_Record .Data_RX_BUF,"\r\n");
				//HAL_UART_Transmit(&huart3 ,(uint8_t* )strUSART_Fram_Record .Data_RX_BUF,strlen(strUSART_Fram_Record .Data_RX_BUF),HAL_MAX_DELAY);        //数据从ESP8266转发到串口调试助手
				printf("发送指令:%s",strUSART_Fram_Record .Data_RX_BUF);
				macESP8266_RST_HIGH_LEVEL();
				//printf("\r\nAT测试.....\r\n");
			  HAL_Delay ( 2000 );
				strEsp8266_Fram_Record .InfBit .FramLength = 0;               //重新开始接收新的数据包
				macESP8266_Usart ( "%s\r\n", strUSART_Fram_Record .Data_RX_BUF );
				strUSART_Fram_Record .InfBit .FramLength = 0;                                //接收数据长度置零
				strUSART_Fram_Record .InfBit .FramFinishFlag = 0;                            //接收标志置零
			}
			if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)                             //如果接收到了ESP8266的数据
			{                                                      
				 strEsp8266_Fram_Record .Data_RX_BUF[strEsp8266_Fram_Record .InfBit .FramLength] = '\0';
				 //HAL_UART_Transmit(&UartHandle ,(uint8_t* )strEsp8266_Fram_Record .Data_RX_BUF,strlen(strEsp8266_Fram_Record .Data_RX_BUF),HAL_MAX_DELAY);        //数据从ESP8266转发到串口调试助手
				 //printf("8266回复:%s\n",strEsp8266_Fram_Record .Data_RX_BUF);
				 
				//Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,(uint8_t *)strEsp8266_Fram_Record .Data_RX_BUF);
					if(!ucTcpClosedFlag){
						//Fullscreen_showimage((const unsigned char *)strEsp8266_Fram_Record .Data_RX_BUF);
						//showimage_XY((const unsigned char *)strEsp8266_Fram_Record .Data_RX_BUF,44,44);
						showimage_interp_XY((const unsigned char *)strEsp8266_Fram_Record .Data_RX_BUF,40,40,3);
						//showimage((const unsigned char *)strEsp8266_Fram_Record .Data_RX_BUF);
					}
				
				
				 strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
				 strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
			}
			if(!ucTcpClosedFlag){
				ESP8266_SendDHT11DataTest();
				HAL_Delay(500);
			}
    }


}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}




void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */



