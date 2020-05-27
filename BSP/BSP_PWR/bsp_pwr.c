/*****************************************************************************
*Copyright(C) 2017,GosuncnWelink
*
*  Module Name ����Դ�����������
*  File Name   ��bsp_pwr.c
*  Description ���ṩ��Դ�����������
*  Author      ��maheng
*  Version     ��
*  Data        ��2020-05-27
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
#include "bsp_pwr.h"

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
*	������		�� ClkInit
*	����	    �� ��ʼ��ʱ����
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� ����ϵͳʱ��Ϊ���168MHz
*****************************************************************************/
void ClkInit(void)
{
    stc_clk_xtal_cfg_t   stcXtalCfg;
    stc_clk_mpll_cfg_t   stcMpllCfg;
    en_clk_sys_source_t  enSysClkSrc;
    stc_clk_sysclk_cfg_t stcSysClkCfg;

    MEM_ZERO_STRUCT(enSysClkSrc);
    MEM_ZERO_STRUCT(stcSysClkCfg);
    MEM_ZERO_STRUCT(stcXtalCfg);
    MEM_ZERO_STRUCT(stcMpllCfg);

    /* Set bus clk div. */
    stcSysClkCfg.enHclkDiv  = ClkSysclkDiv1;  /* Max 168MHz */
    stcSysClkCfg.enExclkDiv = ClkSysclkDiv2;  /* Max 84MHz */
    stcSysClkCfg.enPclk0Div = ClkSysclkDiv1;  /* Max 168MHz */
    stcSysClkCfg.enPclk1Div = ClkSysclkDiv2;  /* Max 84MHz */
    stcSysClkCfg.enPclk2Div = ClkSysclkDiv4;  /* Max 60MHz */
    stcSysClkCfg.enPclk3Div = ClkSysclkDiv4;  /* Max 42MHz */
    stcSysClkCfg.enPclk4Div = ClkSysclkDiv2;  /* Max 84MHz */
    CLK_SysClkConfig(&stcSysClkCfg);

    /* Switch system clock source to MPLL. */
    /* Use Xtal as MPLL source. */
    stcXtalCfg.enMode = ClkXtalModeOsc;
    stcXtalCfg.enDrv = ClkXtalLowDrv;
    stcXtalCfg.enFastStartup = Enable;
    CLK_XtalConfig(&stcXtalCfg);
    CLK_XtalCmd(Enable);

    /* MPLL config. */
    stcMpllCfg.pllmDiv = 1ul;
    stcMpllCfg.plln = 50ul;
    stcMpllCfg.PllpDiv = 4ul;
    stcMpllCfg.PllqDiv = 4ul;
    stcMpllCfg.PllrDiv = 4ul;
    CLK_SetPllSource(ClkPllSrcXTAL);
    CLK_MpllConfig(&stcMpllCfg);

    /* flash read wait cycle setting */
    EFM_Unlock();
    EFM_SetLatency(EFM_LATENCY_5);
    EFM_Lock();

    /* Enable MPLL. */
    CLK_MpllCmd(Enable);

    /* Wait MPLL ready. */
    while (Set != CLK_GetFlagStatus(ClkFlagMPLLRdy))
    {
    }

    /* Switch system clock source to MPLL. */
    CLK_SetSysClkSource(CLKSysSrcMPLL);
}

/*****************************************************************************
*	������		�� Enter_Stop_Mode
*	����	    �� ����Stopģʽ�����͹���
*	�������	�� NULL
*	�������	�� NULL
*	����ֵ˵��  �� NULL
*	����˵��	�� NULL
*****************************************************************************/
void Enter_Stop_Mode(void)
{
	uint32_t u32tmp1, u32tmp2;
	stc_pwc_stop_mode_cfg_t stcPwcStopCfg;
	
	stcPwcStopCfg.enPll 		= Enable;
	stcPwcStopCfg.enStopClk 	= ClkFix;
	stcPwcStopCfg.enStopFlash 	= Wait;
	stcPwcStopCfg.enStpDrvAbi 	= StopHighspeed;
	
	while(Ok != PWC_StopModeCfg(&stcPwcStopCfg))
    {
        Write_Uart_Debug("Config Power Stop Mode Failed!\r\n");
    }
	
	/* Ensure DMA disable */
    u32tmp1 =  M4_DMA1->EN_f.EN;
    u32tmp2 =  M4_DMA2->EN_f.EN;
    while((0ul != u32tmp1) && ((0ul != u32tmp2)))
    {
        Write_Uart_Debug("DMA not Disable, Enter Power Stop Mode Failed!\r\n");
    }
	
	/* Ensure FLASH is ready */
    while(1ul != M4_EFM->FSR_f.RDY)
    {
        Write_Uart_Debug("FLASH not Ready, Enter Power Stop Mode Failed!\r\n");
    }
	
	PWC_EnterStopMd();
}

