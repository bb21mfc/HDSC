/*****************************************************************************
*1
*
*  Module Name ：UART驱动
*  File Name   ：bsp_uart.c
*  Description ：提供UART相关驱动
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

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "bsp_uart.h"

/***************************************************************************
* Manifest Constants                    常量
***************************************************************************/

/***************************************************************************
* Macros                               宏定义
***************************************************************************/

/***************************************************************************
* Types                               类型定义
***************************************************************************/

/***************************************************************************
* Variables Declare                 外部变量声明
***************************************************************************/
extern app_fifo_t Uart_Fifo;
/***************************************************************************
* Function Declare                  外部函数声明
***************************************************************************/

/***************************************************************************
* Variables                           全局变量
***************************************************************************/

/***************************************************************************
* Static Variables                   本地全局变量
***************************************************************************/
static uint16_t m_u16RxData;
/***************************************************************************
* Function prototypes                 函数原型
***************************************************************************/
static void UsartRxIrqCallback(void);


/*****************************************************************************
*	函数名		： USART3_Init
*	功能	    ： 初始化LED对应GPIO
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void USART3_Init(void)
{
    stc_irq_regi_conf_t stcIrqRegiCfg;
    uint32_t u32Fcg1Periph = PWC_FCG1_PERIPH_USART3;
	
	const stc_usart_uart_init_t stcInitCfg = {
        UsartIntClkCkNoOutput,
        UsartClkDiv_1,
        UsartDataBits8,
        UsartDataLsbFirst,
        UsartOneStopBit,
        UsartParityNone,
        UsartSamleBit8,
        UsartStartBitFallEdge,
        UsartRtsEnable,
    };
	
	/* Enable peripheral clock */
    PWC_Fcg1PeriphClockCmd(u32Fcg1Periph, Enable);
	
    /* Initialize USART IO */
    PORT_SetFunc(USART3_RX_PORT, USART3_RX_PIN, USART3_RX_FUNC, Disable);
    PORT_SetFunc(USART3_TX_PORT, USART3_TX_PIN, USART3_TX_FUNC, Disable);
	
    /* Initialize UART */
	USART_UART_Init(USART3_CH, &stcInitCfg);
 
    /* Set baudrate */
    USART_SetBaudrate(USART3_CH, USART3_BAUDRATE);

	/* Set USART RX IRQ */
    stcIrqRegiCfg.enIRQn = Int000_IRQn;
    stcIrqRegiCfg.pfnCallback = &UsartRxIrqCallback;
    stcIrqRegiCfg.enIntSrc = USART3_RI_NUM;
	
    enIrqRegistration(&stcIrqRegiCfg);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
	
	/*Enable TX && RX && RX interupt function*/
	USART_FuncCmd(USART3_CH, UsartTx, Enable);
    USART_FuncCmd(USART3_CH, UsartRx, Enable);
    USART_FuncCmd(USART3_CH, UsartRxInt, Enable);
}

/*****************************************************************************
*	函数名		： UsartRxIrqCallback
*	功能	    ： UART3的接收中断函数
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void UsartRxIrqCallback(void)
{
    m_u16RxData = USART_RecData(USART3_CH);
	app_fifo_write(&Uart_Fifo,(uint8_t*)&m_u16RxData,1);
}

/*****************************************************************************
*	函数名		： USART3_SendData
*	功能	    ： 串口发送函数
*	输入参数	： data：数据 len：长度
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void USART3_SendData(uint8_t *data, uint32_t len)
{
	uint32_t i = 0;
	
	while(i < len)
	{
		while(!USART_GetStatus(USART3_CH,UsartTxEmpty));
		USART_SendData(USART3_CH, data[i]);
		i++;
	}
}

/*****************************************************************************
*	函数名		： Write_Uart_Debug
*	功能	    ： UART3的发送函数
*	输入参数	： 输出字符串
*	输出参数	： 字符串长度
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
uint8_t Write_Uart_Debug(char* fmt, ...)
{
	uint16_t i = 0;
	va_list ap;
	char Write_Buff[256];
	uint16_t last_printf = 0;

	memset(Write_Buff,0,sizeof(Write_Buff));

	va_start(ap,fmt);
	last_printf = vsnprintf(Write_Buff,256,fmt,ap);
	va_end(ap);
	
	USART3_SendData((uint8_t*)Write_Buff,last_printf);

	return i;
}

