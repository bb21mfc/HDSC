/*****************************************************************************
*Copyright(C) 2017,GosuncnWelink
*
*  Module Name ：ADC相关驱动
*  File Name   ：bsp_adc.c
*  Description ：提供ADC相关驱动
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

/***************************************************************************
* Include Files                       文件引用
***************************************************************************/
#include "bsp_adc.h"

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
static uint16_t m_au16Adc1Value[ADC1_CH_COUNT];
/***************************************************************************
* Function prototypes                 函数原型
***************************************************************************/

void ADC_Initialize(void)
{
	AdcClockConfig();
	AdcInitConfig();
	AdcChannelConfig();
}

/*****************************************************************************
*	函数名		： AdcClockConfig
*	功能	    ： 配置ADC使用时钟源
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： 1) ADCLK max frequency is 60MHz.
*         		   2) If PCLK2 and PCLK4 are selected as the ADC clock,
*            		  the following conditions must be met:
*            		  a. ADCLK(PCLK2) max 60MHz;
*                     b. PCLK4 : ADCLK = 1:1, 2:1, 4:1, 8:1, 1:2, 1:4
*****************************************************************************/
static void AdcClockConfig(void)
{
    stc_clk_xtal_cfg_t stcXtalCfg;
    stc_clk_upll_cfg_t stcUpllCfg;

    MEM_ZERO_STRUCT(stcXtalCfg);
    MEM_ZERO_STRUCT(stcUpllCfg);

    /* Use XTAL as UPLL source. */
    stcXtalCfg.enFastStartup = Enable;
    stcXtalCfg.enMode = ClkXtalModeOsc;
    stcXtalCfg.enDrv = ClkXtalLowDrv;
    CLK_XtalConfig(&stcXtalCfg);
	
    CLK_XtalCmd(Enable);
	CLK_SetPllSource(ClkPllSrcXTAL);
	
    /* Set UPLL out 240MHz. */
    /* upll = 8M(XTAL) / pllmDiv * plln */
	stcUpllCfg.pllmDiv = 2u;
    stcUpllCfg.plln    = 60u;
    stcUpllCfg.PllpDiv = 16u;
    stcUpllCfg.PllqDiv = 16u;
    stcUpllCfg.PllrDiv = 16u;
    
    CLK_UpllConfig(&stcUpllCfg);
    CLK_UpllCmd(Enable);
    CLK_SetPeriClkSource(ClkPeriSrcUpllr);

}

/*****************************************************************************
*	函数名		： AdcInitConfig
*	功能	    ： 配置ADC
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void AdcInitConfig(void)
{
    stc_adc_init_t stcAdcInit;

    MEM_ZERO_STRUCT(stcAdcInit);

    stcAdcInit.enDataAlign  = AdcDataAlign_Right;
    stcAdcInit.enAutoClear  = AdcClren_Disable;
    stcAdcInit.enScanMode   = ADC1_SCAN_MODE;
    /* 1. Enable ADC1. */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_PERIPH_ADC1, Enable);
    /* 2. Initialize ADC1. */
    ADC_Init(M4_ADC1, &stcAdcInit);

}

/*****************************************************************************
*	函数名		： AdcChannelConfig
*	功能	    ： ADC channel configuration.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void AdcChannelConfig(void)
{
    stc_adc_ch_cfg_t stcChCfg;
	uint8_t ADC1_Sample = 0x50;

    MEM_ZERO_STRUCT(stcChCfg);

    stcChCfg.u32Channel  = ADC1_SA_NORMAL_CHANNEL;
    stcChCfg.u8Sequence  = ADC_SEQ_A;
    stcChCfg.pu8SampTime = &ADC1_Sample;
    /* 1. Set the ADC pin to analog mode. */
    AdcSetChannelPinMode(M4_ADC1, ADC1_SA_NORMAL_CHANNEL, Pin_Mode_Ana);
    /* 2. Add ADC channel. */
    ADC_AddAdcChannel(M4_ADC1, &stcChCfg);

    /* 3. Configure the average channel if you need. */
    ADC_ConfigAvg(M4_ADC1, AdcAvcnt_32);
    /* 4. Add average channel if you need. */
    //ADC_AddAvgChannel(M4_ADC1, ADC1_AVG_CHANNEL);

}

/*****************************************************************************
*	函数名		： AdcSetChannelPinMode
*	功能	    ： Config the pin which is mapping the channel to analog or digit mode.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void AdcSetChannelPinMode(const M4_ADC_TypeDef *ADCx,
                                 uint32_t u32Channel,
                                 en_pin_mode_t enMode)
{
    uint8_t u8ChIndex;
    uint8_t u8ChOffset = 0u;


    if (M4_ADC1 == ADCx)
    {
        u32Channel &= ADC1_PIN_MASK_ALL;
    }
    else
    {
        u32Channel &= ADC2_PIN_MASK_ALL;
        u8ChOffset = 4u;
    }

    u8ChIndex = 0u;
    while (0u != u32Channel)
    {
        if (u32Channel & 0x1ul)
        {
            AdcSetPinMode((u8ChIndex+u8ChOffset), enMode);
        }

        u32Channel >>= 1u;
        u8ChIndex++;
    }
}

/*****************************************************************************
*	函数名		： AdcSetPinMode
*	功能	    ： Set an ADC pin as analog input mode or digit mode.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
static void AdcSetPinMode(uint8_t u8AdcPin, en_pin_mode_t enMode)
{
    en_port_t enPort = PortA;
    en_pin_t enPin   = Pin00;
    bool bFlag       = true;
    stc_port_init_t stcPortInit;

    MEM_ZERO_STRUCT(stcPortInit);
    stcPortInit.enPinMode = enMode;
    stcPortInit.enPullUp  = Disable;

    switch (u8AdcPin)
    {
    case ADC1_IN0:
        enPort = PortA;
        enPin  = Pin00;
        break;

    case ADC1_IN1:
        enPort = PortA;
        enPin  = Pin01;
        break;

    case ADC1_IN2:
        enPort = PortA;
        enPin  = Pin02;
        break;

    case ADC1_IN3:
        enPort = PortA;
        enPin  = Pin03;
        break;

    case ADC12_IN4:
        enPort = PortA;
        enPin  = Pin04;
        break;

    case ADC12_IN5:
        enPort = PortA;
        enPin  = Pin05;
        break;

    case ADC12_IN6:
        enPort = PortA;
        enPin  = Pin06;
        break;

    case ADC12_IN7:
        enPort = PortA;
        enPin  = Pin07;
        break;

    case ADC12_IN8:
        enPort = PortB;
        enPin  = Pin00;
        break;

    case ADC12_IN9:
        enPort = PortB;
        enPin  = Pin01;
        break;

    case ADC12_IN10:
        enPort = PortC;
        enPin  = Pin00;
        break;

    case ADC12_IN11:
        enPort = PortC;
        enPin  = Pin01;
        break;

    case ADC1_IN12:
        enPort = PortC;
        enPin  = Pin02;
        break;

    case ADC1_IN13:
        enPort = PortC;
        enPin  = Pin03;
        break;

    case ADC1_IN14:
        enPort = PortC;
        enPin  = Pin04;
        break;

    case ADC1_IN15:
        enPort = PortC;
        enPin  = Pin05;
        break;

    default:
        bFlag = false;
        break;
    }

    if (true == bFlag)
    {
        PORT_Init(enPort, enPin, &stcPortInit);
    }
}

/*****************************************************************************
*	函数名		： Get_BAT_ADC_Value
*	功能	    ： 获取电池ADC值.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
uint16_t Get_BAT_ADC_Value(void)
{
	ADC_PollingSa(M4_ADC1, m_au16Adc1Value, ADC1_CH_COUNT, TIMEOUT_MS);
	
	/* ADC1 channel 10 maps pin ADC12_IN10 by default. */
	LOGADC("ADC12_IN10 value %d.\r\n", m_au16Adc1Value[10u]);
        
	return m_au16Adc1Value[10u];
}

/*****************************************************************************
*	函数名		： Get_BAT_Voltage
*	功能	    ： 获取电池电压值.
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
*****************************************************************************/
float Get_BAT_Voltage(void)
{
	float BAT_Voltage = 0.0;
		
	ADC_PollingSa(M4_ADC1, m_au16Adc1Value, ADC1_CH_COUNT, TIMEOUT_MS);
	
	BAT_Voltage = ((float)m_au16Adc1Value[10u] * ADC_VREF) / (float)ADC1_ACCURACY;
	
	LOGADC("ADC12_IN10 value %d.\r\n", m_au16Adc1Value[10u]);
	LOGADC("ADC12_IN10 voltage is %.4fV.\r\n",((float)m_au16Adc1Value[10u] * ADC_VREF) / (float)ADC1_ACCURACY);
	
	return BAT_Voltage;
}

