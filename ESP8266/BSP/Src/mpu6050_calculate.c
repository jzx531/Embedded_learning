#include "mpu6050_calculate.h"
#include "mpu6050_driver.h"
#include <cmath>


short accData[3];
short gyroData[3];

float g_fAccAngle;
float g_fGyroAngleSpeed;
float g_fCarAngle;

float x_fAcc,y_fAcc,z_fAcc;

float ComplementaryFilter(float acc, float gyro, float dt) 
{
    static float a = 0.98;  
    float angle = a * (angle + gyro * dt) + (1 - a) * (acc);  
    return angle;  
}

void GetMpuData(void)//获取MPU-6050数据函数
{
     MPU6050ReadAcc(&accData[0]);//获取MPU-6050加速度数据
		 MPU6050ReadGyro(&gyroData[0]); //获取MPU-6050陀螺仪数据
}

void GetMpuData_IT(void)//获取MPU-6050数据函数
{
	uint8_t buf[6];
	HAL_I2C_Mem_Read_IT(&hi2c1,MPU6050_ADDRESS,MPU6050_ACC_OUT,I2C_MEMADD_SIZE_8BIT,buf,6);    
	
}


void AngleCalculate(void)//角度计算函数
{
    //-------加速度数据处理--------------------------
    //量程为±2g时，灵敏度：16384 LSB/g
    x_fAcc = accData[0] / 16384.0;
    y_fAcc = accData[1] / 16384.0;
    z_fAcc = accData[2] / 16384.0;

    g_fAccAngle = atan2(y_fAcc,z_fAcc) / 3.14 * 180.0;

    //-------陀螺仪数据处理-------------------------
    //范围为2000deg/s时，换算关系：16.4 LSB/(deg/s)
    g_fGyroAngleSpeed = gyroData[0] / 16.4;  //计算角速度值                   

    //-------互补滤波---------------
    g_fCarAngle = ComplementaryFilter(g_fAccAngle, g_fGyroAngleSpeed, dt);
}







