/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name ��GPIO����
*  File Name   ��bsp_gpio.c
*  Description ���ṩGPIO�������
*  Author      ��maheng
*  Version     ��
*  Data        ��2020-05-26
*  Others      ��
*  Revision Details1��
*  Modify Data��
*  Version��
*  Author��
*  Modification��
*  Revision Details2��
*****************************************************************************/

#ifndef	BSP_GPIO_H
#define	BSP_GPIO_H

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "hc32_ddl.h"

/***************************************************************************
* Manifest Constants                    ����
***************************************************************************/


/***************************************************************************
* Macros                               �궨��
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

/***************************************************************************
* Types                             ȫ�����Ͷ���
***************************************************************************/


/***************************************************************************
* Function Declare                  ȫ�ֺ�������
***************************************************************************/
void LED_Gpio_Init(void);


#endif  /* BSP_GPIO_H */

