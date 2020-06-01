/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name ：Debug 调试系统
*  File Name   ：debug.c
*  Description ：进行log调试
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

#ifndef	DEBUG_H
#define	DEBUG_H

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "hc32_ddl.h"
#include "bsp_uart.h"

#include "stdio.h"
#include "stdarg.h"
#include "string.h"
/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/

/***************************************************************************
* Macros                               宏定义
***************************************************************************/

#define ALL_LOG_OPEN	0xFFFF
#define	ALL_LOG_CLOSE	0x0000

#define WDT_LOG_ID		(0x0001 << 0)
#define AT_LOG_ID		(0x0001 << 1)
#define PWC_LOG_ID		(0x0001 << 2)
#define ADC_LOG_ID		(0x0001 << 3)
#define RTC_LOG_ID		(0x0001 << 4)

#define MAX_NAME_LEN	10

#define WDT_LOG_NAME	"WDT"
#define AT_LOG_NAME		"AT"
#define PWC_LOG_NAME	"PWC"
#define ADC_LOG_NAME	"ADC"
#define RTC_LOG_NAME	"RTC"

typedef struct
{
	uint16_t ID;
	char *NAME;
}MODULELOG;


#ifdef WDT_LOG_ID
#define	LOGWDT(...)	Write_Log_From_ID(WDT_LOG_ID, __VA_ARGS__)
#else
#define	LOGWDT(...)
#endif

#ifdef AT_LOG_ID
#define	LOGAT(...)	Write_Log_From_ID(AT_LOG_ID, __VA_ARGS__)
#else
#define	LOGWDT(...)
#endif

#ifdef PWC_LOG_ID
#define	LOGPWC(...)	Write_Log_From_ID(PWC_LOG_ID, __VA_ARGS__)
#else
#define	LOGWDT(...)
#endif

#ifdef ADC_LOG_ID
#define	LOGADC(...)	Write_Log_From_ID(ADC_LOG_ID, __VA_ARGS__)
#else
#define	LOGWDT(...)
#endif

#ifdef RTC_LOG_ID
#define	LOGRTC(...)	Write_Log_From_ID(RTC_LOG_ID, __VA_ARGS__)
#else
#define	LOGWDT(...)
#endif

/***************************************************************************
* Types                             全局类型定义
***************************************************************************/


/***************************************************************************
* Function Declare                  全局函数声明
***************************************************************************/

void Write_Log_ID(uint16_t Log_ID);
void Write_Log_From_ID(uint16_t Log_ID, char* fmt, ...);

#endif  /* DEBUG_H */

