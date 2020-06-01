/*****************************************************************************
* 1
*
*  Module Name ：Sensor驱动
*  File Name   ：sensor.c
*  Description ：Sensor驱动
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

#ifndef	SENSOR_H
#define	SENSOR_H

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

#define SENSOR_ADDRESS					(0x32)

#define I2C1_SENSOR_SCL_PORT            (PortA)
#define I2C1_SENSOR_SCL_PIN             (Pin04)
#define I2C1_SENSOR_SDA_PORT            (PortA)
#define I2C1_SENSOR_SDA_PIN             (Pin05)

#define I2C1_SENSOR_CH                  (M4_I2C1)

#define I2C1_SENSOR_BAUDRATE            (400000ul)

/***************************************************************************
* Types                             全局类型定义
***************************************************************************/

/***************************************************************************
* Function Declare                  全局函数声明
***************************************************************************/
void IIC1_Sensor_Init(void);
void Sensor_WriteData(uint8_t addr,uint8_t *pTxData, uint32_t u32Size);
void Sensor_ReceiveData(uint8_t addr,uint8_t *pRxData, uint32_t u32Size);

#endif  /* SENSOR_H */

