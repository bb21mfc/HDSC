/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name ��RTC�������
*  File Name   ��bsp_rtc.c
*  Description ���ṩRTC�������
*  Author      ��maheng
*  Version     ��
*  Data        ��2020-05-29
*  Others      ��
*  Revision Details1��
*  Modify Data��
*  Version��
*  Author��
*  Modification��
*  Revision Details2��
*****************************************************************************/

#ifndef	BSP_RTC_H
#define	BSP_RTC_H

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "hc32_ddl.h"
#include "time.h"
#include "debug.h"

/***************************************************************************
* Manifest Constants                    ����
***************************************************************************/


/***************************************************************************
* Macros                               �궨��
***************************************************************************/

/***************************************************************************
* Types                             ȫ�����Ͷ���
***************************************************************************/


/***************************************************************************
* Function Declare                  ȫ�ֺ�������
***************************************************************************/
void RTC_Initialize(void);
static void Xtal32_ClockConfig(void);
static void Rtc_Config(void);
static void Rtc_CalendarConfig(void);

void Dispaly_SyetemTime_RTC(void);
void RTC_Set_Time(uint8_t year,uint8_t month,uint8_t day,uint8_t hour,uint8_t min,uint8_t sec,uint8_t week);

time_t Time_ConvCalenderToUnix(struct tm t);
struct tm Time_ConvUnixToCalender(time_t t);
void Time_SetUnixTime(time_t t);
time_t Time_GetUnixTime(void);

#endif  /* BSP_RTC_H */

