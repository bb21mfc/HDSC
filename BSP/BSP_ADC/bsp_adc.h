/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name ��ADC�������
*  File Name   ��bsp_adc.c
*  Description ���ṩADC�������
*  Author      ��maheng
*  Version     ��
*  Data        ��2020-05-28
*  Others      ��
*  Revision Details1��
*  Modify Data��
*  Version��
*  Author��
*  Modification��
*  Revision Details2��
*****************************************************************************/

#ifndef	BSP_ADC_H
#define	BSP_ADC_H

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "hc32_ddl.h"

#include "debug.h"

/***************************************************************************
* Manifest Constants                    ����
***************************************************************************/


/***************************************************************************
* Macros                               �궨��
***************************************************************************/

/*
 * If you remap the mapping between the channel and the pin with the function
 * ADC_ChannleRemap, define ADC_CH_REMAP as non-zero, otherwise define as 0.
 */
#define ADC_CH_REMAP                (0u)

#define ADC1_SA_NORMAL_CHANNEL      (ADC1_CH10)
#define ADC1_SCAN_MODE              (AdcMode_SAOnce)

/* ADC reference voltage. The voltage of pin VREFH. */
#define ADC_VREF                    (3.288f)

/* ADC accuracy. */
#define ADC1_ACCURACY               (4096)

/* Timeout value definitions. */
#define TIMEOUT_MS                  (10u)

/***************************************************************************
* Types                             ȫ�����Ͷ���
***************************************************************************/


/***************************************************************************
* Function Declare                  ȫ�ֺ�������
***************************************************************************/
void ADC_Initialize(void);
static void AdcClockConfig(void);
static void AdcInitConfig(void);
static void AdcChannelConfig(void);
static void AdcSetChannelPinMode(const M4_ADC_TypeDef *ADCx,uint32_t u32Channel,en_pin_mode_t enMode);
static void AdcSetPinMode(uint8_t u8AdcPin, en_pin_mode_t enMode);

uint16_t Get_BAT_ADC_Value(void);
float Get_BAT_Voltage(void);

#endif  /* BSP_ADC_H */

