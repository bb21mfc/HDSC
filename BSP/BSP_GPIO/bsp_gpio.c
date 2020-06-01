/*****************************************************************************
*1
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

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "bsp_gpio.h"

/***************************************************************************
* Manifest Constants                    ����
***************************************************************************/

/***************************************************************************
* Macros                               �궨��
***************************************************************************/

/***************************************************************************
* Types                               ���Ͷ���
***************************************************************************/

/***************************************************************************
* Variables Declare                 �ⲿ��������
***************************************************************************/

/***************************************************************************
* Function Declare                  �ⲿ��������
***************************************************************************/

/***************************************************************************
* Variables                           ȫ�ֱ���
***************************************************************************/

/***************************************************************************
* Static Variables                   ����ȫ�ֱ���
***************************************************************************/

/***************************************************************************
* Function prototypes                 ����ԭ��
***************************************************************************/

/*****************************************************************************
*	������		�� LED_Gpio_Init
*	����	    �� ��ʼ��LED��ӦGPIO
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
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
*	������		�� Bsp_Gpio_Init
*	����	    �� ��ʼ��ʹ�õ��������GPIO
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
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
*	������		�� V_Modem_On
*	����	    �� ��Modem�ĵ�Դ
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void V_Modem_On(void)
{
	PORT_SetBits(V_MDM_EN_PORT, V_MDM_EN_PIN);
}

/*****************************************************************************
*	������		�� V_Modem_Off
*	����	    �� �ر�Modem�ĵ�Դ
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void V_Modem_Off(void)
{
	PORT_ResetBits(V_MDM_EN_PORT, V_MDM_EN_PIN);
}

/*****************************************************************************
*	������		�� Modem_PowerOn
*	����	    �� Modem����
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void Modem_PowerOn(void)
{
	PORT_ResetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	vTaskDelay(500);
	PORT_SetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	
}

/*****************************************************************************
*	������		�� Modem_PowerOff
*	����	    �� Modem�ػ�
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void Modem_PowerOff(void)
{
	PORT_ResetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	vTaskDelay(13000);
	PORT_SetBits(MDM_PWR_KEY_PORT, MDM_PWR_KEY_PIN);
	
}