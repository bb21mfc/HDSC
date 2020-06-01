/*****************************************************************************
*Copyright(C) 2017,GosuncnWelink
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

/***************************************************************************
* Include Files                       �ļ�����
***************************************************************************/
#include "charge.h"

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

/*****************************************************************************
*	������		�� IIC2_Charge_Init
*	����	    �� ��ʼ��IIC2_Chargeͨ��
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void IIC2_Charge_Init(void)
{
	stc_i2c_init_t stcI2cInit;
    stc_clk_freq_t stcClkFreq;
	
    /* Initialize I2C port*/
    PORT_SetFunc(I2C2_CHARGE_SCL_PORT, I2C2_CHARGE_SCL_PIN, Func_I2c2_Scl, Disable);
    PORT_SetFunc(I2C2_CHARGE_SDA_PORT, I2C2_CHARGE_SDA_PIN, Func_I2c2_Sda, Disable);

    /* Enable I2C1 Peripheral*/
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_PERIPH_I2C2, Enable);
	
    /* Initialize I2C peripheral and enable function*/
    I2C_DeInit(I2C2_CHARGE_CH);
	
	/* Get system clock frequency */
    CLK_GetClockFreq(&stcClkFreq);

    MEM_ZERO_STRUCT(stcI2cInit);
    stcI2cInit.enI2cMode = I2cMaster;
    stcI2cInit.u32Pclk3 = stcClkFreq.pclk3Freq;
    stcI2cInit.u32Baudrate = I2C2_CHARGE_BAUDRATE;
    stcI2cInit.u32SclTime = 0ul;
    I2C_Init(I2C2_CHARGE_CH, &stcI2cInit);

    I2C_Cmd(I2C2_CHARGE_CH, Enable);
}

/*****************************************************************************
*	������		�� Charge_WriteData
*	����	    �� ͨ��IIC�����������̷���Charge����
*	�������	�� addr		�Ĵ�����ַ
*				   pTxData 	�������ݵ�ַ
*				   u32Size 	�������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void Charge_WriteData(uint8_t addr,uint8_t *pTxData, uint32_t u32Size)
{
	I2C_WriteData(I2C2_CHARGE_CH,CHARGE_ADDRESS, addr, pTxData, u32Size);
}

/*****************************************************************************
*	������		�� Charge_ReceiveData
*	����	    �� ͨ��IIC�����������̽���Charge����
*	�������	�� addr		�Ĵ�����ַ
*				   pTxData 	�������ݵ�ַ
*				   u32Size 	�������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void Charge_ReceiveData(uint8_t addr,uint8_t *pRxData, uint32_t u32Size)
{
	I2C_ReceiveData(I2C2_CHARGE_CH, CHARGE_ADDRESS, addr, pRxData, u32Size);
}
