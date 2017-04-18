/*******************************************************Copyright*********************************************************
**                                            北京博创兴盛机器人技术有限公司
**                                                       研发部
**                                               http://robot.up-tech.com
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			AdcInit.c
** 最后修订日期:  	2010-04-21
** 最后版本:			1.0
** 描述:				ADC初始化
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:			律晔
** 创建日期:			2010-04-21
** 版本:				1.0
** 描述:				ADC初始化
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
*************************************************************************************************************************/
#include "Apps/AdcControl.h"


/*************************************************************************************************************************
** 函数名称:			InitAdcA
**
** 函数描述:			初始化InitAdcA，启动溢出中断，中断周期为1ms;
**
**
** 输入变量:			void;
** 返回值:			void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:			律晔
** 创建日期:			2010-04-12
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitAdcA(void)
{
	/* Move stored calibration values to ADC A. */
	ADC_CalibrationValues_Load(&ADCA);

	/* Set up ADC A to have signed conversion mode and 12 bit resolution. */
  	ADC_ConvMode_and_Resolution_Config(&ADCA, ADC_ConvMode_Unsigned, ADC_RESOLUTION_12BIT_gc);

	/* Set sample rate */
	ADC_Prescaler_Config(&ADCA, ADC_PRESCALER_DIV512_gc);

	/* Set referance voltage on ADC A to be VCC/1.6 V.*/
	ADC_Reference_Config(&ADCA, ADC_REFSEL_VCC_gc);

   	/* Get offset value for ADC A. */
	ADC_Ch_InputMode_and_Gain_Config(&ADCA.CH0,
	                                 ADC_CH_INPUTMODE_DIFF_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

   	ADC_Ch_InputMux_Config(&ADCA.CH0, ADC_CH_MUXPOS_PIN1_gc, ADC_CH_MUXNEG_PIN1_gc);

	ADC_Enable(&ADCA);
	/* Wait until common mode voltage is stable. Default clk is 2MHz and
	 * therefore below the maximum frequency to use this function. */
	ADC_Wait_32MHz(&ADCA);
	adc_a_control.offset = ADC_Offset_Get_Signed(&ADCA, &ADCA.CH0, false);
    ADC_Disable(&ADCA);

	/* Setup channel 0, 1, 2 and 3 to have single ended input. */
	ADC_Ch_InputMode_and_Gain_Config(&ADCA.CH0,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCA.CH1,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCA.CH2,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCA.CH3,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCA.CH0,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	/* Set input to the channels in ADC A to be PIN 4, 5, 6 and 7. */
	ADC_Ch_InputMux_Config(&ADCA.CH0, ADC_CH_MUXPOS_PIN0_gc, 0);
	ADC_Ch_InputMux_Config(&ADCA.CH1, ADC_CH_MUXPOS_PIN1_gc, 0);
	ADC_Ch_InputMux_Config(&ADCA.CH2, ADC_CH_MUXPOS_PIN2_gc, 0);
	ADC_Ch_InputMux_Config(&ADCA.CH3, ADC_CH_MUXPOS_PIN3_gc, 0);

	/* Setup sweep of all four virtual channels.*/
	ADC_SweepChannels_Config(&ADCA, ADC_SWEEP_0123_gc);

	/* Enable low level interrupts on ADCA channel 3, on conversion complete. */
	ADC_Ch_Interrupts_Config(&ADCA.CH3, ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_MED_gc);

//	/* Enable PMIC interrupt level low. */
//	PMIC.CTRL |= PMIC_LOLVLEX_bm;
//
//	/* Enable global interrupts. */
//	sei();
}


/*************************************************************************************************************************
** 函数名称:			InitAdcB
**
** 函数描述:			初始化InitAdcB，启动溢出中断，中断周期为1ms;
**
**
** 输入变量:			void;
** 返回值:			void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:			律晔
** 创建日期:			2010-04-12
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitAdcB(void)
{
	/* Move stored calibration values to ADC B. */
	ADC_CalibrationValues_Load(&ADCB);

	/* Set up ADC A to have signed conversion mode and 12 bit resolution. */
  	ADC_ConvMode_and_Resolution_Config(&ADCB, ADC_ConvMode_Unsigned, ADC_RESOLUTION_12BIT_gc);

	/* Set sample rate */
	ADC_Prescaler_Config(&ADCB, ADC_PRESCALER_DIV512_gc);

	/* Set referance voltage on ADC A to be VCC/1.6 V.*/
	ADC_Reference_Config(&ADCB, ADC_REFSEL_VCC_gc);	//ADC_REFSEL_INT1V_gc

   	/* Get offset value for ADC A. */
	ADC_Ch_InputMode_and_Gain_Config(&ADCB.CH0,
	                                 ADC_CH_INPUTMODE_DIFF_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

   	ADC_Ch_InputMux_Config(&ADCB.CH0, ADC_CH_MUXPOS_PIN1_gc, ADC_CH_MUXNEG_PIN1_gc);

	ADC_Enable(&ADCB);
	/* Wait until common mode voltage is stable. Default clk is 2MHz and
	 * therefore below the maximum frequency to use this function. */
	ADC_Wait_32MHz(&ADCB);
	adc_a_control.offset_b = ADC_Offset_Get_Signed(&ADCB, &ADCB.CH0, false);
    ADC_Disable(&ADCB);

	/* Setup channel 0, 1, 2 and 3 to have single ended input. */
	ADC_Ch_InputMode_and_Gain_Config(&ADCB.CH0,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCB.CH1,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCB.CH2,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCB.CH3,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	ADC_Ch_InputMode_and_Gain_Config(&ADCB.CH0,
	                                 ADC_CH_INPUTMODE_SINGLEENDED_gc,
	                                 ADC_DRIVER_CH_GAIN_NONE);

	/* Set input to the channels in ADC A to be PIN 4, 5, 6 and 7. */
	ADC_Ch_InputMux_Config(&ADCB.CH0, ADC_CH_MUXPOS_PIN0_gc, 0);
	ADC_Ch_InputMux_Config(&ADCB.CH1, ADC_CH_MUXPOS_PIN1_gc, 0);
	ADC_Ch_InputMux_Config(&ADCB.CH2, ADC_CH_MUXPOS_PIN2_gc, 0);
	ADC_Ch_InputMux_Config(&ADCB.CH3, ADC_CH_MUXPOS_PIN3_gc, 0);

	/* Setup sweep of all four virtual channels.*/
	ADC_SweepChannels_Config(&ADCB, ADC_SWEEP_0123_gc);

	/* Enable low level interrupts on ADCA channel 3, on conversion complete. */
	ADC_Ch_Interrupts_Config(&ADCB.CH3, ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_MED_gc);

//	/* Enable PMIC interrupt level low. */
//	PMIC.CTRL |= PMIC_LOLVLEX_bm;
//
//	/* Enable global interrupts. */
//	sei();
}



/*************************************************************************************************************************
** 函数名称:			StartAdc
**
** 函数描述:			开始一次AD转换
**
**
** 输入变量:			void;
** 返回值:			void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数			ClrRegBit;
**
** 创建人:			律晔
** 创建日期:			2010-04-13
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
static void StartAdc(void)
{
	/* Enable ADC A with free running mode, VCC reference and signed conversion.*/
	ADC_Enable(&ADCA);

	/* Wait until common mode voltage is stable. Default clock is 2MHz and
	 * therefore below the maximum frequency to use this function. */
	ADC_Wait_32MHz(&ADCA);

	/* Enable free running mode. */
	ADC_FreeRunning_Enable(&ADCA);
}






/*! Interrupt routine that reads out the result form the conversion on all
 *  channels to a global array. If the number of conversions carried out is less
 *  than the number given in the define SAMPLE_COUNT a new conversion on all the
 *  channels is started. If not the interrupt on ADC A channel 3 is disabled.
 *
 */

ISR(ADCA_CH3_vect)
{
	//PORTD.OUTTGL  = PIN5_bm;

	ADC_FreeRunning_Disable(&ADCA);

	ADC_Disable(&ADCA);

	/*  Read samples and clear interrupt flags. */
	if (0 == adc_a_control.group)
	{
		adc_a_control.ad0 = ADC_ResultCh_GetWord_Signed(&ADCA.CH0, adc_a_control.offset);
		adc_a_control.ad1 = ADC_ResultCh_GetWord_Signed(&ADCA.CH1, adc_a_control.offset);
		adc_a_control.ad2 = ADC_ResultCh_GetWord_Signed(&ADCA.CH2, adc_a_control.offset);
		adc_a_control.ad3 = ADC_ResultCh_GetWord_Signed(&ADCA.CH3, adc_a_control.offset);

		/* Set input to the channels in ADC A to be PIN 4, 5, 6 and 7. */
		ADC_Ch_InputMux_Config(&ADCA.CH0, ADC_CH_MUXPOS_PIN4_gc, 0);
		ADC_Ch_InputMux_Config(&ADCA.CH1, ADC_CH_MUXPOS_PIN5_gc, 0);
		ADC_Ch_InputMux_Config(&ADCA.CH2, ADC_CH_MUXPOS_PIN6_gc, 0);
		ADC_Ch_InputMux_Config(&ADCA.CH3, ADC_CH_MUXPOS_PIN7_gc, 0);

		adc_a_control.group = 1;

		ADC_Enable(&ADCA);

		ADC_Wait_32MHz(&ADCA);

		ADC_FreeRunning_Enable(&ADCA);
	}
	else if(1 == adc_a_control.group)
	{
		adc_a_control.ad4 = ADC_ResultCh_GetWord_Signed(&ADCA.CH0, adc_a_control.offset);
		adc_a_control.ad5 = ADC_ResultCh_GetWord_Signed(&ADCA.CH1, adc_a_control.offset);
		adc_a_control.ad6 = ADC_ResultCh_GetWord_Signed(&ADCA.CH2, adc_a_control.offset);
		adc_a_control.ad7 = ADC_ResultCh_GetWord_Signed(&ADCA.CH3, adc_a_control.offset);

		/* Set input to the channels in ADC A to be PIN 4, 5, 6 and 7. */
		ADC_Ch_InputMux_Config(&ADCA.CH0, ADC_CH_MUXPOS_PIN0_gc, 0);
		ADC_Ch_InputMux_Config(&ADCA.CH1, ADC_CH_MUXPOS_PIN1_gc, 0);
		ADC_Ch_InputMux_Config(&ADCA.CH2, ADC_CH_MUXPOS_PIN2_gc, 0);
		ADC_Ch_InputMux_Config(&ADCA.CH3, ADC_CH_MUXPOS_PIN3_gc, 0);

		adc_a_control.group = 0;

		/* Enable ADC A with free running mode, VCC reference and signed conversion.*/
		ADC_Enable(&ADCB);

		/* Wait until common mode voltage is stable. Default clock is 2MHz and
		 * therefore below the maximum frequency to use this function. */
		ADC_Wait_32MHz(&ADCB);

		/* Enable free running mode. */
		ADC_FreeRunning_Enable(&ADCB);
	}
}


ISR(ADCB_CH3_vect)
{
	//PORTD.OUTTGL  = PIN5_bm;

	ADC_FreeRunning_Disable(&ADCB);

	ADC_Disable(&ADCB);

	/*  Read samples and clear interrupt flags. */
	adc_a_control.adb0 = ADC_ResultCh_GetWord_Signed(&ADCB.CH0, adc_a_control.offset_b);
	adc_a_control.adb1 = ADC_ResultCh_GetWord_Signed(&ADCB.CH1, adc_a_control.offset_b);
	adc_a_control.adb2 = ADC_ResultCh_GetWord_Signed(&ADCB.CH2, adc_a_control.offset_b);
	adc_a_control.adb3 = ADC_ResultCh_GetWord_Signed(&ADCB.CH3, adc_a_control.offset_b);

	/* Set input to the channels in ADC A to be PIN 4, 5, 6 and 7. */
}

/*************************************************************************************************************************
**														结构体声明
*************************************************************************************************************************/
ADC_CONTROL_STRUCT adc_a_control =
{

	.pStart = StartAdc,

	.report_cycle = 100,
	.time_count = 30,

	.group = 0,
};

/*************************************************************************************************************************
**                                                      文件结束
*************************************************************************************************************************/
