/**
  ******************************************************************************
  * @file    CerviGUI.h
  * @author  DannLab
  * @brief   This file contains GUI for demo application
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#ifndef CERVIGUI_H_
#define CERVIGUI_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "fatfs_storage.h"
#include "ImageAloc.h"

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/* Defines -------------------------------------------------------------------*/
#define GraphicInternalBuffer	0xC0260000
#define StepperMenuColor		0xFF58585A
#define IOMenuColor				0xFFFF0000

/* Private variables ---------------------------------------------------------*/
FATFS SD_FatFs;  /* File system object for SD card logical drive */
char SD_Path[4]; /* SD card logical drive path */

// Buffer for image processing
//uint8_t *uwInternelBuffer;
//uwInternelBuffer = (uint8_t *)0xC0260000;

/* Private function ----------------------------------------------------------*/
void 	LCD_Config(void);
void 	Error_Handler(void);
void 	LoadGraphics(void);
void 	CerviGUI_Init(void);
void 	GUI_Intro(void);
uint8_t GUI_MainMenu(void);
void	GUI_IOMenu(void);

/**
 *  @brief Sub menu
 */
typedef enum
{
	MAIN_MENU			= 0x00, /*!< Sub menu select menu */
	IO_MENU				= 0x01, /*!< I/O Status menu */
	JOG_MOTOR_MENU		= 0x02, /*!< Stepper motor control menu */
	ONLINE_MOTOR_MENU	= 0x03 /*!< Online motor control menu */

} GUI_MenuTypeDef;

#endif /* CERVIGUI_H_ */
