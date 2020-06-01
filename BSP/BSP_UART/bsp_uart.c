/*****************************************************************************
*1
*
*  Module Name ��UART����
*  File Name   ��bsp_uart.c
*  Description ���ṩUART�������
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
#include "bsp_uart.h"

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
extern app_fifo_t Uart_Fifo;
/***************************************************************************
* Function Declare                  �ⲿ��������
***************************************************************************/

/***************************************************************************
* Variables                           ȫ�ֱ���
***************************************************************************/

/***************************************************************************
* Static Variables                   ����ȫ�ֱ���
***************************************************************************/
static uint16_t m_u16RxData;
/***************************************************************************
* Function prototypes                 ����ԭ��
***************************************************************************/
static void UsartRxIrqCallback(void);


/*****************************************************************************
*	������		�� USART3_Init
*	����	    �� ��ʼ��LED��ӦGPIO
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
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
*	������		�� UsartRxIrqCallback
*	����	    �� UART3�Ľ����жϺ���
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
static void UsartRxIrqCallback(void)
{
    m_u16RxData = USART_RecData(USART3_CH);
	app_fifo_write(&Uart_Fifo,(uint8_t*)&m_u16RxData,1);
}

/*****************************************************************************
*	������		�� USART3_SendData
*	����	    �� ���ڷ��ͺ���
*	�������	�� data������ len������
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
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
*	������		�� Write_Uart_Debug
*	����	    �� UART3�ķ��ͺ���
*	�������	�� ����ַ���
*	�������	�� �ַ�������
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
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

