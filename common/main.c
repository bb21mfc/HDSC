/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ddl.h"
#include "FreeRTOS.h"
#include "task.h"

#include "bsp_gpio.h"
#include "bsp_uart.h"
#include "bsp_pwr.h"
#include "bsp_adc.h"
#include "bsp_rtc.h"

#include "at_cmd.h"
#include "debug.h"
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
TaskHandle_t   My_Task1_Handle;
TaskHandle_t   My_Task2_Handle;
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
void vTask1Code( void * pvParameters );
void vTask2Code( void * pvParameters );
	
/**
 *******************************************************************************
 ** \brief  Main function of GPIO output
 **
 ** \param  None
 **
 ** \retval int32_t Return value, if needed
 **
 ******************************************************************************/
int32_t main(void)
{
	/* Initialize Clock */
    SystemClkInit();
	
	LED_Gpio_Init();
	USART3_Init();
	ADC_Initialize();
	RTC_Initialize();
	
	xTaskCreate( vTask1Code, "My_Task1", 512, NULL, 6, &My_Task1_Handle);

	xTaskCreate( vTask2Code, "My_Task2", 512, NULL, 7, &My_Task2_Handle);

	Task_AT_Process_Start();
	
	vTaskStartScheduler();

    while(1)
    {
        /* de-init if necessary */
        //PORT_DeInit();
    };
}

void vTask1Code( void * pvParameters )
{
	while(1)
	{
		LED0_TOGGLE();
		LED2_TOGGLE();
		
		vTaskDelay(500);
	}
}

void vTask2Code( void * pvParameters )
{
	uint16_t i = 0;
	
	while(1)
	{
		LED_RED_TOGGLE();
		LED3_TOGGLE();
		
		Write_Uart_Debug("i = %d\r\n",i);
		i++;
		if(i == 10)
		{
			i = 0;
			Set_Wakeup_Time(10);
			Enter_Stop_Mode();
		}
		
		vTaskDelay(1000);
	}
}


/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
