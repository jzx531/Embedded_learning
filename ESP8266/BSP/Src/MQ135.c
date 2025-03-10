#include "MQ135.h"
#include "adc.h"
#include <cmath>

ADC_HandleTypeDef ADC_Handle;
ADC_ChannelConfTypeDef ADC_Config;

/**
  * @brief  空气检测模块的GPIO配置
  * @param  无
  * @retval 无
  */
static void MQ135_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //使能 ADC 时钟
    MQ135_ADC_CLK_ENABLE(); 
    // 使能 GPIO 时钟
    MQ135_ADC_GPIO_CLK_ENABLE();
    DO_INPUT_GPIO_CLK_ENABLE();
       
    // 配置 AO IO ——模拟量接收
    GPIO_InitStructure.Pin  = MQ135_ADC_GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    GPIO_InitStructure.Pull = GPIO_NOPULL ; 
    HAL_GPIO_Init(MQ135_ADC_GPIO_PORT, &GPIO_InitStructure);	

    // 配置 DO IO ——数字量接收
    GPIO_InitStructure.Pin  = DO_INPUT_GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;	    
    GPIO_InitStructure.Pull = GPIO_NOPULL ; 
    HAL_GPIO_Init(DO_INPUT_GPIO_PORT, &GPIO_InitStructure);	

}

/**
  * @brief  空气检测模块的ADC配置
  * @param  无
  * @retval 无
  */
static void MQ135_ADC_Mode_Config(void)
{
    RCC_PeriphCLKInitTypeDef ADC_CLKInit;
    // 开启ADC时钟
    ADC_CLKInit.PeriphClockSelection=RCC_PERIPHCLK_ADC;	       //ADC外设时钟
    ADC_CLKInit.AdcClockSelection=RCC_ADCPCLK2_DIV6;           //分频因子6时钟为72M/6=12MHz
    HAL_RCCEx_PeriphCLKConfig(&ADC_CLKInit);                   //设置ADC时钟
   
    ADC_Handle.Instance=MQ135_ADC;
    ADC_Handle.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //右对齐
    ADC_Handle.Init.ScanConvMode=DISABLE;                      //非扫描模式
    ADC_Handle.Init.ContinuousConvMode=ENABLE;                 //连续转换
    ADC_Handle.Init.NbrOfConversion=1;                         //1个转换在规则序列中 也就是只转换规则序列1 
    ADC_Handle.Init.DiscontinuousConvMode=DISABLE;             //禁止不连续采样模式
    ADC_Handle.Init.NbrOfDiscConversion=0;                     //不连续采样通道数为0
    ADC_Handle.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //软件触发
    HAL_ADC_Init(&ADC_Handle);                                 //初始化 
 
  /*---------------------------------------------------------------------------*/
    ADC_Config.Channel      = MQ135_ADC_CHANNEL;
    ADC_Config.Rank         = 1;
    // 采样时间间隔	
    ADC_Config.SamplingTime = ADC_SAMPLETIME_55CYCLES_5 ;
    // 配置 ADC 通道转换顺序为1，第一个转换，采样时间为3个时钟周期
    HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Config);
	/* 执行ADC 自校准 */
    HAL_ADCEx_Calibration_Start(&ADC_Handle);
		
    HAL_ADC_Start_IT(&ADC_Handle);
}

/**
  * @brief  ADC中断配置
  * @param  无
  * @retval 无
  */
static void MQ135_ADC_NVIC_Config(void)
{
    HAL_NVIC_SetPriority(MQ135_ADC_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(MQ135_ADC_IRQ);
}

/**
  * @brief  空气检测模块初始化
  * @param  无
  * @retval 无
  */
void MQ135_Init(void)
{
    MQ135_GPIO_Config();
    MQ135_ADC_Mode_Config();
    MQ135_ADC_NVIC_Config();
}


__IO uint32_t ADC_ConvertedValue;

float vrl = 0;   /* AO输出的模拟电压 */
float Rs;        /* 当前传感器电阻 */
float ppm = 0;   /* 污染物平均浓度 */
/**
  * @brief  求ppm
  * @param  无
  * @retval ppm
  * @note
  * 根据手册提供的各污染气体灵敏度 拟合成幂函数
  * 需要根据Rs/R0推算ppm，所以拟合函数时，x轴为Rs/R0，y轴为ppm，推导出y=ax^b
  * 图表没有每个点对应具体数值只能大致估计，所以测量值存在误差，想要完全精确请根据环境做多次标定
  */
float MQ135_Get_PPM(void)
{
	/* 读取AO输出电压 */
    vrl = (float)ADC_ConvertedValue / 4096 * VC;
    /* 换算Rs电阻 */
    Rs = (float)(VC - vrl) * RL / vrl;
    
    float Rs0 = Rs/R0;  /* Rs/R0 */
    
//    printf("Rs = %0.2f\r\n",Rs);
//    printf("Rs/R0 = %0.2f\r\n",Rs0);

    /* y=ax^b x为Rs/R0，ab的取值根据数据手册图表自行拟合成幂函数 */
    ppm =  A*pow(Rs/R0,B) ;
    
	return ppm;
}
