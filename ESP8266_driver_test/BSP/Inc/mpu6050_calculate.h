#ifndef MPU6050_CAL_H
#define MPU6050_CAL_H

extern short accData[3];
extern short gyroData[3];

extern float g_fAccAngle;
extern float g_fGyroAngleSpeed;
extern float g_fCarAngle;

extern float x_fAcc,y_fAcc,z_fAcc;
static float dt = 0.005;

float ComplementaryFilter(float acc, float gyro, float dt); 
void GetMpuData(void);//获取MPU-6050数据函数
void GetMpuData_IT(void);//获取MPU-6050数据函数

void AngleCalculate(void);


#endif




