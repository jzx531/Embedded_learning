#ifndef  __BSP_ESP8266_H
#define	 __BSP_ESP8266_H


#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>
#include "usart.h"
#include "esp_common.h"

#ifndef u32
#define u32 uint32_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u8
#define u8 uint_t
#endif


#if defined ( __CC_ARM   )
#pragma anon_unions
#endif



/******************************* ESP8266 数据类型定义 ***************************/
typedef enum{
	STA,
  AP,
  STA_AP  
} ENUM_Net_ModeTypeDef;


typedef enum{
	 enumTCP,
	 enumUDP,
} ENUM_NetPro_TypeDef;
	

typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID_0 = 5,
} ENUM_ID_NO_TypeDef;
	

typedef enum{
	OPEN = 0,
	WEP = 1,
	WPA_PSK = 2,
	WPA2_PSK = 3,
	WPA_WPA2_PSK = 4,
} ENUM_AP_PsdMode_TypeDef;



/******************************* ESP8266 外部全局变量声明 ***************************/
//#define RX_BUF_MAX_LEN     1024                                     //最大接收缓存字节数
#define RX_BUF_MAX_LEN     4096                                   //最大接收缓存字节数

extern struct  STRUCT_USARTx_Fram                                  //串口数据帧的处理结构体
{
	char  Data_RX_BUF [ RX_BUF_MAX_LEN ];
	
  union {
    __IO u16 InfAll;
    struct {
		  __IO u16 FramLength       :15;                               // 14:0 
		  __IO u16 FramFinishFlag   :1;                                // 15 
	  } InfBit;
  }; 
	
} strEsp8266_Fram_Record;

extern struct STRUCT_USARTx_Fram strUSART_Fram_Record;

/******************************** ESP8266 连接引脚定义 ***********************************/
#define      macESP8266_CH_PD_CLK_ENABLE()                    __HAL_RCC_GPIOB_CLK_ENABLE()  
#define      macESP8266_CH_PD_PORT                            GPIOB
#define      macESP8266_CH_PD_PIN                             GPIO_PIN_8

#define      macESP8266_RST_CLK_ENABLE()                      __HAL_RCC_GPIOB_CLK_ENABLE()
#define      macESP8266_RST_PORT                              GPIOB
#define      macESP8266_RST_PIN                               GPIO_PIN_9

 

#define      macESP8266_USART_BAUD_RATE                       115200

#define      macESP8266_USARTx                                USART3
#define      macESP8266_USART_CLK_ENABLE()                    __HAL_RCC_USART3_CLK_ENABLE()
#define      macESP8266_USART_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOB_CLK_ENABLE()     
#define      macESP8266_USART_TX_PORT                         GPIOB   
#define      macESP8266_USART_TX_PIN                          GPIO_PIN_10
#define      macESP8266_USART_RX_PORT                         GPIOB
#define      macESP8266_USART_RX_PIN                          GPIO_PIN_11
#define      macESP8266_USART_IRQ                             USART3_IRQn
#define      macESP8266_USART_INT_FUN                         USART3_IRQHandler



/*********************************************** ESP8266 函数宏定义 *******************************************/
#define     macESP8266_Usart( fmt, ... )           USART_printf ( macESP8266_USARTx, fmt, ##__VA_ARGS__ ) 
#define     macPC_Usart( fmt, ... )                printf ( fmt, ##__VA_ARGS__ )
//#define     macPC_Usart( fmt, ... )                

#define     macESP8266_CH_ENABLE()                 HAL_GPIO_WritePin( macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN, GPIO_PIN_SET )
#define     macESP8266_CH_DISABLE()                HAL_GPIO_WritePin( macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN, GPIO_PIN_RESET )

#define     macESP8266_RST_HIGH_LEVEL()            HAL_GPIO_WritePin ( macESP8266_RST_PORT, macESP8266_RST_PIN, GPIO_PIN_SET )
#define     macESP8266_RST_LOW_LEVEL()             HAL_GPIO_WritePin ( macESP8266_RST_PORT, macESP8266_RST_PIN, GPIO_PIN_RESET )


/****************************************** ESP8266 函数声明 ***********************************************/
void                     ESP8266_Init                        ( void );
void                     ESP8266_Rst                         ( void );
bool                     ESP8266_Cmd                         ( char * cmd, char * reply1, char * reply2, u32 waittime );
bool                     ESP8266_AT_Test                     ( void );
bool                     ESP8266_Net_Mode_Choose             ( ENUM_Net_ModeTypeDef enumMode );
bool                     ESP8266_JoinAP                      ( char * pSSID, char * pPassWord );
bool                     ESP8266_BuildAP                     ( char * pSSID, char * pPassWord, ENUM_AP_PsdMode_TypeDef enunPsdMode );
bool                     ESP8266_Enable_MultipleId           ( FunctionalState enumEnUnvarnishTx );
bool                     ESP8266_Link_Server                 ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool                     ESP8266_StartOrShutServer           ( FunctionalState enumMode, char * pPortNum, char * pTimeOver );
uint8_t                  ESP8266_Get_LinkStatus              ( void );
uint8_t                  ESP8266_Get_IdLinkStatus            ( void );
uint8_t                  ESP8266_Inquire_ApIp                ( char * pApIp, uint8_t ucArrayLength );
bool                     ESP8266_UnvarnishSend               ( void );
void                     ESP8266_ExitUnvarnishSend           ( void );
bool                     ESP8266_SendString                  ( FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId );
char *                   ESP8266_ReceiveString               ( FunctionalState enumEnUnvarnishTx );
bool                     ESP8266_DHCP_CUR                    ( void );


#endif

//下面两个函数需要注释掉UART1,3的IRQ_Handler
/*
void macESP8266_USART_INT_FUN(void)
{
    uint8_t ucCh;
    UART_HandleTypeDef *huart = &huart3; // 假设 hmesp8266_usart 是 macESP8266_USARTx 的 HAL 句柄
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET)
    {
        ucCh = (uint8_t)(huart->Instance->DR & 0xFF); // 读取接收到的数据
        //printf("8266 data %c\n", ucCh);

        if (strEsp8266_Fram_Record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1)) // 预留1个字节写结束符
        {
            strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength++] = ucCh;
        }
    }

    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET) // 数据帧接收完毕
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart); // 清除空闲中断标志
        ucCh = (uint8_t)(huart->Instance->DR & 0xFF); // 读取接收到的数据
        //printf("8266 over data %c\n", ucCh);
				
        //if (strEsp8266_Fram_Record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1)) // 预留1个字节写结束符
        //{
        //    strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength++] = ucCh;
        //} 
        //strEsp8266_Fram_Record.InfBit.FramFinishFlag = 1;
        //ucTcpClosedFlag = strstr(strEsp8266_Fram_Record.Data_RX_BUF, "CLOSED\r\n") ? 1 : 0;
				//HAL_UART_Transmit(&UartHandle ,(uint8_t* )strEsp8266_Fram_Record .Data_RX_BUF,strlen(strEsp8266_Fram_Record .Data_RX_BUF),HAL_MAX_DELAY);   
		}
}


void DEBUG_USART_IRQHandler(void)
{
    uint8_t ucCh;
    UART_HandleTypeDef *huart = &UartHandle; // 假设 hdebug_usart 是 DEBUG_USARTx 的 HAL 句柄

    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET)
    {
        ucCh = (uint8_t)(huart->Instance->DR & 0xFF); // 读取接收到的数据
        //printf("rx data %c\n", ucCh);

        if (strUSART_Fram_Record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1)) // 预留1个字节写结束符
        {
            strUSART_Fram_Record.Data_RX_BUF[strUSART_Fram_Record.InfBit.FramLength++] = ucCh;
        }
    }

    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET) // 数据帧接收完毕
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart); // 清除空闲中断标志
        
			//	ucCh = (uint8_t)(huart->Instance->DR & 0xFF); // 读取接收到的数据
      //  printf("rx over data %c\n", ucCh);
      //  
      //  if (strUSART_Fram_Record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1)) // 预留1个字节写结束符
     //  {
     //       strUSART_Fram_Record.Data_RX_BUF[strUSART_Fram_Record.InfBit.FramLength++] = ucCh;
      //  }
      //  strUSART_Fram_Record.InfBit.FramFinishFlag = 1;
    }
}
*/
