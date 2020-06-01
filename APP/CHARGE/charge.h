/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name �����оƬ����
*  File Name   ��sensor.c
*  Description �����оƬ����
*  Author      ��maheng
*  Version     ��
*  Data        ��2020-06-01
*  Others      ��
*  Revision Details1��
*  Modify Data��
*  Version��
*  Author��
*  Modification��
*  Revision Details2��
*****************************************************************************/

#ifndef	CHARGE_H
#define	CHARGE_H

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "hc32_ddl.h"
#include "bsp_iic.h"

#include "debug.h"

/***************************************************************************
* Manifest Constants                    ����
***************************************************************************/


/***************************************************************************
* Macros                               �궨��
***************************************************************************/
#define CHARGE_ADDRESS					(0x6B)

#define I2C2_CHARGE_SCL_PORT            (PortA)
#define I2C2_CHARGE_SCL_PIN             (Pin06)
#define I2C2_CHARGE_SDA_PORT            (PortB)
#define I2C2_CHARGE_SDA_PIN             (Pin00)

#define I2C2_CHARGE_CH                  (M4_I2C2)

#define I2C2_CHARGE_BAUDRATE            (400000ul)

/***************************************************************************
* Types                             ȫ�����Ͷ���
***************************************************************************/

/***************************************************************************
* Function Declare                  ȫ�ֺ�������
***************************************************************************/

void IIC2_Charge_Init(void);
void Charge_WriteData(uint8_t addr,uint8_t *pTxData, uint32_t u32Size);
void Charge_ReceiveData(uint8_t addr,uint8_t *pRxData, uint32_t u32Size);

#endif  /* CHARGE_H */

