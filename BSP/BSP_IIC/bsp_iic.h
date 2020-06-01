/*****************************************************************************
* Copyright(C) 2017,GosuncnWelink
*
*  Module Name ：IIC相关驱动
*  File Name   ：bsp_iic.c
*  Description ：提供IIC相关驱动
*  Author      ：maheng
*  Version     ：
*  Data        ：2020-05-28
*  Others      ：
*  Revision Details1：
*  Modify Data：
*  Version：
*  Author：
*  Modification：
*  Revision Details2：
*****************************************************************************/

#ifndef	BSP_IIC_H
#define	BSP_IIC_H

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "hc32_ddl.h"

#include "debug.h"

/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/


/***************************************************************************
* Macros                               宏定义
***************************************************************************/

#define ADDRESS_W                       (0x00u)
#define ADDRESS_R                       (0x01u)

#define TIMEOUT                         ((uint32_t)0x10000)

typedef enum Generate_Status
{
    GENERATE_START 		= 0u,
    GENERATE_RESTART 	= 1u,
} Generate_Status_t;

typedef enum return_status
{
    I2C_RET_OK 		= 0u,
    I2C_RET_ERROR  	= 1u,
} return_status_t;
/***************************************************************************
* Types                             全局类型定义
***************************************************************************/


/***************************************************************************
* Function Declare                  全局函数声明
***************************************************************************/
static uint8_t Master_StartOrRestart(M4_I2C_TypeDef* I2Cx,uint8_t u8Start);
static uint8_t Master_Stop(M4_I2C_TypeDef* I2Cx);
static uint8_t Master_SendAddr(M4_I2C_TypeDef* I2Cx, uint8_t u8Addr);
static uint8_t Master_WriteData(M4_I2C_TypeDef* I2Cx, uint8_t *pTxData, uint32_t u32Size);
static uint8_t Master_ReceiveData(M4_I2C_TypeDef* I2Cx, uint8_t *pRxData, uint32_t u32Size);
void I2C_WriteData(M4_I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t addr,uint8_t *pTxData, uint32_t u32Size);
void I2C_ReceiveData(M4_I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t addr,uint8_t *pRxData, uint32_t u32Size);

#endif  /* BSP_IIC_H */

