/**
  ******************************************************************************
  * @file    USART1config.h
  * @author  DannLab
  * @brief   This file contains USART1 configuration
  ******************************************************************************
  * @attention
  * USART configuration for Discovery F746G
  * Connection through USART1-> St-link->/dev/ttyACM0
  *
  ******************************************************************************
  */

#ifndef USART1CONFIG_H_
#define USART1CONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"
#include "stm32f7xx_hal_usart.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_uart_ex.h"
#include "stm32f7xx_ll_usart.h"

/* Defines -------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/
void POST_USART1_Init( void );
void SendString(const char* str);
uint8_t ReciveChar(void);
void rec(void);


#endif /* USART1CONFIG_H_ */
