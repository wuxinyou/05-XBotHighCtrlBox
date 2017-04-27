#ifndef __KEY_READ_H
#define __KEY_READ_H	
#include "stm32f10x.h"

#define KEYNUM	40
#define	KEY_MAX_TIMER	10

//******************* A系列开关*************************
#define __KEY_A1_PIN		GPIO_Pin_9			//开关A1
#define __KEY_A2_PIN		GPIO_Pin_8			//开关A2
#define __KEY_A3_PIN		GPIO_Pin_7 	    	//开关A3
#define __KEY_A4_PIN		GPIO_Pin_6		  	//开关A4
#define __KEY_A5_PIN		GPIO_Pin_5		   	//开关A5
#define __KEY_A6_PIN 		GPIO_Pin_7		  	//开关A6
#define __KEY_A7_PIN 		GPIO_Pin_4		  	//开关A7
#define __KEY_A8_PIN 		GPIO_Pin_3		  	//开关A8

//******************* B系列开关*************************
#define __KEY_B1_PIN		GPIO_Pin_10			//开关B1
#define __KEY_B2_PIN		GPIO_Pin_11			//开关B2
#define __KEY_B3_PIN		GPIO_Pin_12 		//开关B3
#define __KEY_B4_PIN		GPIO_Pin_13		  	//开关B4
#define __KEY_B5_PIN		GPIO_Pin_14		   	//开关B5
#define __KEY_B6_PIN 		GPIO_Pin_15		  	//开关B6
#define __KEY_B7_PIN 		GPIO_Pin_10		  	//开关B7
#define __KEY_B8_PIN 		GPIO_Pin_11		  	//开关B8

//******************* E系列开关*************************
#define __KEY_EU_PIN		GPIO_Pin_1			//开关A1
#define __KEY_ED_PIN		GPIO_Pin_14			//开关A2
#define __KEY_EL_PIN		GPIO_Pin_13 	    	//开关A3
#define __KEY_ER_PIN		GPIO_Pin_0		  	//开关A4
#define __KEY_EM_PIN		GPIO_Pin_15		   	//开关A5

//******************* F系列开关*************************
#define __KEY_FU_PIN		GPIO_Pin_4			//开关A1
#define __KEY_FD_PIN		GPIO_Pin_4			//开关A2
#define __KEY_FL_PIN		GPIO_Pin_7 	    	//开关A3
#define __KEY_FR_PIN		GPIO_Pin_5		  	//开关A4
#define __KEY_FM_PIN		GPIO_Pin_6		   	//开关A5

//******************* H系列开关*************************
#define __KEY_H1_PIN		GPIO_Pin_5			//开关A1
#define __KEY_H2_PIN		GPIO_Pin_0			//开关A2
#define __KEY_H3_PIN		GPIO_Pin_1 		    //开关A3
#define __KEY_H4_PIN		GPIO_Pin_7		  	//开关A4
#define __KEY_H5_PIN		GPIO_Pin_8		   	//开关A5

//******************* IJ系列开关*************************
#define __KEY_I1_PIN 		GPIO_Pin_3		  	//开关A6
#define __KEY_I2_PIN 		GPIO_Pin_4		  	//开关A7
#define __KEY_J1_PIN 		GPIO_Pin_5		  	//开关A8
#define __KEY_J2_PIN		GPIO_Pin_6			//开关A1

//******************* M系列开关*************************
#define __KEY_M2_PIN		GPIO_Pin_0			//开关M2
#define __KEY_M3_PIN		GPIO_Pin_1 		    //开关M3
#define __KEY_M4_PIN		GPIO_Pin_2		  	//开关M4

//******************* G系列开关*************************
#define __KEY_G1_PIN		GPIO_Pin_6		   	//开关G1
#define __KEY_G2_PIN 		GPIO_Pin_7		  	//开关G2



//*****************************************端口号设置**********************************//

//******************* A系列开关*************************
#define __KEY_A1_PORT		GPIOB			//开关A1
#define __KEY_A2_PORT		GPIOB			//开关A2
#define __KEY_A3_PORT		GPIOB 			//开关A3
#define __KEY_A4_PORT		GPIOB		  	//开关A4
#define __KEY_A5_PORT		GPIOB		   	//开关A5
#define __KEY_A6_PORT 		GPIOD		  	//开关A6
#define __KEY_A7_PORT 		GPIOD		  	//开关A7
#define __KEY_A8_PORT 		GPIOD		  	//开关A8

//******************* B系列开关*************************
#define __KEY_B1_PORT		GPIOE			//开关B1
#define __KEY_B2_PORT		GPIOE			//开关B2
#define __KEY_B3_PORT		GPIOE 			//开关B3
#define __KEY_B4_PORT		GPIOE		  	//开关B4
#define __KEY_B5_PORT		GPIOE		   	//开关B5
#define __KEY_B6_PORT 		GPIOE		  	//开关B6
#define __KEY_B7_PORT 		GPIOB		  	//开关B7
#define __KEY_B8_PORT 		GPIOB		  	//开关B8

//******************* E系列开关*************************
#define __KEY_EU_PORT		GPIOD			//开关A1
#define __KEY_ED_PORT		GPIOD			//开关A2
#define __KEY_EL_PORT		GPIOD 			//开关A3
#define __KEY_ER_PORT		GPIOD		  	//开关A4
#define __KEY_EM_PORT		GPIOD		   	//开关A5

//******************* F系列开关*************************
#define __KEY_FU_PORT		GPIOA			//开关A1
#define __KEY_FD_PORT		GPIOC			//开关A2
#define __KEY_FL_PORT		GPIOA 			//开关A3
#define __KEY_FR_PORT		GPIOA		  	//开关A4
#define __KEY_FM_PORT		GPIOA		   	//开关A5

//******************* H系列开关*************************
#define __KEY_H1_PORT		GPIOC			//开关A1
#define __KEY_H2_PORT		GPIOB			//开关A2
#define __KEY_H3_PORT		GPIOB 			//开关A3
#define __KEY_H4_PORT		GPIOE		  	//开关A4
#define __KEY_H5_PORT		GPIOE		   	//开关A5

//******************* IJ系列开关*************************
#define __KEY_I1_PORT 		GPIOE		  	//开关A6
#define __KEY_I2_PORT 		GPIOE		  	//开关A7
#define __KEY_J1_PORT 		GPIOE		  	//开关A8
#define __KEY_J2_PORT		GPIOE			//开关A1

//******************* M系列开关*************************
#define __KEY_M2_PORT		GPIOE			//开关M2
#define __KEY_M3_PORT		GPIOE 			//开关M3
#define __KEY_M4_PORT		GPIOE		  	//开关M4

//******************* G系列开关*************************
#define __KEY_G1_PORT		GPIOC		   	//开关G1
#define __KEY_G2_PORT 		GPIOC		  	//开关G2

#define KEY_PRESS_NULL	0X00
#define KEY_PRESS_DOWN	0X01
#define KEY_RRESS_UP	0X02
#define KEY_SELECT	  	0X03
#define KEY_UNSELECT	0X04


typedef struct S_KEYDATA_STRUCT
{
	uint16_t KEY_Pin;
	GPIO_TypeDef* KEY_PORT;
	uint8_t TimerTick;
	uint8_t PreState;		//表示前一时刻按键状态,默认情况下没有按键按下
	uint8_t NowState;		//定义一个中间变量，起到传参的作用
	uint8_t TimerTickMax;

}KEYDATA_STRUCT;


#define	KEY_A1	0
#define	KEY_A2	1
#define	KEY_A3	2
#define	KEY_A4	3
#define	KEY_A5	4
#define	KEY_A6	5
#define	KEY_A7	6
#define	KEY_A8	7

#define	KEY_B1	8
#define	KEY_B2	9
#define	KEY_B3	10
#define	KEY_B4	11
#define	KEY_B5	12
#define	KEY_B6	13
#define	KEY_B7	14
#define	KEY_B8	15

#define	KEY_H1	16
#define	KEY_H2	17
#define	KEY_H3	18
#define	KEY_H4	19
#define	KEY_H5	20

#define	KEY_I1	21
#define	KEY_I2	22
#define	KEY_J1	23
#define	KEY_J2	24
#define	KEY_M2	25
#define	KEY_M3	26
#define	KEY_M4	27
#define	KEY_G1	28
#define	KEY_G2	29

#define	KEY_EU	30
#define	KEY_ED	31
#define	KEY_EL	32
#define	KEY_ER	33
#define	KEY_EM	34

#define	KEY_FU	35
#define	KEY_FD	36
#define	KEY_FL	37
#define	KEY_FR	38
#define	KEY_FM	39

extern KEYDATA_STRUCT KEY_DATA[KEYNUM];


extern void KeyRead_Init(void);
extern void KeyAll_OpTask(void);

	  
#endif

