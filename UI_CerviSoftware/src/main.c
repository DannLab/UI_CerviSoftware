 /**
******************************************************************************
* @file    /UI_CerviSoftware/src/main.c
* @author  DannLab
* @brief   This file provides main program functions
******************************************************************************
* @attention
*
* This is a simple demo program for Cervi Robotics
*
* This example provide:
*
* I/O status menu:
* This menu allows change and display I/O status
*
* Stepper motor control menu
* JOG menu for manual stepper motor control
*
* Online motor control
* This is extension for manual JOG menu that can provide
* control motor through UART
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function ----------------------------------------------------------*/
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	//uwInternelBuffer = (uint8_t *)0xC0260000;

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	- Configure the Flash ART accelerator on ITCM interface
	- Configure the Systick to generate an interrupt each 1 msec
	- Set NVIC Group Priority to 4
	- Global MSP (MCU Support Package) initialization
	*/
	HAL_Init();

	/* Configure the system clock to 200 MHz */
	SystemClock_Config();

	/* Configure LED1 */
	BSP_LED_Init(LED1);


	/* Configure TAMPER Button */
	BSP_PB_Init(BUTTON_TAMPER, BUTTON_MODE_GPIO);

	/* USART1 initialize */
	POST_USART1_Init();

	CerviGUI_Init();
	GUI_Intro();
	HAL_Delay(300);

	while(1)
	{
		switch(GUI_MainMenu())
		{
		case IO_MENU:
			HAL_Delay(100);
			GUI_IOMenu();
			break;

		case JOG_MOTOR_MENU:
			HAL_Delay(100);
			GUI_STPMenu();
			break;
		}

		BSP_LCD_SelectLayer(1);
		BSP_LCD_Clear(LCD_COLOR_WHITE);
	}
}


//-------------------------------------------------------------------------------------
//--------------- main end ------------------------------------------------------------
//-------------------------------------------------------------------------------------

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 200000000
  *            HCLK(Hz)                       = 200000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 400
  *            PLL_P                          = 2
  *            PLL_Q                          = 8
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 6
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 200 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
