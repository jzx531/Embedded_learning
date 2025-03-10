#include "bsp_esp8266_test.h"
#include "bsp_esp8266_mqtt.h"
#include "bsp_esp8266.h"
#include "delay.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "led.h"



#define LED_CMD_NUMBER   4
char *ledCmd[LED_CMD_NUMBER] = { "LED1_ON", "LED2_ON", "LED3_ON", "LED_ALLOFF" };


volatile uint8_t ucTcpClosedFlag = 0;



/**
  * @brief  获取网络调试助手和串口调试助手发来的信息
  * @param  无
  * @retval 无
  */
void Get_ESP82666_Cmd( char * cmd)
{
	uint8_t i;
	for(i = 0;i < LED_CMD_NUMBER; i++)
	{
     if(( bool ) strstr ( cmd, ledCmd[i] ))
		 break;
	}
	switch(i)
    {
      case 0:
        LED_ON;
        break;
      
      case 1:
        LED_ON;
        break;
      
      case 2:
        LED_ON;
        break;
      
      case 3:
        LED_OFF;
        //LED_OFF;
        //LED_OFF;
        break;
      
      default:
        break;      
    }   
}


/**
  * @brief  ESP8266 StaTcpClient Unvarnish 配置测试函数
  * @param  无
  * @retval 无
  */
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
  printf( "\r\n正在配置 ESP8266 ......\r\n" );
  printf( "\r\n使能 ESP8266 ......\r\n" );
	macESP8266_CH_ENABLE();
	while( ! ESP8266_AT_Test() );
  //while( ! ESP8266_DHCP_CUR () );
  printf( "\r\n正在配置工作模式 STA ......\r\n" );
	while( ! ESP8266_Net_Mode_Choose ( STA ) );

  printf( "\r\n正在连接 WiFi ......\r\n" );
  while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
  printf( "\r\n禁止多连接 ......\r\n" );
	while( ! ESP8266_Enable_MultipleId ( DISABLE ) );
	
  printf( "\r\n正在连接 Server ......\r\n" );
	while( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
  printf( "\r\n进入透传发送模式 ......\r\n" );
	while( ! ESP8266_UnvarnishSend () );
	
	printf( "\r\n配置 ESP8266 完毕\r\n" );
	printf ( "\r\n开始透传......\r\n" );
  
}

void ESP8266_StaMQTTClient_Unvarnish_ConfigTest(void)
{
    printf( "\r\n正在配置 ESP8266 ......\r\n" );
    printf( "\r\n使能 ESP8266 ......\r\n" );
    macESP8266_CH_ENABLE();
    while( ! ESP8266_AT_Test() );
    
//    ESP8266_Cmd ( "AT+CIPSERVER=0", "OK", NULL, 5000 );    
    printf( "\r\n禁止多连接 ......\r\n" );
    while( ! ESP8266_Enable_MultipleId ( DISABLE ) );
    
    printf( "\r\n正在配置工作模式 STA ......\r\n" );
    while( ! ESP8266_Net_Mode_Choose ( STA ) );
    //while( ! ESP8266_DHCP_CUR () );
    
    
    printf( "\r\n正在连接 WiFi ......\r\n" );
    while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
    
    //以下使用MQTT AT指令实现连接
    printf( "\r\n正在配置MQTT ......\r\n" );
    while( !ESP8266_MQTT_USERCFG ());
    
    printf( "\r\n正在连接MQTT ......\r\n" );
    while( !ESP8266_MQTT_CONN ());
    
    printf( "\r\n正在订阅MQTT ......\r\n" );
    while( !ESP8266_MQTT_SUB ());
    
    mqtt_flag = 1;//mqtt已连接
    printf( "\r\n配置 ESP8266 完毕\r\n" );
    printf("等待接收MQTT LED控制数据\r\n");
    
}


/**
  * @brief  ESP8266 检查是否接收到了数据，检查连接和掉线重连
  * @param  无
  * @retval 无
  */
void ESP8266_CheckRecvDataTest(void)
{
  uint8_t ucStatus;
  uint16_t i;
  
  /* 如果接收到了串口调试助手的数据 */
	/*
  if(strUSART_Fram_Record.InfBit.FramFinishFlag == 1)
  {
    for(i = 0;i < strUSART_Fram_Record.InfBit.FramLength; i++)
    {
      HAL_UART_Transmit(&huart3, (uint8_t *)&strUSART_Fram_Record.Data_RX_BUF[i], 1, HAL_MAX_DELAY);
    }
    strUSART_Fram_Record .InfBit .FramLength = 0;                                //接收数据长度置零
    strUSART_Fram_Record .InfBit .FramFinishFlag = 0;                            //接收标志置零
    Get_ESP82666_Cmd(strUSART_Fram_Record .Data_RX_BUF);                         //检查一下是不是点灯命令
  }*/
  
  /* 如果接收到了ESP8266的数据 */
  if(strEsp8266_Fram_Record.InfBit.FramFinishFlag)
  {                                                      
    for(i = 0;i < strEsp8266_Fram_Record .InfBit .FramLength; i++)               
    {
       HAL_UART_Transmit(&huart1, (uint8_t *)&strEsp8266_Fram_Record .Data_RX_BUF[i], 1, HAL_MAX_DELAY);
    }
     strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
     strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
     Get_ESP82666_Cmd(strEsp8266_Fram_Record .Data_RX_BUF);                      //检查一下是不是点灯命令
  }
  
  if ( ucTcpClosedFlag )                                             //检测是否失去连接
  {
    ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //确认失去连接后重连
    {
      printf ( "\r\n正在重连热点和服务器 ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      printf ( "\r\n重连热点和服务器成功\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
    
  }
}

void ESP_cmd_test(void)
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
				 printf("8266回复:%s\n",strEsp8266_Fram_Record .Data_RX_BUF);
				 strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
				 strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
			}
			
			
		 if ( ucTcpClosedFlag )                                             //检测是否失去连接
		 {
			ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
			uint8_t ucStatus;
			do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
			while ( ! ucStatus );
			if ( ucStatus == 4 )                                             //确认失去连接后重连
			{
				printf ( "\r\n正在重连热点和服务器 ......\r\n" );
				
				while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
				
				while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
				
				printf ( "\r\n重连热点和服务器成功\r\n" );

			}
			
			while ( ! ESP8266_UnvarnishSend () );		
			
		}
			
}



void ESP8266_SendDHT11DataTest(void)
{
  char cStr [ 100 ] = { 0 };
  uint8_t ucStatus;
  
  sprintf(cStr, "Pi 的值 = %f", 3.1415);
  
  printf ( "%s", cStr );                                             //打印读取 DHT11 温湿度信息

  ESP8266_SendString ( ENABLE, cStr, 0, Single_ID_0 );               //发送 DHT11 温湿度信息到网络调试助手
  
  
  if ( ucTcpClosedFlag )                                             //检测是否失去连接
  {
    ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //确认失去连接后重连
    {
      printf ( "\r\n正在重连热点和服务器 ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      printf ( "\r\n重连热点和服务器成功\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
    
  }
}


