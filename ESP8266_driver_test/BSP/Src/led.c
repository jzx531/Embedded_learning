#include "led.h"
#include "delay.h"
void LED_toggle(void)
{
	LED_ON;
	delay_ms(1000);
	LED_OFF;
	delay_ms(1000);
}