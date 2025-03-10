本项目使用STM32C8T6+esp8266

通过python上位机使用socket TCP协议进行连接

使用pyautogui,PILLOW库进行截屏和图像处理

之后上位机将截屏发送给esp8266,esp8266通过spi将图片传递给stm32c8t6,stm32c8t6通过ST7735S显示图片

由于stm32c8t6资源有限,传递40x40的图片不会超过栈内存分配

所以图片很小,通过插值放大算法进行模糊放大




 
