/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name ��AT�������
*  File Name   ��at_cmd.c
*  Description ������AT����
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

#ifndef	AT_CMD_H
#define	AT_CMD_H

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "hc32_ddl.h"
#include "bsp_gpio.h"
#include "bsp_uart.h"
#include "fifo.h"

#include "FreeRTOS.h"
#include "task.h"

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

void AT_Process( void * pvParameters );
void Task_AT_Process_Start(void);
#endif  /* AT_CMD_H */
