/**
  ******************************************************************************
  * @file    STEPconfig.c
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
#include "STEPconfig.h"

// ----------------------------------------------------------------------------
//
//	X axis timer config
//
// ----------------------------------------------------------------------------
void Init_Xaxis( void )
{
// ----------------------------------------------------------------------------
// Direction pin
// ----------------------------------------------------------------------------
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER5_0;

// ----------------------------------------------------------------------------
// Timer 2 set slave ( counting axis distance in pulses )
// ----------------------------------------------------------------------------
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // set clock on tim2

	TIM2->PSC = 0; // prescaler
	TIM2->ARR = 10; // compare
	TIM2->CCR1= 0; // duty

	TIM2->SMCR |= TIM_SMCR_TS_1; // Internal trigger 2 ITR2
	TIM2->SMCR |= TIM_SMCR_SMS; // Slave mode external

	TIM2->CR1 |= TIM_CR1_ARPE; // autoreload on - changes on fly
	TIM2->EGR |= TIM_EGR_UG; // trigger update event to reload timer registers
	TIM2->DIER |= TIM_DIER_UIE; // enable update interrupt

// ----------------------------------------------------------------------------
	//NVIC->ISER[0] |= 1<< (TIM2_IRQn); // enable the TIM2 IRQ
	NVIC_EnableIRQ(TIM2_IRQn);

// ----------------------------------------------------------------------------
// Timer 3 set master ( counting axis speed )
// ----------------------------------------------------------------------------
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // set clock on tim3

	TIM3->PSC = 180; // prescaler
	TIM3->ARR = 200; // compare
	TIM3->CCR1= 100; // duty

	TIM3->CR1 &= (uint16_t)(~TIM_CR1_CKD); // Set clock division to zero
	TIM3->CR2 |= 0x20; /* MMS (6:4) */

	TIM3->CR1 |= TIM_CR1_ARPE; // autoreload on - register ARR is buffered
	TIM3->EGR |= TIM_EGR_UG; // trigger update event to reload timer registers

// Pull signal output----------------------------------------------------------
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER |= GPIO_MODER_MODER6_1; // Channel 1 PA6
	GPIOA->AFR[0] |= 2<<(4*6); // Alternate function channel 2

	TIM3->CCMR1 |= TIM_CCMR1_OC1M; //OC1M[2:0] bits (Output Compare 1 Mode)
	TIM3->CCER |= TIM_CCER_CC1E; //Capture/Compare 1 output enable
	//TIM3->CCER |= TIM_CCER_CC1P; //Capture/Compare 1 output Polarity
// ----------------------------------------------------------------------------
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM_CR1_CEN; // counter enabled
}

// ----------------------------------------------------------------------------
//
//	Y axis timer config
//
// ----------------------------------------------------------------------------
void Init_Yaxis( void )
{
// ----------------------------------------------------------------------------
// Direction pin
// ----------------------------------------------------------------------------
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;

// ----------------------------------------------------------------------------
// Timer 5 set slave ( counting axis distance in pulses )
// ----------------------------------------------------------------------------
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // set clock on tim2

	TIM5->PSC = 0; // prescaler
	TIM5->ARR = 10; // compare
	TIM5->CCR1= 0; // duty

	TIM5->SMCR |= TIM_SMCR_TS_1; // Internal trigger 2 ITR2
	TIM5->SMCR |= TIM_SMCR_SMS; // Slave mode external

	TIM5->CR1 |= TIM_CR1_ARPE; // autoreload on - changes on fly
	TIM5->EGR |= TIM_EGR_UG; // trigger update event to reload timer registers
	TIM5->DIER |= TIM_DIER_UIE; // enable update interrupt

// ----------------------------------------------------------------------------
	//NVIC->ISER[0] |= 1<< (TIM5_IRQn); // enable the TIM5 IRQ
	NVIC_EnableIRQ(TIM5_IRQn);

// ----------------------------------------------------------------------------
// Timer 4 set master ( counting axis speed )
// ----------------------------------------------------------------------------
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // set clock on tim4

	TIM4->PSC = 180; // prescaler
	TIM4->ARR = 200; // compare
	TIM4->CCR1= 100; // duty

	TIM4->CR1 &= (uint16_t)(~TIM_CR1_CKD); // Set clock division to zero
	TIM4->CR2 |= 0x20; /* MMS (6:4) */

	TIM4->CR1 |= TIM_CR1_ARPE; // autoreload on
	TIM4->EGR |= TIM_EGR_UG; // trigger update event to reload timer registers

// Pull signal output----------------------------------------------------------
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	GPIOD->MODER |= GPIO_MODER_MODER12_1; // Channel 1 PD12
	GPIOD->AFR[1] |= 2<<(4*4); // Alternate function channel 2

	TIM4->CCMR1 |= TIM_CCMR1_OC1M; //OC1M[2:0] bits (Output Compare 1 Mode)
	TIM4->CCER |= TIM_CCER_CC1E; //Capture/Compare 1 output enable
	//TIM3->CCER |= TIM_CCER_CC1P; //Capture/Compare 1 output Polarity
// ----------------------------------------------------------------------------
	TIM5->CNT = 0;
	TIM5->CR1 |= TIM_CR1_CEN; // counter enabled
}

// ----------------------------------------------------------------------------
//
//	Accelerate config
//
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Timer 6 set
// ----------------------------------------------------------------------------
void Tim6Init( void )
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // set clock on tim6

	TIM6->PSC = 180; // prescaler
	TIM6->ARR = 100; // compare
	TIM6->CCR1= 50; // duty

	TIM6->CR1 |= TIM_CR1_ARPE; // autoreload on
	TIM6->EGR |= TIM_EGR_UG; // trigger update event to reload timer registers

	TIM6->DIER |= TIM_DIER_UDE;
	TIM6->EGR |= TIM_EGR_UG;	//Re-initializes the timer counter and generates an update of the registers

// ----------------------------------------------------------------------------
	TIM6->CNT = 0;
	TIM6->CR1 |= TIM_CR1_CEN; // counter enabled
}

// ----------------------------------------------------------------------------
//
//	Movement
//
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Feed rate speed movement X
// X - x distance [mm]
// F - speed [mm/min]
// ----------------------------------------------------------------------------
int G1X( int X, int F )
{
	if(X<0){
		X = 0-X;
		X_DIR_0; }
	else
		X_DIR_1;

	TIM2->ARR = X*100; // compare X pulses
	TIM3->ARR = 600000/F; // compare X speed
	TIM3->CCR1= 300000/F; // duty X speed

	TIM2->EGR |= TIM_EGR_UG; // trigger update event to reload timer registers
	TIM2->DIER |= TIM_DIER_UIE; // enable update interrupt

	TIM3->PSC = 180; // prescaler
	TIM2->CNT = 0;
	TIM3->CNT = 0;
	TIM3->CR1 |= TIM_CR1_CEN;// Start X axis

	return 0;
}

// ----------------------------------------------------------------------------
// Feed rate speed movement Y
// Y - y distance [mm]
// F - speed [mm/min]
// ----------------------------------------------------------------------------
int G1Y( int Y, int F )
{
	if(Y<0){
		Y = 0-Y;
		Y_DIR_0; }
	else
		Y_DIR_1;

	TIM5->ARR = Y*100; // compare Y pulses
	TIM4->ARR = 600000/F; // compare Y speed
	TIM4->CCR1= 300000/F; // duty Y speed

	TIM5->EGR |= TIM_EGR_UG; // trigger update event to reload timer registers
	TIM5->DIER |= TIM_DIER_UIE; // enable update interrupt

	TIM4->PSC = 180; // prescaler
	TIM5->CNT = 0;
	TIM4->CNT = 0;
	TIM4->CR1 |= TIM_CR1_CEN;	// Start Y axis

	return 0;
}

// ----------------------------------------------------------------------------
// Feed rate speed movement Z
// Z - z distance [mm]
// F - speed [mm/min]
// ----------------------------------------------------------------------------
int G1Z( int Z, int F )
{
	if(Z<0){
		Z = 0-Z;
		Z_DIR_0; }
	else
		Z_DIR_1;

	TIM12->ARR = Z*100; // compare Z pulses
	TIM14->ARR = 600000/F; // compare Z speed
	TIM14->CCR1= 300000/F; // duty Z speed

	TIM12->DIER = TIM_DIER_UIE;	// enable update interrupt
	TIM12->EGR = TIM_EGR_UG;	// trigger update event to reload timer registers

	TIM14->PSC = 180; // prescaler
	TIM12->CNT = 0;
	TIM14->CNT = 0;
	TIM14->CR1 |= TIM_CR1_CEN;	// Start Z axis

	return 0;
}

// ----------------------------------------------------------------------------
// Feed rate speed movement + accelerate loop
// only one axis in the same time
//
// axis - x/y/z distance [mm]
// distance - distance G91 mode
// F - speed [mm/min]
// ----------------------------------------------------------------------------
int MoveAxis(int axis, int distance, uint16_t feed)
{
	// minimal speed is determinated by number of devision
	int accel_dist = feed/3000;
	if(distance < 0)
		accel_dist = -1*(feed/3000);

	// minimal speed is determinated by number of devision
	 int psc = (feed/30);

	 switch(axis)
	 {
	 case Xaxis:
	 {
		 G1X(accel_dist, feed);						// accelerate
		 while((TIM3->CR1 & TIM_CR1_CEN))
			 TIM3->PSC = (180*psc)/(TIM2->CNT+1);

		 G1X(distance-(2*accel_dist), feed);		// straight move
		 while((TIM3->CR1 & TIM_CR1_CEN));

		 G1X(accel_dist, feed);						// deacceleration
		 while((TIM3->CR1 & TIM_CR1_CEN))
			 TIM3->PSC = (180*psc)/(psc-TIM2->CNT);
		 break;
	 }
	 case Yaxis:
	 {
		 G1Y(accel_dist, feed);						// accelerate
		 while((TIM4->CR1 & TIM_CR1_CEN))
			 TIM4->PSC = (180*psc)/(TIM5->CNT+1);

		 G1Y(distance-(2*accel_dist), feed);		// straight move
		 while((TIM4->CR1 & TIM_CR1_CEN));

		 G1Y(accel_dist, feed);						// deacceleration
		 while((TIM4->CR1 & TIM_CR1_CEN))
			 TIM4->PSC = (180*psc)/(psc-TIM5->CNT);
		 break;
	 }
	 case Zaxis:
	 {
		 G1Z(accel_dist, feed);
		 while((TIM14->CR1 & TIM_CR1_CEN))
		 {
			 TIM14->PSC = (180*psc)/(TIM12->CNT+1);
		 }
		 G1Z(distance-(2*accel_dist), feed);
		 while((TIM14->CR1 & TIM_CR1_CEN));
		 G1Z(accel_dist, feed);
		 while((TIM14->CR1 & TIM_CR1_CEN))
		 {
			 TIM14->PSC = (180*psc)/(psc-TIM12->CNT);
		 }
		 break;
	 }
	 }
	 return 0;
}

// ----------------------------------------------------------------------------
// Check axis busy flag
// Return - busy or not
// ----------------------------------------------------------------------------
// X axis flag-----------------------------------------------------------------
int X_BusyFlag( void )
{
	if(TIM4->CR1 & TIM_CR1_CEN)
		return 1;
	else
		return 0;
}
// Y axis flag-----------------------------------------------------------------
int Y_BusyFlag( void )
{
	if(TIM3->CR1 & TIM_CR1_CEN)
		return 1;
	else
		return 0;
}
