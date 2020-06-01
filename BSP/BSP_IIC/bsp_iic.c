/*****************************************************************************
*Copyright(C) 2017,GosuncnWelink
*
*  Module Name ��IIC�������
*  File Name   ��bsp_iic.c
*  Description ���ṩIIC�������
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

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "bsp_iic.h"

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
*	������		�� Master_StartOrRestart
*	����	    �� ����Start�ź�
*	�������	�� u8Start��START or RESTART
*	�������	�� NULL
*	����ֵ˵��  �� I2C_RET_ERROR  Process failed
*				   I2C_RET_OK     Process success
*	����˵��	�� NULL
*****************************************************************************/
static uint8_t Master_StartOrRestart(M4_I2C_TypeDef* I2Cx,uint8_t u8Start)
{
    uint32_t u32TimeOut = TIMEOUT;
    en_flag_status_t enFlagBusy = Reset;
    en_flag_status_t enFlagStartf = Reset;

    /* generate start or restart signal */
    if(GENERATE_START == u8Start)
    {
        /* Wait I2C bus idle */
        while(Set == I2C_GetStatus(I2Cx, I2C_SR_BUSY))
        {
            if(0ul == (u32TimeOut--))
            {
                return I2C_RET_ERROR;
            }
        }

        I2C_GenerateStart(I2Cx , Enable);
    }
    else
    {
        /* Clear start status flag */
        I2C_ClearStatus(I2Cx, I2C_CLR_STARTFCLR);
        /* Send restart condition */
        I2C_GenerateReStart(I2Cx , Enable);
    }

    /* Judge if start success*/
    u32TimeOut = TIMEOUT;
    while(1)
    {
        enFlagBusy = I2C_GetStatus(I2Cx, I2C_SR_BUSY);
        enFlagStartf = I2C_GetStatus(I2Cx, I2C_SR_STARTF);
        if(enFlagBusy && enFlagStartf)
        {
            break;
        }
        if(0ul == (u32TimeOut--))
        {
            return I2C_RET_ERROR;
        }
    }

    return I2C_RET_OK;
}

/*****************************************************************************
*	������		�� Master_Stop
*	����	    �� ����Stop�ź�
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� I2C_RET_ERROR  Process failed
*				   I2C_RET_OK     Process success
*	����˵��	�� NULL
*****************************************************************************/
static uint8_t Master_Stop(M4_I2C_TypeDef* I2Cx)
{
    uint32_t u32TimeOut;

    /* Wait I2C bus busy */
    u32TimeOut = TIMEOUT;
    while(Reset == I2C_GetStatus(I2Cx, I2C_SR_BUSY))
    {
        if(0ul == (u32TimeOut--))
        {
            return I2C_RET_ERROR;
        }
    }

    I2C_GenerateStop(I2Cx, Enable);

    /* Wait STOPF */
    u32TimeOut = TIMEOUT;
    while(Reset == I2C_GetStatus(I2Cx, I2C_SR_STOPF))
    {
        if(0ul == (u32TimeOut--))
        {
            return I2C_RET_ERROR;
        }
    }
    return I2C_RET_OK;
}

/*****************************************************************************
*	������		�� Master_SendAddr
*	����	    �� ͨ��IIC���߷��͵�ַ
*	�������	�� u8Addr Ҫ���������豸�ĵ�ַ
*	�������	�� NULL
*	����ֵ˵��  �� I2C_RET_ERROR  Process failed
*				   I2C_RET_OK     Process success
*	����˵��	�� NULL
*****************************************************************************/
static uint8_t Master_SendAddr(M4_I2C_TypeDef* I2Cx, uint8_t u8Addr)
{
    uint32_t u32TimeOut = TIMEOUT;

    /* Wait tx buffer empty */
    while(Reset == I2C_GetStatus(I2Cx, I2C_SR_TEMPTYF))
    {
        if(0ul == (u32TimeOut--))
        {
            return I2C_RET_ERROR;
        }
    }

    /* Send I2C address */
    I2C_SendData(I2Cx, u8Addr);

    //if(E2_ADDRESS_W == (u8Adr & 0x01u))
    if(!(u8Addr & 0x01u))     /*  C-STAT MISRAC2004-13.7 */
    {
        /* If in master transfer process, Need wait transfer end*/
        uint32_t u32TimeOut = TIMEOUT;
        while(Reset == I2C_GetStatus(I2Cx, I2C_SR_TENDF))
        {
            if(0ul == (u32TimeOut--))
            {
                return I2C_RET_ERROR;
            }
        }
    }

    /* Check ACK */
    u32TimeOut = TIMEOUT;
    while(Set == I2C_GetStatus(I2Cx, I2C_SR_NACKDETECTF))
    {
        if(0ul == (u32TimeOut--))
        {
            return I2C_RET_ERROR;
        }
    }

    return I2C_RET_OK;
}

/*****************************************************************************
*	������		�� Master_WriteData
*	����	    �� ͨ��IIC���߷�������
*	�������	�� pTxData	�������ݵ�ַ
*				   u32Size  �������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� I2C_RET_ERROR  Process failed
*				   I2C_RET_OK     Process success
*	����˵��	�� NULL
*****************************************************************************/
static uint8_t Master_WriteData(M4_I2C_TypeDef* I2Cx, uint8_t *pTxData, uint32_t u32Size)
{
    uint32_t u32TimeOut = TIMEOUT;

    while(u32Size--)
    {
        /* Wait tx buffer empty */
        u32TimeOut = TIMEOUT;
        while(Reset == I2C_GetStatus(I2Cx, I2C_SR_TEMPTYF))
        {
            if(0ul == (u32TimeOut--))
            {
                return I2C_RET_ERROR;
            }
        }

        /* Send one byte data */
        I2C_SendData(I2Cx, *pTxData++);

        /* Wait transfer end*/
        u32TimeOut = TIMEOUT;
        while(Reset == I2C_GetStatus(I2Cx, I2C_SR_TENDF))
        {
            if(0ul == (u32TimeOut--))
            {
                return I2C_RET_ERROR;
            }
        }

        /* Check ACK */
        u32TimeOut = TIMEOUT;
        while(Set == I2C_GetStatus(I2Cx, I2C_SR_NACKDETECTF))
        {
            if(0ul == (u32TimeOut--))
            {
                return I2C_RET_ERROR;
            }
        }
    }

    return I2C_RET_OK;
}

/*****************************************************************************
*	������		�� Master_ReceiveData
*	����	    �� ͨ��IIC���߽�������
*	�������	�� pRxData	�������ݵ�ַ
*				   u32Size  �������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� I2C_RET_ERROR  Process failed
*				   I2C_RET_OK     Process success
*	����˵��	�� NULL
*****************************************************************************/
static uint8_t Master_ReceiveData(M4_I2C_TypeDef* I2Cx, uint8_t *pRxData, uint32_t u32Size)
{
    uint32_t u32TimeOut = TIMEOUT;

    for(uint32_t i=0ul; i<u32Size; i++)
    {
        /* if the last byte receive, need config NACK*/
        if(i == (u32Size - 1ul))
        {
            I2C_NackConfig(I2Cx, Enable);
        }

        /* Wait receive full flag*/
        u32TimeOut = TIMEOUT;
        while(Reset == I2C_GetStatus(I2Cx, I2C_SR_RFULLF))
        {
            if(0ul == (u32TimeOut--))
            {
                return I2C_RET_ERROR;
            }
        }

        /* read data from register*/
        *pRxData++ = I2C_ReadData(I2Cx);
    }
    return I2C_RET_OK;
}

/*****************************************************************************
*	������		�� I2C_WriteData
*	����	    �� ͨ��IIC�����������̷�������
*	�������	�� addr		�Ĵ�����ַ
*				   pTxData 	�������ݵ�ַ
*				   u32Size 	�������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void I2C_WriteData(M4_I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t addr,uint8_t *pTxData, uint32_t u32Size)
{
    /* I2C master data write*/
    Master_StartOrRestart(I2Cx, GENERATE_START);

    Master_SendAddr(I2Cx, (uint8_t)Device_Addr|ADDRESS_W);
	
	Master_WriteData(I2Cx, &addr, 1);
   
    Master_WriteData(I2Cx, pTxData, u32Size);

    Master_Stop(I2Cx);
}

/*****************************************************************************
*	������		�� I2C_ReceiveData
*	����	    �� ͨ��IIC�����������̽�������
*	�������	�� addr		�Ĵ�����ַ
*				   pTxData 	�������ݵ�ַ
*				   u32Size 	�������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void I2C_ReceiveData(M4_I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t addr,uint8_t *pRxData, uint32_t u32Size)
{
    /* I2C master data read*/
    Master_StartOrRestart(I2Cx,GENERATE_START);
   
    Master_SendAddr(I2Cx, (uint8_t)Device_Addr|ADDRESS_W);
	
	Master_WriteData(I2Cx, &addr, 1);
	
	Master_StartOrRestart(I2Cx, GENERATE_RESTART);
	
	Master_SendAddr(I2Cx, (uint8_t)Device_Addr|ADDRESS_R);

    Master_ReceiveData(I2Cx, pRxData, u32Size);

    Master_Stop(I2Cx);

}
