/*****************************************************************************
* 1
*
*  Module Name ：电源管理相关驱动
*  File Name   ：bsp_pwr.c
*  Description ：提供电源管理相关驱动
*  Author      ：maheng
*  Version     ：
*  Data        ：2020-05-27
*  Others      ：
*  Revision Details1：
*  Modify Data：
*  Version：
*  Author：
*  Modification：
*  Revision Details2：
*****************************************************************************/

#ifndef	BSP_PWR_H
#define	BSP_PWR_H

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "hc32_ddl.h"
#include "bsp_uart.h"

#include "debug.h"

/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/


/***************************************************************************
* Macros                               宏定义
***************************************************************************/

/***************************************************************************
* Types                             全局类型定义
***************************************************************************/


/***************************************************************************
* Function Declare                  全局函数声明
***************************************************************************/
void SystemClkInit(void);

void Enter_Stop_Mode(void);

void Set_Wakeup_Time(uint16_t Wakeup_Time);

#endif  /* BSP_PWR_H */

