/*****************************************************************************
* 1
*
*  Module Name ：GPIO驱动
*  File Name   ：bsp_uart.c
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

#ifndef	BSP_UART_H
#define	BSP_UART_H

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "hc32_ddl.h"
#include "bsp_gpio.h"
#include "fifo.h"

#include "stdio.h"
#include "stdarg.h"
#include "string.h"
/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/


/***************************************************************************
* Macros                               宏定义
***************************************************************************/

#define USART3_CH                        (M4_USART3)

/* USART baudrate definition */
#define USART3_BAUDRATE                  (115200ul)

/* USART RX Port/Pin definition */
#define USART3_RX_PORT                   (PortE)
#define USART3_RX_PIN                    (Pin04)
#define USART3_RX_FUNC                   (Func_Usart3_Rx)

/* USART TX Port/Pin definition */
#define USART3_TX_PORT                   (PortE)
#define USART3_TX_PIN                    (Pin05)
#define USART3_TX_FUNC                   (Func_Usart3_Tx)

/* USART interrupt number  */
#define USART3_RI_NUM                    (INT_USART3_RI)

/***************************************************************************
* Types                             全局类型定义
***************************************************************************/


/***************************************************************************
* Function Declare                  全局函数声明
***************************************************************************/
void USART3_Init(void);
void USART3_SendData(uint8_t *data, uint32_t len);
uint8_t Write_Uart_Debug(char* fmt, ...);
#endif  /* BSP_UART_H */

