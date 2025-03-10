#include "mpu6050_driver.h"
#include "delay.h"
#include "stdio.h"

//野火代码

#define I2C_Handle hi2c1

#define I2Cx_FLAG_TIMEOUT             ((uint32_t) 1000) //0x1100
#define I2Cx_LONG_TIMEOUT             ((uint32_t) (300 * I2Cx_FLAG_TIMEOUT)) //was300

int Sensors_I2C_WriteRegister(unsigned char slave_addr,
                                        unsigned char reg_addr,
                                        unsigned short len, 
                                        unsigned char *data_ptr)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&I2C_Handle, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT,data_ptr, len,I2Cx_FLAG_TIMEOUT); 
	/* 检查通讯状态 */
	if(status != HAL_OK)
	{
		/* 总线出错处理 */
		printf("slave_addr %d",slave_addr);
	}
	while (HAL_I2C_GetState(&I2C_Handle) != HAL_I2C_STATE_READY)
	{
		
	}
	/* 检查SENSOR是否就绪进行下一次读写操作 */
	while (HAL_I2C_IsDeviceReady(&I2C_Handle, slave_addr, I2Cx_FLAG_TIMEOUT, I2Cx_FLAG_TIMEOUT) == HAL_TIMEOUT);
	/* 等待传输结束 */
	while (HAL_I2C_GetState(&I2C_Handle) != HAL_I2C_STATE_READY)
	{
		
	}
	return status;
}

/**
  * @brief  读寄存器，这是提供给上层的接口
	* @param  slave_addr: 从机地址
	* @param 	reg_addr:寄存器地址
	* @param len：要读取的长度
	*	@param data_ptr:指向要存储数据的指针
  * @retval 正常为0，不正常为非0
  */
int Sensors_I2C_ReadRegister(unsigned char slave_addr,
                                       unsigned char reg_addr,
                                       unsigned short len, 
                                       unsigned char *data_ptr)
{
	HAL_StatusTypeDef status = HAL_OK;
	status =HAL_I2C_Mem_Read(&I2C_Handle,slave_addr,reg_addr,I2C_MEMADD_SIZE_8BIT,data_ptr,len,I2Cx_FLAG_TIMEOUT);    
	/* 检查通讯状态 */
	if(status != HAL_OK)
	{
		/* 总线出错处理 */
		printf("slave_addr %d",slave_addr);
	}
	while (HAL_I2C_GetState(&I2C_Handle) != HAL_I2C_STATE_READY)
	{
		
	}
	/* 检查SENSOR是否就绪进行下一次读写操作 */
	while (HAL_I2C_IsDeviceReady(&I2C_Handle, slave_addr, I2Cx_FLAG_TIMEOUT, I2Cx_FLAG_TIMEOUT) == HAL_TIMEOUT);
	/* 等待传输结束 */
	while (HAL_I2C_GetState(&I2C_Handle) != HAL_I2C_STATE_READY)
	{
		
	}
	return status;
}

#define MPU_ERROR 		I2C_ERROR
#define MPU_INFO 		I2C_INFO
/**
  * @brief   写数据到MPU6050寄存器
  * @param   reg_add:寄存器地址
	* @param	 reg_data:要写入的数据
  * @retval  
  */
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat)
{
	Sensors_I2C_WriteRegister(MPU6050_ADDRESS,reg_add,1,&reg_dat);
}

/**
  * @brief   从MPU6050寄存器读取数据
  * @param   reg_add:寄存器地址
	* @param	 Read：存储数据的缓冲区
	* @param	 num：要读取的数据量
  * @retval  
  */
void MPU6050_ReadData(uint8_t reg_add,unsigned char* Read,uint8_t num)
{
	Sensors_I2C_ReadRegister(MPU6050_ADDRESS,reg_add,num,Read);
}


/**
  * @brief   初始化MPU6050芯片
  * @param   
  * @retval  
  */
void MPU6050_Init(void)
{
	//在初始化之前要延时一段时间，若没有延时，则断电后再上电数据可能会出错
	delay_ms(100);
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	    //解除休眠状态
	MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //陀螺仪采样率
	MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);	  //配置加速度传感器工作在16G模式
	MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	delay_ms(200);
}

/**
  * @brief   读取MPU6050的ID
  * @param   
  * @retval  正常返回1，异常返回0
  */
uint8_t MPU6050ReadID(void)
{
	unsigned char Re = 0;
  MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //读器件地址
	printf("reading MPU6050: \t");
	printf("Re = %u\n",Re);
	if(Re != (MPU6050_ADDRESS>>1))
	{
		printf("MPU6050 dectected error! can't find Mpu6050\n");
		return 0;
	}
	else
	{
		printf("MPU6050 ID = %d\r\n",Re);
		return 1;
	}
		
}

/**
  * @brief   读取MPU6050的加速度数据
  * @param   
  * @retval  
  */
void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

/**
  * @brief   读取MPU6050的角加速度数据
  * @param   
  * @retval  
  */
void  MPU6050ReadGyro(short *gyroData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

/**
  * @brief   读取MPU6050的原始温度数据
  * @param   
  * @retval  
  */
void MPU6050ReadTemp(short *tempData)
{
	uint8_t buf[2];
    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
    *tempData = (buf[0] << 8) | buf[1];
}

/**
  * @brief   读取MPU6050的温度数据，转化成摄氏度
  * @param   
  * @retval  
  */
void MPU6050_ReturnTemp(float *Temperature)
{
	short temp3;
	uint8_t buf[2];
	
	MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
    temp3= (buf[0] << 8) | buf[1];	
	*Temperature=((float) temp3/340.0)+36.53;

}






/*
void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    // 唤醒MPU6050
    data = 0;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);

    // 设置采样率
    data = 0x07;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, SMPLRT_DIV, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);

    // 配置陀螺仪和加速度计
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);

    // 配置陀螺仪量程
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);

    // 配置加速度计量程
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);

    // 使能中断
    data = 0x01;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, INT_ENABLE, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
}

void MPU6050_ReadAccel(I2C_HandleTypeDef *hi2c, int16_t *ax, int16_t *ay, int16_t *az)
{
    uint8_t buffer[6];

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, buffer, 6, 100);

    *ax = (int16_t)((buffer[0] << 8) | buffer[1]);
    *ay = (int16_t)((buffer[2] << 8) | buffer[3]);
    *az = (int16_t)((buffer[4] << 8) | buffer[5]);
}


void MPU6050_ReadGyro(I2C_HandleTypeDef *hi2c, int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t buffer[6];

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT, buffer, 6, 100);

    *gx = (int16_t)((buffer[0] << 8) | buffer[1]);
    *gy = (int16_t)((buffer[2] << 8) | buffer[3]);
    *gz = (int16_t)((buffer[4] << 8) | buffer[5]);
}

*/


