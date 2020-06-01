/*****************************************************************************
*Copyright(C) 2017,GosuncnWelink
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

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "charge.h"

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

/***************************************************************************
* Function Declare                  外部函数声明
***************************************************************************/

/***************************************************************************
* Variables                           全局变量
***************************************************************************/

/***************************************************************************
* Static Variables                   本地全局变量
***************************************************************************/

/*****************************************************************************
*	函数名		： IIC2_Charge_Init
*	功能	    ： 初始化IIC2_Charge通道
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
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
*	函数名		： Charge_WriteData
*	功能	    ： 通过IIC总线完整流程发送Charge数据
*	输入参数	： addr		寄存器地址
*				   pTxData 	发送数据地址
*				   u32Size 	发送数据长度
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Charge_WriteData(uint8_t addr,uint8_t *pTxData, uint32_t u32Size)
{
	I2C_WriteData(I2C2_CHARGE_CH,CHARGE_ADDRESS, addr, pTxData, u32Size);
}

/*****************************************************************************
*	函数名		： Charge_ReceiveData
*	功能	    ： 通过IIC总线完整流程接收Charge数据
*	输入参数	： addr		寄存器地址
*				   pTxData 	发送数据地址
*				   u32Size 	发送数据长度
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Charge_ReceiveData(uint8_t addr,uint8_t *pRxData, uint32_t u32Size)
{
	I2C_ReceiveData(I2C2_CHARGE_CH, CHARGE_ADDRESS, addr, pRxData, u32Size);
}
