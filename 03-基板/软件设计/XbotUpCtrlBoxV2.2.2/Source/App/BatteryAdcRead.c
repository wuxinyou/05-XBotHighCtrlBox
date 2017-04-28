
#include "BatteryAdcRead.h"

#define BAT_ADC_BUF_LEN	 30

#define BAT_VALUE_MAX	255
#define BAT_VALUE_MIN	1
#define BAT_ADC_RANGE	0x400
#define BAT_VALUE_RANGE	255

uint8_t BAT1_GetValue(void)
{
	static uint16_t BatAdcBuf[BAT_ADC_BUF_LEN];
	static uint8_t BufIndex=0;
	uint32_t BatValueSum=0;
	uint8_t Index=0;

	if(BufIndex<BAT_ADC_BUF_LEN)
		BatAdcBuf[BufIndex++] = BatteryGetAdc1();
	else
		BufIndex = 0;	

	for(Index=0;Index<BAT_ADC_BUF_LEN;Index++)
		BatValueSum+=BatAdcBuf[Index];

		BatValueSum /= BAT_ADC_BUF_LEN;

	BatValueSum *= BAT_VALUE_RANGE;
	BatValueSum /= BAT_ADC_RANGE;	

	if(BatValueSum>BAT_VALUE_MAX)
		BatValueSum=BAT_VALUE_MAX;
	else if(BatValueSum<BAT_VALUE_MIN)
		BatValueSum=BAT_VALUE_MIN;
		
	return (uint8_t)BatValueSum;
}



uint8_t BAT2_GetValue(void)
{
	static uint16_t BatAdcBuf[BAT_ADC_BUF_LEN];
	static uint8_t BufIndex=0;
	uint32_t BatValueSum=0;
	uint8_t Index;
	if(BufIndex<BAT_ADC_BUF_LEN)
		BatAdcBuf[BufIndex++] = (uint16_t)BatteryGetAdc2();
  	else
		BufIndex = 0;	

	for(Index=0;Index<BAT_ADC_BUF_LEN;Index++)
		BatValueSum+=BatAdcBuf[Index];

		BatValueSum /= BAT_ADC_BUF_LEN;

	BatValueSum *= BAT_VALUE_RANGE;
	BatValueSum /= BAT_ADC_RANGE;	

	if(BatValueSum>BAT_VALUE_MAX)
		BatValueSum=BAT_VALUE_MAX;
	else if(BatValueSum<BAT_VALUE_MIN)
		BatValueSum=BAT_VALUE_MIN;
		
	return (uint8_t)BatValueSum;
}



