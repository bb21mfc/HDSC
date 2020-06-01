/*****************************************************************************
*1
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

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "debug.h"

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
uint16_t LOG_SWITCH = PWC_LOG_ID | RTC_LOG_ID;

MODULELOG Module_List[] = 
{
	{WDT_LOG_ID,WDT_LOG_NAME},
	{AT_LOG_ID,AT_LOG_NAME},
	{PWC_LOG_ID,PWC_LOG_NAME},
	{ADC_LOG_ID,ADC_LOG_NAME},
	{RTC_LOG_ID,RTC_LOG_NAME},
};
/***************************************************************************
* Static Variables                   本地全局变量
***************************************************************************/

/***************************************************************************
* Function prototypes                 函数原型
***************************************************************************/

void Write_Log_ID(uint16_t Log_ID)
{
	uint16_t count;
	char Log_Name[MAX_NAME_LEN];
	
	memset(Log_Name,0,sizeof(Log_Name));
	
	for(count = 0; count < sizeof(Module_List)/sizeof(MODULELOG); count++)
	{
		if(Log_ID == Module_List[count].ID)
		{
			Write_Uart_Debug("[%s] ",Module_List[count].NAME);
			break;
		}
	}
	
}

void Write_Log_From_ID(uint16_t Log_ID, char* fmt, ...)
{
	uint16_t i = 0;
	va_list ap;
	char Write_Buff[128];
	uint16_t last_printf = 0;
	
	if(LOG_SWITCH & Log_ID)
	{
		
		Write_Log_ID(Log_ID);
		
		memset(Write_Buff,0,sizeof(Write_Buff));

		va_start(ap,fmt);
		last_printf = vsnprintf(Write_Buff,128,fmt,ap);
		va_end(ap);
		
		while(i < last_printf)
		{
			while(!USART_GetStatus(USART3_CH,UsartTxEmpty));
			USART_SendData(USART3_CH, (uint16_t)Write_Buff[i]);
			i++;
		}
	}

}

