/*****************************************************************************
*1
*
*  Module Name ��Sensor����
*  File Name   ��sensor.c
*  Description ��Sensor����
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
#include "sensor.h"

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
*	������		�� IIC1_Sensor_Init
*	����	    �� ��ʼ��IIC1_Sensorͨ��
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void IIC1_Sensor_Init(void)
{
	stc_i2c_init_t stcI2cInit;
    stc_clk_freq_t stcClkFreq;
	
    /* Initialize I2C port*/
    PORT_SetFunc(I2C1_SENSOR_SCL_PORT, I2C1_SENSOR_SCL_PIN, Func_I2c1_Scl, Disable);
    PORT_SetFunc(I2C1_SENSOR_SDA_PORT, I2C1_SENSOR_SDA_PIN, Func_I2c1_Sda, Disable);

    /* Enable I2C1 Peripheral*/
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_PERIPH_I2C1, Enable);
	
    /* Initialize I2C peripheral and enable function*/
    I2C_DeInit(I2C1_SENSOR_CH);
	
	/* Get system clock frequency */
    CLK_GetClockFreq(&stcClkFreq);

    MEM_ZERO_STRUCT(stcI2cInit);
    stcI2cInit.enI2cMode = I2cMaster;
    stcI2cInit.u32Pclk3 = stcClkFreq.pclk3Freq;
    stcI2cInit.u32Baudrate = I2C1_SENSOR_BAUDRATE;
    stcI2cInit.u32SclTime = 0ul;
    I2C_Init(I2C1_SENSOR_CH, &stcI2cInit);

    I2C_Cmd(I2C1_SENSOR_CH, Enable);
}

/*****************************************************************************
*	������		�� I2C_WriteData
*	����	    �� ͨ��IIC�����������̷���Sensor����
*	�������	�� addr		�Ĵ�����ַ
*				   pTxData 	�������ݵ�ַ
*				   u32Size 	�������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void Sensor_WriteData(uint8_t addr,uint8_t *pTxData, uint32_t u32Size)
{
	I2C_WriteData(I2C1_SENSOR_CH,SENSOR_ADDRESS, addr, pTxData, u32Size);
}

/*****************************************************************************
*	������		�� Sensor_ReceiveData
*	����	    �� ͨ��IIC�����������̽���Sensor����
*	�������	�� addr		�Ĵ�����ַ
*				   pTxData 	�������ݵ�ַ
*				   u32Size 	�������ݳ���
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void Sensor_ReceiveData(uint8_t addr,uint8_t *pRxData, uint32_t u32Size)
{
	I2C_ReceiveData(I2C1_SENSOR_CH, SENSOR_ADDRESS, addr, pRxData, u32Size);
}
