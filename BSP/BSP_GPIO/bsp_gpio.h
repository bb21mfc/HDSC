/*****************************************************************************
* 1
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

#ifndef	BSP_GPIO_H
#define	BSP_GPIO_H

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "hc32_ddl.h"

#include "FreeRTOS.h"
#include "task.h"
/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/


/***************************************************************************
* Macros                               宏定义
***************************************************************************/

/* LED0 Port/Pin definition */
#define  LED0_PORT        (PortE)
#define  LED0_PIN         (Pin06)

/* LED1 Port/Pin definition */
#define  LED1_PORT        (PortA)
#define  LED1_PIN         (Pin07)

/* LED2 Port/Pin definition */
#define  LED2_PORT        (PortB)
#define  LED2_PIN         (Pin05)

/* LED3 Port/Pin definition */
#define  LED3_PORT        (PortB)
#define  LED3_PIN         (Pin09)

/* LED0~3 toggle definition */
#define  LED0_TOGGLE()    (PORT_Toggle(LED0_PORT, LED0_PIN))
#define  LED1_TOGGLE()    (PORT_Toggle(LED1_PORT, LED1_PIN))
#define  LED2_TOGGLE()    (PORT_Toggle(LED2_PORT, LED2_PIN))
#define  LED3_TOGGLE()    (PORT_Toggle(LED3_PORT, LED3_PIN))


/* LED RED Port/Pin definition */
#define  LED_RED_PORT       (PortA)
#define  LED_RED_PIN        (Pin07)

/* LED GREEN Port/Pin definition */
#define  LED_GREEN_PORT     (PortB)
#define  LED_GREEN_PIN      (Pin05)

/* LED YELLOW Port/Pin definition */
#define  LED_YELLOW_PORT    (PortB)
#define  LED_YELLOW_PIN     (Pin09)

/* Sensor Port/Pin definition */
#define  SENSOR_PORT        (PortH)
#define  SENSOR_PIN         (Pin02)

/* GPS Port/Pin definition */
#define  GPS_PORT        	(PortC)
#define  GPS_PIN         	(Pin13)

/* BAT ADC_EN Port/Pin definition */
#define  BAT_ADC_EN_PORT    (PortB)
#define  BAT_ADC_EN_PIN     (Pin08)

/* V_MDM_EN Port/Pin definition */
#define  V_MDM_EN_PORT    	(PortA)
#define  V_MDM_EN_PIN     	(Pin03)

/* MDM_PWR_KEY Port/Pin definition */
#define  MDM_PWR_KEY_PORT   (PortB)
#define  MDM_PWR_KEY_PIN    (Pin15)


#define  LED_RED_ON()    		(PORT_ResetBits(LED_RED_PORT, LED_RED_PIN))
#define  LED_RED_OFF()    		(PORT_SetBits(LED_RED_PORT, LED_RED_PIN))
#define  LED_RED_TOGGLE()    	(PORT_Toggle(LED_RED_PORT, LED_RED_PIN))

#define  LED_GREEN_ON()    		(PORT_ResetBits(LED_GREEN_PORT, LED_GREEN_PIN))
#define  LED_GREEN_OFF()    	(PORT_SetBits(LED_GREEN_PORT, LED_GREEN_PIN))
#define  LED_GREEN_TOGGLE()    	(PORT_Toggle(LED_GREEN_PORT, LED_GREEN_PIN))

#define  LED_YELLOW_ON()    	(PORT_ResetBits(LED_YELLOW_PORT, LED_YELLOW_PIN))
#define  LED_YELLOW_OFF()    	(PORT_SetBits(LED_YELLOW_PORT, LED_YELLOW_PIN))
#define  LED_YELLOW_TOGGLE()    (PORT_Toggle(LED_YELLOW_PORT, LED_YELLOW_PIN))

/***************************************************************************
* Types                             全局类型定义
***************************************************************************/

/***************************************************************************
* Function Declare                  全局函数声明
***************************************************************************/
void LED_Gpio_Init(void);

void Bsp_Gpio_Init(void);

void V_Modem_On(void);
void V_Modem_Off(void);
void Modem_PowerOn(void);
void Modem_PowerOff(void);

#endif  /* BSP_GPIO_H */

