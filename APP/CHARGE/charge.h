/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name ：充电芯片驱动
*  File Name   ：sensor.c
*  Description ：充电芯片驱动
*  Author      ：maheng
*  Version     ：
*  Data        ：2020-06-01
*  Others      ：
*  Revision Details1：
*  Modify Data：
*  Version：
*  Author：
*  Modification：
*  Revision Details2：
*****************************************************************************/

#ifndef	CHARGE_H
#define	CHARGE_H

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "hc32_ddl.h"
#include "bsp_iic.h"

#include "debug.h"

/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/


/***************************************************************************
* Macros                               宏定义
***************************************************************************/
#define CHARGE_ADDRESS					(0x6B)

#define I2C2_CHARGE_SCL_PORT            (PortA)
#define I2C2_CHARGE_SCL_PIN             (Pin06)
#define I2C2_CHARGE_SDA_PORT            (PortB)
#define I2C2_CHARGE_SDA_PIN             (Pin00)

#define I2C2_CHARGE_CH                  (M4_I2C2)

#define I2C2_CHARGE_BAUDRATE            (400000ul)

/***************************************************************************
* Types                             全局类型定义
***************************************************************************/

/***************************************************************************
* Function Declare                  全局函数声明
***************************************************************************/

void IIC2_Charge_Init(void);
void Charge_WriteData(uint8_t addr,uint8_t *pTxData, uint32_t u32Size);
void Charge_ReceiveData(uint8_t addr,uint8_t *pRxData, uint32_t u32Size);

#endif  /* CHARGE_H */

