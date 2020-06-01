/*****************************************************************************
*1
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

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "sensor.h"

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
*	函数名		： IIC1_Sensor_Init
*	功能	    ： 初始化IIC1_Sensor通道
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
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
*	函数名		： I2C_WriteData
*	功能	    ： 通过IIC总线完整流程发送Sensor数据
*	输入参数	： addr		寄存器地址
*				   pTxData 	发送数据地址
*				   u32Size 	发送数据长度
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Sensor_WriteData(uint8_t addr,uint8_t *pTxData, uint32_t u32Size)
{
	I2C_WriteData(I2C1_SENSOR_CH,SENSOR_ADDRESS, addr, pTxData, u32Size);
}

/*****************************************************************************
*	函数名		： Sensor_ReceiveData
*	功能	    ： 通过IIC总线完整流程接收Sensor数据
*	输入参数	： addr		寄存器地址
*				   pTxData 	发送数据地址
*				   u32Size 	发送数据长度
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
void Sensor_ReceiveData(uint8_t addr,uint8_t *pRxData, uint32_t u32Size)
{
	I2C_ReceiveData(I2C1_SENSOR_CH, SENSOR_ADDRESS, addr, pRxData, u32Size);
}
