/**
  ******************************************************************************
  * @file    STEPconfig.h
  * @author  DannLab
  * @brief   This file contains Stepper motor control for demo application
  ******************************************************************************
  * @attention
  *	This code works for stm32f429 Cortex M4 and have no test run on
  *	Discovery STM32F746G-DISCO board
  *
  *	Outputs ports not power on!
  ******************************************************************************
  */
#ifndef STEPCONFIG_H_
#define STEPCONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"

/* Defines -------------------------------------------------------------------*/
#define Xaxis 0
#define Yaxis 1
#define Zaxis 2

#define X_DIR_1	GPIOC->ODR |= (1<<5);
#define X_DIR_0	GPIOC->ODR &= ~(1<<5);

#define Y_DIR_1	GPIOA->ODR |= (1<<5);
#define Y_DIR_0	GPIOA->ODR &= ~(1<<5);

#define Z_DIR_1	GPIOH->ODR |= (1<<4);
#define Z_DIR_0	GPIOH->ODR &= ~(1<<4);

/* Private variables ---------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/
void Init_Xaxis( void );
void Init_Yaxis( void );
void Init_Zaxis( void );

int G1X( int X, int F );
int G1Y( int Y, int F );
int G1Z( int Z, int F );

int MoveAxis(int axis, int distance, uint16_t feed);

int X_BusyFlag( void );
int Y_BusyFlag( void );

/**
 *  @brief Stepper motor varibles
 */
typedef enum
{
	FeedRate,			/*!< Stepper motor speed */
	Position,			/*!< Stepper motor position */
	Accelerate			/*!< Stepper motor accelerate */

} StepperStatTypeDef;

#endif /* STEPCONFIG_H_ */
