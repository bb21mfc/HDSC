/*****************************************************************************
*1
*
*  Module Name ：电源管理相关驱动
*  File Name   ：bsp_pwr.c
*  Description ：提供电源管理相关驱动
*  Author      ：maheng
*  Version     ：
*  Data        ：2020-05-27
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
#include "bsp_pwr.h"

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

/***************************************************************************
* Function prototypes                 函数原型
***************************************************************************/

/*****************************************************************************
*	函数名		： ClkInit
*	功能	    ： 初始化时钟树
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： 配置系统时钟为最高168MHz
*****************************************************************************/
void SystemClkInit(void)
{
    stc_clk_xtal_cfg_t   stcXtalCfg;
    stc_clk_mpll_cfg_t   stcMpllCfg;
    stc_clk_sysclk_cfg_t stcSysClkCfg;
	stc_sram_config_t  stcSramConfig;

    MEM_ZERO_STRUCT(stcSysClkCfg);
    MEM_ZERO_STRUCT(stcXtalCfg);
    MEM_ZERO_STRUCT(stcMpllCfg);
	MEM_ZERO_STRUCT(stcSramConfig);

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
	/* Set MPLL out 168MHz. */
	/* sysclk = 8M / pllmDiv * plln / PllpDiv */
	stcMpllCfg.pllmDiv = 1u;
    stcMpllCfg.plln    = 42u;
    stcMpllCfg.PllpDiv = 2u;
    stcMpllCfg.PllqDiv = 16u;
    stcMpllCfg.PllrDiv = 16u;
    CLK_SetPllSource(ClkPllSrcXTAL);
    CLK_MpllConfig(&stcMpllCfg);

    /* flash read wait cycle setting */
    EFM_Unlock();
    EFM_SetLatency(EFM_LATENCY_5);
    EFM_Lock();
	
	/* If the system clock frequency is higher than 100MHz and SRAM1, SRAM2, SRAM3 or Ret_SRAM is used,
       the wait cycle must be set. */
    stcSramConfig.u8SramIdx     = Sram12Idx | Sram3Idx | SramRetIdx;
    stcSramConfig.enSramRC      = SramCycle2;
    stcSramConfig.enSramWC      = SramCycle2;
    stcSramConfig.enSramEccMode = EccMode0;
    stcSramConfig.enSramEccOp   = SramNmi;
    stcSramConfig.enSramPyOp    = SramNmi;
    SRAM_Init(&stcSramConfig);

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
*	函数名		： Enter_Stop_Mode
*	功能	    ： 进入Stop模式，降低功耗
*	输入参数	： NULL
*	输出参数	： NULL
*	返回值说明  ： NULL
*	其他说明	： NULL
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
        LOGPWC("Config Power Stop Mode Failed!\r\n");
    }
	
	/* Ensure DMA disable */
    u32tmp1 =  M4_DMA1->EN_f.EN;
    u32tmp2 =  M4_DMA2->EN_f.EN;
    while((0ul != u32tmp1) && ((0ul != u32tmp2)))
    {
        LOGPWC("DMA not Disable, Enter Power Stop Mode Failed!\r\n");
    }
	
	/* Ensure FLASH is ready */
    while(1ul != M4_EFM->FSR_f.RDY)
    {
        LOGPWC("FLASH not Ready, Enter Power Stop Mode Failed!\r\n");
    }
	
	LOGPWC("Enter Stop Mode!\r\n");
	PWC_EnterStopMd();
}
static void WKTM_IrqCallback(void);

void Set_Wakeup_Time(uint16_t Wakeup_Time)
{
	stc_pwc_wktm_ctl_t stc_pwc_wktm_ctl;
	stc_irq_regi_conf_t stcIrqRegiCfg;
	
	MEM_ZERO_STRUCT(stc_pwc_wktm_ctl);
	MEM_ZERO_STRUCT(stcIrqRegiCfg);
	
//	PWC_ClearWakeup1Flag(PWC_WKTM_WKUPFLAG);

//	stc_pwc_wktm_ctl.enWkclk 		= Wk64hz;
//	stc_pwc_wktm_ctl.u16WktmCmp 	= 0;
//	stc_pwc_wktm_ctl.enWktmEn 		= Disable;
//	
//	PWC_WktmControl( &stc_pwc_wktm_ctl );

	
	stc_pwc_wktm_ctl.enWkclk 		= Wk64hz;
	stc_pwc_wktm_ctl.u16WktmCmp 	= Wakeup_Time*64;
	stc_pwc_wktm_ctl.enWktmEn 		= Enable;
	stc_pwc_wktm_ctl.enWkOverFlag   = UnEqual;
	
	PWC_WktmControl( &stc_pwc_wktm_ctl );
	
	PWC_StopWkupCmd(PWC_STOPWKUPEN_WKTM,Enable);
	
//	stcIrqRegiCfg.enIntSrc		= INT_WKTM_PRD;
//	stcIrqRegiCfg.enIRQn		= Int025_IRQn;
//	stcIrqRegiCfg.pfnCallback   = &WKTM_IrqCallback;
//	
//	enIrqRegistration(&stcIrqRegiCfg);
//    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
//    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
//    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
	
}

static void WKTM_IrqCallback(void)
{
	//Write_Uart_Debug("WKTM_IrqCallback Happen\r\n");
	LED0_TOGGLE();
	LED2_TOGGLE();
}
