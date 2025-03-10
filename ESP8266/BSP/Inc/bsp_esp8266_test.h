#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f1xx_hal.h"



/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "jzx_mate40"                //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "jzx213212246"           //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP                 "192.168.43.49"      //要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port               "8000"               //要连接的服务器的端口


/********************************** MQTT设置的参数**********************************/

#define MQTT_BROKERADDRESS "a1AmmW4kqUJ.iot-as-mqtt.cn-shanghai.aliyuncs.com"   //服务器域名

#define MQTT_CLIENT_ID  "a1AmmW4kqUJ.mqtt_stm32|securemode=2\\,signmethod=hmacsha256\\,timestamp=1741593800897|"  //客户编号
#define MQTT_USER_NAME  "mqtt_stm32&a1AmmW4kqUJ"                                //用户名
#define MQTT_PASSWD     "02aac334108aa9cfef75b050a4173b3fb4f04e6ec991f4c010f559678ebf6aed"              //用户密码
#define MQTT_SUBSCRIBE_TOPIC  "/sys/a1AmmW4kqUJ/mqtt_stm32/thing/service/property/set"    //订阅主题
#define MQTT_PUBLISH_TOPIC    "/sys/a1AmmW4kqUJ/mqtt_stm32/thing/event/property/post"     //消息发布


/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** 测试函数声明 ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_StaMQTTClient_Unvarnish_ConfigTest(void);
void ESP8266_CheckRecvDataTest(void);
void Get_ESP82666_Cmd( char * cmd);

void ESP8266_SendDHT11DataTest(void);
void ESP_cmd_test(void);

#endif

