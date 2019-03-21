/**
  ******************************************************************************
  * @file    CerviGUI.c
  * @author  DannLab
  * @brief   This file contains GUI for demo application
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "CerviGUI.h"

GUI_MenuTypeDef GUI_Menu;

/* LCD Config ----------------------------------------------------------------*/
/**
  * @brief  LCD configuration
  * @param  None
  * @retval None
  */
/* ---------------------------------------------------------------------------*/
void LCD_Config(void)
{
  /* LCD Initialization */
  BSP_LCD_Init();

  /* LCD Initialization */
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS+(BSP_LCD_GetXSize()*BSP_LCD_GetYSize()*4));

  /* Enable the LCD */
  BSP_LCD_DisplayOn();

  /* Select the LCD Background Layer  */
  BSP_LCD_SelectLayer(0);

  /* Clear the Background Layer */
  BSP_LCD_Clear(LCD_COLOR_BLACK);

  /* Select the LCD Foreground Layer  */
  BSP_LCD_SelectLayer(1);

  /* Clear the Foreground Layer */
  BSP_LCD_Clear(LCD_COLOR_BLACK);

  /* Configure the transparency for foreground and background :
     Increase the transparency */
  BSP_LCD_SetTransparency(0, 0);
  BSP_LCD_SetTransparency(1, 100);
}

/* Error_Handler -------------------------------------------------------------*/
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Turn LED1 on */
  BSP_LED_On(LED1);
  while(1)
  {
  }
}
/* ---------------------------------------------------------------------------*/

/* LoadGraphic ---------------------------------------------------------------*/
/**
  * @brief  Load graphic from SD
  * @param  None
  * @retval None
  */
/* ---------------------------------------------------------------------------*/
void LoadGraphics(void)
{
	int counter = 0;
	char* pDirectoryFiles[MAX_BMP_FILES];
	uint8_t  ubNumberOfFiles = 0;

	BSP_SD_Init();

	/* Select the LCD Foreground Layer  */
	BSP_LCD_SelectLayer(1);

	/* Clear the Foreground Layer */
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	/* Configure the transparency for foreground and background :
	 Increase the transparency */
	BSP_LCD_SetTransparency(0, 0);
	BSP_LCD_SetTransparency(1, 100);

	while(BSP_SD_IsDetected() != SD_PRESENT)
	{
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"  Please insert SD Card                  ");
	}


	/*##-2- Link the SD Card disk I/O driver ###################################*/
	if(FATFS_LinkDriver(&SD_Driver, SD_Path) == 0)
	{
	/*##-3- Initialize the Directory Files pointers (heap) ###################*/
	for (counter = 0; counter < MAX_BMP_FILES; counter++)
	{
	  pDirectoryFiles[counter] = malloc(MAX_BMP_FILE_NAME);
	  if(pDirectoryFiles[counter] == NULL)
	  {
		/* Set the Text Color */
		BSP_LCD_SetTextColor(LCD_COLOR_RED);

		BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"  Cannot allocate memory ");

		while(1)
		{
		}
	  }
	}

	/* Get the BMP file names on root directory */
	ubNumberOfFiles = Storage_GetDirectoryBitmapFiles("/Media", pDirectoryFiles);

	if (ubNumberOfFiles == 0)
	{
	  for (counter = 0; counter < MAX_BMP_FILES; counter++)
	  {
		free(pDirectoryFiles[counter]);
	  }
	  BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"  No Bitmap files...      ");
	  while(1)
	  {
	  }
	}
	}
	else
	{
	/* FatFs Initialization Error */
	Error_Handler();
	}
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Startup GUI
  * @param  None
  * @retval None
  */
/* ---------------------------------------------------------------------------*/
void CerviGUI_Init(void)
{
	/*##-1- Configure LCD ######################################################*/
	LCD_Config();

	LoadGraphics();

	/* Touchscreen initialization */
	if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR)
	{
	  printf("BSP_TS_Init error\n");
	}
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Startup GUI
  * @param  None
  * @retval None
  */
/* ---------------------------------------------------------------------------*/
void GUI_Intro(void)
{
	uint8_t *uwInternelBuffer;
	uwInternelBuffer = (uint8_t *)0xC0260000;

	uint32_t transparency = 0;
	uint8_t str[30];

	BSP_LCD_SetTransparency(0, 0);
	BSP_LCD_SetTransparency(1, 100);

	/* Set LCD foreground Layer */
	BSP_LCD_SelectLayer(1);

	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"  Loading...                             ");


	BSP_LCD_SetTransparency(1, 255);
	BSP_LCD_SetTransparency(0, 255);

	#define delay 35

//--------------- new thing -----------------------------------------------------------

	BSP_LCD_SelectLayer(1);

	HAL_Delay(1000);

	for(int a=1; a<8; a++)
	{
		sprintf ((char*)str, "GRsource/Intro/%d.bmp", a);
		/* Open a file and copy its content to an internal buffer */
		Storage_OpenReadFile(uwInternelBuffer+(a-1)*391800, (const char*)str);
	}

	for(int a=1; a<8; a++)
	{
		/* Write bmp file on LCD frame buffer */
		BSP_LCD_DrawBitmap(0, 0, uwInternelBuffer+(a-1)*391800);

		HAL_Delay(delay);
	}

// Load images to SDRAM ---------------------------------------------------------------

	Storage_OpenReadFile(ADR_cervi, "Media/cervi.bmp");
	Storage_OpenReadFile(ADR_iomenu, "GRsource/iomenu.bmp");
	Storage_OpenReadFile(ADR_piomenu, "GRsource/piomenu.bmp");
	Storage_OpenReadFile(ADR_servo, "GRsource/servo.bmp");
	Storage_OpenReadFile(ADR_pservo, "GRsource/pservo.bmp");
	Storage_OpenReadFile(ADR_miomenu, "GRsource/miomenu.bmp");
	Storage_OpenReadFile(ADR_mstepmenu, "GRsource/mstpmenu.bmp");
	Storage_OpenReadFile(ADR_on, "GRsource/on.bmp");
	Storage_OpenReadFile(ADR_off, "GRsource/off.bmp");
	Storage_OpenReadFile(ADR_back1, "GRsource/back1.bmp");
	Storage_OpenReadFile(ADR_pback1, "GRsource/pback1.bmp");
	Storage_OpenReadFile(ADR_plugin, "GRsource/plugin.bmp");
	Storage_OpenReadFile(ADR_plugout, "GRsource/plugout.bmp");

	HAL_Delay(500);

	 /* Set LCD foreground Layer */
	BSP_LCD_SelectLayer(0);
	BSP_LCD_DrawBitmap(0, 0, ADR_cervi);

	/* Configure the transparency for foreground layer : decrease the transparency */
	for (transparency = 255; transparency > 0; transparency--)
	{
		BSP_LCD_SetTransparency(1, transparency);

	  /* Insert a delay of display */
	  HAL_Delay(1);
	}

	HAL_Delay(1400);

	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_LCD_DrawBitmap(250, 36, ADR_iomenu);
	BSP_LCD_DrawBitmap(30, 36, ADR_servo);

	for (transparency = 0; transparency < 255; transparency++)
	{
		BSP_LCD_SetTransparency(1, transparency);

	  /* Insert a delay of display */
	  HAL_Delay(1);
	}
	 /* Set LCD background Layer */
	BSP_LCD_SelectLayer(0);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Startup GUI
  * @param  None
  * @retval None
  */
/* ---------------------------------------------------------------------------*/
uint8_t GUI_MainMenu(void)
{
	TS_StateTypeDef  TS_State = {0};
	//TS_StateTypeDef TS_Status;

	//uint8_t *uwInternelBuffer;
	//uwInternelBuffer = (uint8_t *)0xC0260000;

	int x1, y1;

	BSP_LCD_SelectLayer(1);
	//BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_LCD_DrawBitmap(250, 36, ADR_iomenu);
	BSP_LCD_DrawBitmap(30, 36, ADR_servo);

	while(1)
	{
		BSP_TS_GetState(&TS_State);
		if(TS_State.touchEventId[0] == TOUCH_EVENT_PRESS_DOWN)
		{
			x1 = TS_State.touchX[0];
			y1 = TS_State.touchY[0];

			BSP_TS_ResetTouchData(&TS_State);

			if(30<x1 && x1<230 && 36<y1 && y1<236)
			{
				BSP_LCD_DrawBitmap(30, 36, ADR_pservo);
				return (JOG_MOTOR_MENU);
				break;
			}
			else

			if(250<x1 && x1<450 && 36<y1 && y1<236)
			{
				BSP_LCD_DrawBitmap(250, 36, ADR_piomenu);
				return (IO_MENU);
				break;
			}
		}
	}
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Startup GUI
  * @param  None
  * @retval None
  */
/* ---------------------------------------------------------------------------*/
void GUI_IOMenu(void)
{
	TS_StateTypeDef  TS_State = {0};

	int x1, y1;

	//uint8_t *uwInternelBuffer;
	//uwInternelBuffer = (uint8_t *)0xC0260000;

	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_LCD_SetTextColor(IOMenuColor);

	for(int a=0; a<36; a++)
	{
		BSP_LCD_DrawHLine(0,a,480);
		HAL_Delay(5);
	}

	BSP_LCD_DrawBitmap(0, 0, ADR_miomenu);
	BSP_LCD_DrawBitmap(20, 100, ADR_off);
	BSP_LCD_DrawBitmap(20, 180, ADR_off);
	BSP_LCD_DrawBitmap(400, 20, ADR_back1);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font16);

	BSP_LCD_DisplayStringAt(130, 120, (uint8_t*) "Change output status - LED1", LEFT_MODE);
	BSP_LCD_DisplayStringAt(130, 200, (uint8_t*) "Check input status - switch 1", LEFT_MODE);

	//if led is on turn off
	if(GPIOI->IDR & (1<<1))
	{
		BSP_LCD_DrawBitmap(20, 100, ADR_on);
	}
	else
	{
		BSP_LCD_DrawBitmap(20, 100, ADR_off);
	}

	while(1)
	{
		BSP_TS_GetState(&TS_State);
		if(TS_State.touchEventId[0] == TOUCH_EVENT_PRESS_DOWN)
		{
			x1 = TS_State.touchX[0];
			y1 = TS_State.touchY[0];

			BSP_TS_ResetTouchData(&TS_State);

			// check back1 button
			if(400<x1 && x1<460 && 20<y1 && y1<80)
			{
				BSP_LCD_DrawBitmap(400, 20, ADR_pback1);
				HAL_Delay(100);
				break;
			}
			else
			// check output button
			if(!(GPIOI->IDR & (1<<1)))
			{
				if(70<x1 && x1<120 && 100<y1 && y1<157)
				{
					BSP_LCD_DrawBitmap(20, 100, ADR_on);
					BSP_LED_On(LED1);
				}
			}
			else
			{
				if(20<x1 && x1<70 && 100<y1 && y1<157)
				{
					BSP_LCD_DrawBitmap(20, 100, ADR_off);
					BSP_LED_Off(LED1);
				}
			}
		}
		if(BSP_PB_GetState(BUTTON_TAMPER) != RESET)
		{
			BSP_LCD_DrawBitmap(20, 180, ADR_on);
		}
		else
			BSP_LCD_DrawBitmap(20, 180, ADR_off);
	}
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Startup GUI
  * @param  None
  * @retval None
  */
/* ---------------------------------------------------------------------------*/
void GUI_STPMenu(void)
{
	TS_StateTypeDef  TS_State = {0};

	uint8_t data;

	int exit=0, exit_menu = 0, constat = 0;

	int x1, y1;

	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_LCD_SetTextColor(StepperMenuColor);

	for(int a=0; a<36; a++)
	{
		BSP_LCD_DrawHLine(0,a,480);
		HAL_Delay(5);
	}

	BSP_LCD_DrawBitmap(0, 0, ADR_mstepmenu);
	BSP_LCD_DrawBitmap(400, 20, ADR_back1);
	BSP_LCD_DrawBitmap(80, 110, ADR_plugout);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font16);

	BSP_LCD_DrawRect(70, 100, 330, 100);

	BSP_LCD_DisplayStringAt(180, 110, (uint8_t*) "                   ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(180, 130, (uint8_t*) "System disconnected", LEFT_MODE);
	BSP_LCD_DisplayStringAt(180, 150, (uint8_t*) "-tap to connect-   ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(180, 170, (uint8_t*) "                   ", LEFT_MODE);

	while(!exit)
	{
		BSP_TS_GetState(&TS_State);
		if(TS_State.touchEventId[0] == TOUCH_EVENT_PRESS_DOWN)
		{
			x1 = TS_State.touchX[0];
			y1 = TS_State.touchY[0];

			BSP_TS_ResetTouchData(&TS_State);

			// check back1 button
			if(400<x1 && x1<460 && 20<y1 && y1<80)
			{
				BSP_LCD_DrawBitmap(400, 20, ADR_pback1);
				HAL_Delay(100);
				exit=1;
			}
			else
			// check connection button
			if(70<x1 && x1<400 && 100<y1 && y1<200 && constat==0)
			{
				//BSP_LCD_DisplayStringAt(180, 110, (uint8_t*) "Processing...      ", LEFT_MODE);
				BSP_LCD_DisplayStringAt(180, 130, (uint8_t*) "Trying to connect  ", LEFT_MODE);
				BSP_LCD_DisplayStringAt(180, 150, (uint8_t*) "USART(115200bps)   ", LEFT_MODE);
				BSP_LCD_DisplayStringAt(180, 170, (uint8_t*) "(8bit,1s,no par)   ", LEFT_MODE);

				SendString("Do you want to connect? [y/n]\n");

				constat = 1;
			}
		}
		if(constat == 1)
		{
			data = ReciveChar();
			if(data == 'y')
			{
				BSP_LCD_DrawBitmap(80, 110, ADR_plugin);
				BSP_LCD_DisplayStringAt(180, 130, (uint8_t*) "Connected          ", LEFT_MODE);

				for(int c=0; c<20; c++)
					SendString("\n");

				SendString("Connected...\n\n What do you want to do?\n");
				SendString("1 - Disconnect\n");
				SendString("2 - Move axis\n");
				SendString("3 - Read axis coordinates\n");

				for(int c=0; c<11; c++)
					SendString("\n");

				while(!exit_menu)
				{
					data = ReciveChar();

					switch(data)
					{
					case '1':
						BSP_LCD_DrawBitmap(80, 110, ADR_plugout);
						BSP_LCD_DisplayStringAt(180, 130, (uint8_t*) "Disconnected       ", LEFT_MODE);
						SendString("\n\nDisconnected\n");
						exit_menu = 1;
						break;

					case '2':
					case '3':
						SendString("\n\nCommand not included\n");

						HAL_Delay(2000);

						SendString("Connected...\n What do you want to do?\n");
						SendString("1 - Disconnect\n");
						SendString("2 - Move axis\n");
						SendString("3 - Read axis coordinates\n");

						for(int c=0; c<11; c++)
							SendString("\n");
						break;
					}
				}
			}
		}
	}
}

void USART1_IRQHandler(void)
{
}

/************************ Dann Lab *****************************END OF FILE****/
