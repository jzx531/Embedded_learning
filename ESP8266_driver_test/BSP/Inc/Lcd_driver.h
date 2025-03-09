#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "stm32f1xx_hal.h"


#include "delay.h" 



#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        128


#define LCD_CTRL   	  	  GPIOB		//定义TFT 数据端口

#define LCD_CTRL2   	  	GPIOA		//定义BLK 数据端口

#define LCD_BLK        	GPIO_PIN_8   //PA8--BLK
#define LCD_RS         	GPIO_PIN_1	 //PB1---RS/DC
#define LCD_CS        	GPIO_PIN_12  //PB11---CS/CE

#define LCD_SCL        	GPIO_PIN_13	 //PB13--SCL/SCK
#define LCD_SDA        	GPIO_PIN_15	 //PB15 --SDA/DIN

#define LCD_SDO         GPIO_PIN_14  //PB14----SDO

/*
//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	LCD_CTRL->BSRR=LCD_CS    
#define	LCD_RS_SET  	LCD_CTRL->BSRR=LCD_RS    
#define	LCD_SDA_SET  	LCD_CTRL->BSRR=LCD_SDA    
#define	LCD_SCL_SET  	LCD_CTRL->BSRR=LCD_SCL    
#define	LCD_RST_SET  	LCD_CTRL->BSRR=LCD_RST

#define	LCD_SDO_SET  	LCD_CTRL->BSRR=LCD_SDO

#define	LCD_BLK_SET  	LCD_CTRL2->BSRR=LCD_BLK   

//液晶控制口置0操作语句宏定义
#define	LCD_CS_CLR  	LCD_CTRL->BRR=LCD_CS    
#define	LCD_RS_CLR  	LCD_CTRL->BRR=LCD_RS    
#define	LCD_SDA_CLR  	LCD_CTRL->BRR=LCD_SDA    
#define	LCD_SCL_CLR  	LCD_CTRL->BRR=LCD_SCL    

#define	LCD_SDO_CLR  	LCD_CTRL->BRR=LCD_SDO

#define	LCD_BLK_CLR  	LCD_CTRL2->BRR=LCD_BLK 



#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入
*/



// 控制信号置位/清零操作 
// 主控制端口（GPIOB）
#define LCD_CS_SET     HAL_GPIO_WritePin(LCD_CTRL, LCD_CS, GPIO_PIN_SET)
#define LCD_RS_SET     HAL_GPIO_WritePin(LCD_CTRL, LCD_RS, GPIO_PIN_SET)
#define LCD_SCL_SET    HAL_GPIO_WritePin(LCD_CTRL, LCD_SCL, GPIO_PIN_SET)
#define LCD_SDA_SET    HAL_GPIO_WritePin(LCD_CTRL, LCD_SDA, GPIO_PIN_SET)
#define LCD_SDO_SET    HAL_GPIO_WritePin(LCD_CTRL, LCD_SDO, GPIO_PIN_SET)

#define LCD_CS_CLR     HAL_GPIO_WritePin(LCD_CTRL, LCD_CS, GPIO_PIN_RESET)
#define LCD_RS_CLR     HAL_GPIO_WritePin(LCD_CTRL, LCD_RS, GPIO_PIN_RESET)
#define LCD_SCL_CLR    HAL_GPIO_WritePin(LCD_CTRL, LCD_SCL, GPIO_PIN_RESET)
#define LCD_SDA_CLR    HAL_GPIO_WritePin(LCD_CTRL, LCD_SDA, GPIO_PIN_RESET)
#define LCD_SDO_CLR    HAL_GPIO_WritePin(LCD_CTRL, LCD_SDO, GPIO_PIN_RESET)

// 背光控制（GPIOA）
#define LCD_BLK_SET    HAL_GPIO_WritePin(LCD_CTRL2, LCD_BLK, GPIO_PIN_SET)
#define LCD_BLK_CLR    HAL_GPIO_WritePin(LCD_CTRL2, LCD_BLK, GPIO_PIN_RESET)

// 数据端口操作（假设使用GPIOA的0-7位作为数据线）
#define LCD_DATA_GPIO  GPIOA  // 假设数据端口为GPIOA


// 数据端口操作（保留直接寄存器访问以提高速度）
#define LCD_DATAOUT(x)  (LCD_DATA_GPIO_Port->ODR = (x))  // 输出数据到整个端口
#define LCD_DATAIN      (LCD_DATA_GPIO_Port->IDR)        // 从整个端口读取数据



#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 

#define u8 uint8_t
#define u16 uint16_t

void Lcd_init_2(void);
void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);


#endif


