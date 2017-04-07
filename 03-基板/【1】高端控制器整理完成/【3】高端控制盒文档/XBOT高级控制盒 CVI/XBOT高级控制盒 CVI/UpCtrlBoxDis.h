/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2013. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  CTDIS                           1
#define  CTDIS_J2                        2
#define  CTDIS_J1                        3
#define  CTDIS_I2                        4
#define  CTDIS_FM                        5
#define  CTDIS_EM                        6
#define  CTDIS_B6                        7
#define  CTDIS_I1                        8
#define  CTDIS_M4                        9
#define  CTDIS_M3                        10
#define  CTDIS_M2                        11
#define  CTDIS_JK_LeftY                  12
#define  CTDIS_JK_LeftX                  13
#define  CTDIS_JK_RightY                 14
#define  CTDIS_JK_RightX                 15
#define  CTDIS_ComStart                  16      /* callback function: ComStartCallback */
#define  CTDIS_ComNum                    17
#define  CTDIS_ComBaudRate               18
#define  CTDIS_TOGGLEBUTTON_2            19
#define  CTDIS_ER                        20
#define  CTDIS_ED                        21
#define  CTDIS_EL                        22
#define  CTDIS_EU                        23
#define  CTDIS_H5                        24
#define  CTDIS_H4                        25
#define  CTDIS_H3                        26
#define  CTDIS_H2                        27
#define  CTDIS_B8                        28
#define  CTDIS_B7                        29
#define  CTDIS_H1                        30
#define  CTDIS_B5                        31
#define  CTDIS_A2                        32
#define  CTDIS_A8                        33
#define  CTDIS_B2                        34
#define  CTDIS_B4                        35
#define  CTDIS_B3                        36
#define  CTDIS_A3                        37
#define  CTDIS_A5                        38
#define  CTDIS_A6                        39
#define  CTDIS_B1                        40
#define  CTDIS_A4                        41
#define  CTDIS_A1                        42
#define  CTDIS_A7                        43
#define  CTDIS_FR                        44
#define  CTDIS_FD                        45
#define  CTDIS_FL                        46
#define  CTDIS_FU                        47
#define  CTDIS_TIMER                     48      /* callback function: Tim1Callback */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK ComStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tim1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
