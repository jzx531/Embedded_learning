#ifndef __BSP_ESP8266_MQTT_H
#define __BSP_ESP8266_MQTT_H

#include "esp_common.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "delay.h"
#include "led.h" 
#include "bsp_esp8266.h"

extern int led_value;//led开关值
extern uint8_t mqtt_flag;//matt连接标志


bool ESP8266_MQTT_USERCFG ( void );
bool ESP8266_MQTT_CONN ( void );
bool ESP8266_MQTT_SUB ( void );
bool ESP8266_MQTT_PUB ( uint8_t temp_set,uint8_t humi_set,uint8_t led_value );
bool ESP8266_MQTT_RECV( void );
bool ESP8266_MQTT_PUB_float ( double data );

#endif /* __BSP_ESP8266_MQTT_H */


