
/* Includes ------------------------------------------------------------------*/

#include "STM32_Adc.h"
#include "STM32_GpioInit.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define ADC1_DR_Address    ((uint32_t)0x4001244C)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint16_t ADC1ConvertedValue[STM32_ADC_CACHEL_M][STM32_ADC_CHANNEL_N];		


/* Private functions ---------------------------------------------------------*/
 /*
  * @brief   初始化ADC1,采用DMA方式
  * @param  None
  * @retval None
  */
void Adc1Dma_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	/* System clocks configuration ---------------------------------------------*/
	{
		/* ADCCLK = PCLK2/4 */		 		//9M Hz
		RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
		
		/* Enable peripheral clocks ------------------------------------------------*/
		/* Enable DMA1 and DMA2 clocks */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2 |RCC_AHBPeriph_DMA2, ENABLE);
		
		/* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_APB2Periph_ADC2 |RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC, ENABLE);
	}
	
	/* GPIO configuration ------------------------------------------------------*/
	{
		STM32_GpioOneInit(GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);   //Bat1_adc
		STM32_GpioOneInit(GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);   //Bat2_adc
		STM32_GpioOneInit(GPIO_Pin_2,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);   //joyStickRightX_adc
		STM32_GpioOneInit(GPIO_Pin_3,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);		//joyStickRightY_adc

		STM32_GpioOneInit(GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOC);   //joyStickLeftX_adc
		STM32_GpioOneInit(GPIO_Pin_2,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOC);   //joyStickLeftY_adc
		
		STM32_GpioOneInit(GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOC);   //swADC

	}
	
	/* DMA1 channel1 configuration ----------------------------------------------*/	
	{
	
	  DMA_DeInit(DMA1_Channel1);
	  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	//外设地址
	  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC1ConvertedValue;		//内存地址
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;			//dma传输方向单向
	  DMA_InitStructure.DMA_BufferSize = STM32_ADC_CHANNEL_N*STM32_ADC_CACHEL_M;	//设置DMA在传输时缓冲区的长度 word
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//设置DMA的外设递增模式，一个外设
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;		//设置DMA的内存递增模式，
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据字长
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//内存数据字长
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;				//设置DMA的传输模式：连续不断的循环模式
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;			//设置DMA的优先级别
	  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;					//设置DMA的2个memory中的变量互相访问
	  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	  

	}
	
	
	/* ADC1 configuration ------------------------------------------------------*/
	{
	 /* ADC1 configuration ------------------------------------------------------*/
	  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//独立工作模式
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;				//扫描方式
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//连续转换
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发禁止
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//数据右对齐
	  ADC_InitStructure.ADC_NbrOfChannel = STM32_ADC_CHANNEL_N;					//用于转换的通道数
	  ADC_Init(ADC1, &ADC_InitStructure);
	
	  /* ADC1 regular channels configuration [规则模式通道配置]*/ 
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_0 , 1, ADC_SampleTime_239Cycles5);  //Bat1_Adc
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_1 , 2, ADC_SampleTime_239Cycles5);  //Bat2_Adc
		
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 3, ADC_SampleTime_239Cycles5);  //JOYSTICK_LEFT_X
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 4, ADC_SampleTime_239Cycles5);  //JOYSTICK_LEFT_Y
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_3 , 5, ADC_SampleTime_239Cycles5);  //JOYSTICK_RIGHT_X
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_2 , 6, ADC_SampleTime_239Cycles5);  //JOYSTICK_RIGHT_Y
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10 , 7, ADC_SampleTime_239Cycles5);   //swAdc
	}
	
	/*  ADC START ---------------------------------------------------------------*/
	{
	  /* Enable ADC1 DMA [使能ADC1 DMA]*/
	  ADC_DMACmd(ADC1, ENABLE);
	  
	  /* Enable ADC1 [使能ADC1]*/
	  ADC_Cmd(ADC1, ENABLE); 
	
	  /* Enable ADC1 reset calibaration register */   
	  ADC_ResetCalibration(ADC1);
	  /* Check the end of ADC1 reset calibration register */
	  while(ADC_GetResetCalibrationStatus(ADC1));
	
	  /* Start ADC1 calibaration */
	  ADC_StartCalibration(ADC1);
	  /* Check the end of ADC1 calibration */
	  while(ADC_GetCalibrationStatus(ADC1));


	  /* Enable DMA1 channel1 */
	  DMA_Cmd(DMA1_Channel1, ENABLE); 	  


	  /* Start ADC1 Software Conversion */
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	}
}

//................均值获得Hb100AdcVaule...............	
uint16_t GetAdcAverageValue(uint16_t (*pAdcVaule)[STM32_ADC_CHANNEL_N],uint8_t AdcIndex,uint8_t DataLen)
{
	uint32_t AdcSum=0;
	uint8_t DataIndex;
	
	for(DataIndex=0;DataIndex<DataLen;DataIndex++)
		AdcSum += pAdcVaule[DataIndex][AdcIndex];
	
	AdcSum /= DataLen;

	return (uint16_t)AdcSum;
		
}
















