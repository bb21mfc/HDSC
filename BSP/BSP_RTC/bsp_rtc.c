/*****************************************************************************
*Copyright(C) 2017,GosuncnWelink
*
*  Module Name ：RTC相关驱动
*  File Name   ：bsp_rtc.c
*  Description ：提供RTC相关驱动
*  Author      ：maheng
*  Version     ：
*  Data        ：2020-05-29
*  Others      ：
*  Revision Details1：
*  Modify Data：
*  Version：
*  Author：
*  Modification：
*  Revision Details2：
*****************************************************************************/

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "bsp_rtc.h"

/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/

/***************************************************************************
* Macros                               宏定义
***************************************************************************/

/***************************************************************************
* Types                               类型定义
***************************************************************************/

/***************************************************************************
* Variables Declare                 外部变量声明
***************************************************************************/

/***************************************************************************
* Function Declare                  外部函数声明
***************************************************************************/

/***************************************************************************
* Variables                           全局变量
***************************************************************************/

/***************************************************************************
* Static Variables                   本地全局变量
***************************************************************************/

/***************************************************************************
* Function prototypes                 函数原型
***************************************************************************/

/*****************************************************************************
*	函数名		： RTC_Initialize
*	功能	    ： Initialize RTC
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void RTC_Initialize(void)
{
	//Colse RTC First
	RTC_DeInit();
	RTC_Cmd(Disable);
	
	Xtal32_ClockConfig();
	Rtc_Config();
}

/*****************************************************************************
*	函数名		： Xtal32_ClockConfig
*	功能	    ： Config RTC Clock Source.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void Xtal32_ClockConfig(void)
{
    stc_clk_xtal32_cfg_t stcXtal32Cfg;

    /* configure structure initialization */
    MEM_ZERO_STRUCT(stcXtal32Cfg);

    /* Stop xtal32 */
    CLK_Xtal32Cmd(Disable);
    Ddl_Delay1ms(100u);
    /* Configuration xtal32 structure */
    stcXtal32Cfg.enFastStartup = Disable;
    stcXtal32Cfg.enDrv = ClkXtal32HighDrv;
    stcXtal32Cfg.enFilterMode = ClkXtal32FilterModeFull;
    CLK_Xtal32Config(&stcXtal32Cfg);
    /* Startup xtal32 */
    CLK_Xtal32Cmd(Enable);
    /* wait for xtal32 running */
    //Ddl_Delay1ms(3000u);
}

/*****************************************************************************
*	函数名		： Rtc_Config
*	功能	    ： Config RTC Drive.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void Rtc_Config(void)
{
    stc_rtc_init_t stcRtcInit;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcRtcInit);

    /* Rtc stopped */
    if (0u == M4_RTC->CR1_f.START)
    {
        /* Reset rtc counter */
        if (RTC_DeInit() == ErrorTimeout)
        {
            Write_Uart_Debug("reset rtc failed!\r\n");
        }
        else
        {
            /* Configuration rtc structure */
            stcRtcInit.enClkSource = RtcClkXtal32;
            stcRtcInit.enPeriodInt = RtcPeriodIntOneSec;
            stcRtcInit.enTimeFormat = RtcTimeFormat24Hour;
            stcRtcInit.enCompenWay = RtcOutputCompenDistributed;
            stcRtcInit.enCompenEn = Disable;
            stcRtcInit.u16CompenVal = 0u;
            RTC_Init(&stcRtcInit);

            /* Enable period interrupt */
            RTC_IrqCmd(RtcIrqPeriod, Enable);
            /* Startup rtc count */
            RTC_Cmd(Enable);

            /* wait for rtc running */
            Ddl_Delay1ms(1u);
            /* Update time after RTC startup */
            Rtc_CalendarConfig();
        }
    }
}

/*****************************************************************************
*	函数名		： Rtc_CalendarConfig
*	功能	    ： Config RTC Calendar.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void Rtc_CalendarConfig(void)
{
    stc_rtc_date_time_t stcRtcDateTimeCfg;

    /* configure structure initialization */
    MEM_ZERO_STRUCT(stcRtcDateTimeCfg);
#if 0
//    /* calendar configuration */
//    stcRtcDateTimeCfg.u8Year = 20u;
//    stcRtcDateTimeCfg.u8Month = 5u;
//    stcRtcDateTimeCfg.u8Day = 29u;
//    stcRtcDateTimeCfg.u8Weekday = RtcWeekdayFriday;
//    stcRtcDateTimeCfg.u8Hour = 23u;
//    stcRtcDateTimeCfg.u8Minute = 59u;
//    stcRtcDateTimeCfg.u8Second = 55u;
//	
//    if (RTC_SetDateTime(RtcDataFormatDec, &stcRtcDateTimeCfg, Enable, Enable) != Ok)
//    {
//        Write_Uart_Debug("write calendar failed!\r\n");
//    }
#else
	Time_SetUnixTime(1590767995);
#endif
}

/*****************************************************************************
*	函数名		： RTC_Set_Time
*	功能	    ： Set RTC Time.
*	输入参数	： year,mouth,day:年,月,日  hour,min,sec,week:小时,分钟,秒钟,周
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void RTC_Set_Time(uint8_t year,uint8_t month,uint8_t day,uint8_t hour,uint8_t min,uint8_t sec,uint8_t week)
{
	stc_rtc_date_time_t stcRtcDateTimeCfg;

    /* configure structure initialization */
    MEM_ZERO_STRUCT(stcRtcDateTimeCfg);

    /* calendar configuration */
    stcRtcDateTimeCfg.u8Year = year;
    stcRtcDateTimeCfg.u8Month = month;
    stcRtcDateTimeCfg.u8Day = day;
    stcRtcDateTimeCfg.u8Weekday = week;	
    stcRtcDateTimeCfg.u8Hour = hour;
    stcRtcDateTimeCfg.u8Minute = min;
    stcRtcDateTimeCfg.u8Second = sec;
	
	if (RTC_SetDateTime(RtcDataFormatDec, &stcRtcDateTimeCfg, Enable, Enable) != Ok)
    {
        Write_Uart_Debug("write calendar failed!\r\n");
    }
}

/*****************************************************************************
*	函数名		： Dispaly_SyetemTime_RTC
*	功能	    ： Dispaly SyetemTime RTC.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Dispaly_SyetemTime_RTC(void)
{
	time_t UnixTime;
	stc_rtc_date_time_t stcCurrDateTime;
	
	MEM_ZERO_STRUCT(stcCurrDateTime);
	
	RTC_GetDateTime(RtcDataFormatDec, &stcCurrDateTime);
	
	UnixTime = Time_GetUnixTime();
	
	LOGRTC("20%02d/%02d/%02d %02d:%02d:%02d  %d\r\n", stcCurrDateTime.u8Year,
                       stcCurrDateTime.u8Month, stcCurrDateTime.u8Day,
                       stcCurrDateTime.u8Hour, stcCurrDateTime.u8Minute,
                       stcCurrDateTime.u8Second,UnixTime);
}

time_t Time_ConvCalenderToUnix(struct tm t)
{
	return mktime(&t);
}

struct tm Time_ConvUnixToCalender(time_t t)
{
	struct tm *t_tm;
	
	t_tm = localtime(&t);
	
	return *t_tm;
}

/*****************************************************************************
*	函数名		： Time_SetUnixTime
*	功能	    ： 设置时间戳信息
*	输入参数	： time_t Unix时间戳
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Time_SetUnixTime(time_t t)
{
	struct tm t_tm;
	
	t_tm = Time_ConvUnixToCalender(t);
	
	RTC_Set_Time(t_tm.tm_year + 1900 - 2000,
				 t_tm.tm_mon + 1,
				 t_tm.tm_mday,
				 t_tm.tm_hour,
				 t_tm.tm_min,
				 t_tm.tm_sec,
				 t_tm.tm_wday);
}

/*****************************************************************************
*	函数名		： Time_SetUnixTime
*	功能	    ： 获取时间戳信息
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： time_t 
*	其他说明	： NULL
*****************************************************************************/
time_t Time_GetUnixTime(void)
{
	struct tm t_tm;
	time_t tmp;
	
	stc_rtc_date_time_t stcCurrDateTime;
	
	MEM_ZERO_STRUCT(stcCurrDateTime);
	
	RTC_GetDateTime(RtcDataFormatDec, &stcCurrDateTime);
	
	t_tm.tm_year 	= stcCurrDateTime.u8Year + 2000 - 1900;
	t_tm.tm_mon		= stcCurrDateTime.u8Month - 1;
	t_tm.tm_mday	= stcCurrDateTime.u8Day;
	t_tm.tm_wday	= stcCurrDateTime.u8Weekday;
	
	t_tm.tm_hour	= stcCurrDateTime.u8Hour;
	t_tm.tm_min		= stcCurrDateTime.u8Minute;
	t_tm.tm_sec		= stcCurrDateTime.u8Second;
	
	tmp = Time_ConvCalenderToUnix(t_tm);
	
	return tmp;
}
