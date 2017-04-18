#ifndef __STM32_ADC_H
#define __STM32_ADC_H	

#include <stm32f4xx.h>  
#include <stdio.h>

 
#define ADC1_DR_Address  ((uint32_t)0X4001204C)
											 //((uint32_t)0x4001204C);
#define DMABUFFSIZE 1
#define DMABUFFLEN	10
extern void Adc1DmaInit(void);
extern void StartAdcConvert(void);
extern int16_t getADCValue(void);
#endif


