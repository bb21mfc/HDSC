/*****************************************************************************
*1
*
*  Module Name ：GPIO驱动
*  File Name   ：bsp_gpio.c
*  Description ：提供GPIO相关驱动
*  Author      ：maheng
*  Version     ：
*  Data        ：2020-05-26
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
#include "bsp_gpio.h"

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
*	函数名		： LED_Gpio_Init
*	功能	    ： 初始化LED对应GPIO
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void LED_Gpio_Init(void)
{
	stc_port_init_t stcPortInit;
	
	/* configuration structure initialization */
    MEM_ZERO_STRUCT(stcPortInit);

    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enExInt = Disable;
    stcPortInit.enPullUp = Disable;

    /* LED0 Port/Pin initialization */
    PORT_Init(LED0_PORT, LED0_PIN, &stcPortInit);

    /* LED1 Port/Pin initialization */
    PORT_Init(LED1_PORT, LED1_PIN, &stcPortInit);

    /* LED2 Port/Pin initialization */
    PORT_Init(LED2_PORT, LED2_PIN, &stcPortInit);

    /* LED3 Port/Pin initialization */
    PORT_Init(LED3_PORT, LED3_PIN, &stcPortInit);
}

/*****************************************************************************
*	函数名		： Bsp_Gpio_Init
*	功能	    ： 初始化使用到的外设的GPIO
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Bsp_Gpio_Init(void)
{
	stc_port_init_t stcPortInit;
	
	/* configuration structure initialization */
    MEM_ZERO_STRUCT(stcPortInit);

    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enExInt = Disable;
    stcPortInit.enPullUp = Disable;
	stcPortInit.enPinDrv = Pin_Drv_H;
	
	/* LED RED Port/Pin initialization */
    PORT_Init(LED_RED_PORT, LED_RED_PIN, &stcPortInit);
	
	/* LED GREEN Port/Pin initialization */
    PORT_Init(LED_GREEN_PORT, LED_GREEN_PIN, &stcPortInit);
	
	/* LED YELLOW Port/Pin initialization */
    PORT_Init(LED_YELLOW_PORT, LED_YELLOW_PIN, &stcPortInit);
	
	/* Sensor Port/Pin initialization */
    PORT_Init(SENSOR_PORT, SENSOR_PIN, &stcPortInit);
	
	/* GPS Port/Pin initialization */
    PORT_Init(GPS_PORT, GPS_PIN, &stcPortInit);
	
	/* BAT_ADC_EN Port/Pin initialization */
    PORT_Init(BAT_ADC_EN_PORT, BAT_ADC_EN_PIN, &stcPortInit);
	
	/* V_MDM_EN Port/Pin initialization */
    PORT_Init(V_MDM_EN_PORT, V_MDM_EN_PIN, &stcPortInit);
	
	/* MDM_PWR_KEY Port/Pin initialization */
    PORT_Init(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN, &stcPortInit);
	PORT_SetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
}

/*****************************************************************************
*	函数名		： V_Modem_On
*	功能	    ： 打开Modem的电源
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void V_Modem_On(void)
{
	PORT_SetBits(V_MDM_EN_PORT, V_MDM_EN_PIN);
}

/*****************************************************************************
*	函数名		： V_Modem_Off
*	功能	    ： 关闭Modem的电源
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void V_Modem_Off(void)
{
	PORT_ResetBits(V_MDM_EN_PORT, V_MDM_EN_PIN);
}

/*****************************************************************************
*	函数名		： Modem_PowerOn
*	功能	    ： Modem开机
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Modem_PowerOn(void)
{
	PORT_ResetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	vTaskDelay(500);
	PORT_SetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	
}

/*****************************************************************************
*	函数名		： Modem_PowerOff
*	功能	    ： Modem关机
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Modem_PowerOff(void)
{
	PORT_ResetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	vTaskDelay(13000);
	PORT_SetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	
}