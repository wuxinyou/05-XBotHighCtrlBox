#include "JoyStickAdcRead.h"

#define JK_ADC_ZERO_MID		0X0830
#define JK_ADC_ZERO_DEAD	0X0080
#define JK_ADC_ZERO_CHECK	0X0200

#define JK_VALUE_MAX	127
#define JK_VALUE_MIN	-128
#define JK_ADC_RANGE	0x800
#define JK_VALUE_RANGE	128

#define JK_ADC_INDEX_MAX 	100		//init_time= (JK_ADC_INDEX_MAX*JK_ADC_TIME_MAX)ms
#define JK_ADC_TIME_MAX 	10		//1 UNIT = 1ms





uint16_t  JK_ADC_ZERO_LX,JK_ADC_ZERO_LY;
uint16_t  JK_ADC_ZERO_RX,JK_ADC_ZERO_RY;



bool JoyStickAdcReadInit(void)
{
	uint32_t JK_LeftAdcX_SUM=0,JK_LeftAdcY_SUM=0;
	uint32_t JK_RightAdcX_SUM=0,JK_RightAdcY_SUM=0;
	uint8_t Index=0;

	SysTick_Delay(JK_ADC_TIME_MAX*10);
/*************** 1S÷”ºÏ≤‚µÁŒª∆˜¡„Œª*********************/
	for(Index=0;Index<JK_ADC_INDEX_MAX;Index++)
	{
		JK_ADC_ZERO_LX = JoyStickGetLeftAdcX();
		JK_ADC_ZERO_LY = JoyStickGetLeftAdcY();
		JK_ADC_ZERO_RX = JoyStickGetRightAdcX();
		JK_ADC_ZERO_RY = JoyStickGetRightAdcY();

		JK_LeftAdcX_SUM  += JK_ADC_ZERO_LX;	
		JK_LeftAdcY_SUM  += JK_ADC_ZERO_LY;
		JK_RightAdcX_SUM += JK_ADC_ZERO_RX;
		JK_RightAdcY_SUM += JK_ADC_ZERO_RY;

		if(JK_ADC_ZERO_LX>(JK_ADC_ZERO_MID+JK_ADC_ZERO_DEAD)
			&&JK_ADC_ZERO_LX<(JK_ADC_ZERO_MID-JK_ADC_ZERO_DEAD))
			break;
		if(JK_ADC_ZERO_LY>(JK_ADC_ZERO_MID+JK_ADC_ZERO_DEAD)
			&&JK_ADC_ZERO_LX<(JK_ADC_ZERO_MID-JK_ADC_ZERO_DEAD))
			break;
		if(JK_ADC_ZERO_RX>(JK_ADC_ZERO_MID+JK_ADC_ZERO_DEAD)
			&&JK_ADC_ZERO_LX<(JK_ADC_ZERO_MID-JK_ADC_ZERO_DEAD))
			break;
		if(JK_ADC_ZERO_RY>(JK_ADC_ZERO_MID+JK_ADC_ZERO_DEAD)
			&&JK_ADC_ZERO_LX<(JK_ADC_ZERO_MID-JK_ADC_ZERO_DEAD))
			break;

		SysTick_Delay(JK_ADC_TIME_MAX);
	}

	if(Index == JK_ADC_INDEX_MAX )
	{
		JK_ADC_ZERO_LX = JK_LeftAdcX_SUM/JK_ADC_INDEX_MAX;
		JK_ADC_ZERO_LY = JK_LeftAdcY_SUM/JK_ADC_INDEX_MAX;
		JK_ADC_ZERO_RX = JK_RightAdcX_SUM/JK_ADC_INDEX_MAX;
		JK_ADC_ZERO_RY = JK_RightAdcY_SUM/JK_ADC_INDEX_MAX;
		return true;

	}
	else
	{
		JK_ADC_ZERO_LX = JK_ADC_ZERO_MID;
		JK_ADC_ZERO_LY = JK_ADC_ZERO_MID;
		JK_ADC_ZERO_RX = JK_ADC_ZERO_MID;
		JK_ADC_ZERO_RY = JK_ADC_ZERO_MID;
		return false;
	}
	
	

}

int8_t JK_GetValue(uint16_t AdcValue,uint16_t AdcZero)
{
	int32_t JkValue;

	JkValue = AdcValue;

	if(JkValue>AdcZero+JK_ADC_ZERO_CHECK)
		JkValue=JkValue-(AdcZero+JK_ADC_ZERO_CHECK);
	else if(JkValue<AdcZero-JK_ADC_ZERO_CHECK)
	 	JkValue=JkValue-(AdcZero-JK_ADC_ZERO_CHECK);
	else
		JkValue = 0;	
	
	JkValue *= JK_VALUE_RANGE;
	JkValue /= JK_ADC_RANGE;
	
	if(JkValue>JK_VALUE_MAX)
		JkValue=JK_VALUE_MAX;
	else if(JkValue<JK_VALUE_MIN)
		JkValue=JK_VALUE_MIN;
	
	
	

	return (int8_t)	JkValue;

}




