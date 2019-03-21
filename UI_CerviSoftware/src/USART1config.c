/**
  ******************************************************************************
  * @file    USART1config.c
  * @author  DannLab
  * @brief   This file contains USART1 configuration
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "USART1config.h"

// ----------------------------------------------------------------------------
//	POST Init - USART1
// ----------------------------------------------------------------------------
void POST_USART1_Init( void )
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // set clock on USART1
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // set clock on PORTA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // set clock on PORTB

	GPIOA->MODER |= GPIO_MODER_MODER9_1; // PA9 alternative UART TXD
	GPIOB->MODER |= GPIO_MODER_MODER7_1; // PB7 alternative UART RXD

	GPIOA->AFR[1] |= (7<<(4*1)); //alternate function 7 for USART1 PIN 9 - TX
	GPIOB->AFR[0] |= (7<<(4*7)); //alternate function 7 for USART1 PIN 7 - RX

	__HAL_RCC_USART1_CLK_ENABLE();

	UART_HandleTypeDef uart;

	uart.Instance = USART1;
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&uart);

	//USART1->CR1 |= USART_CR1_RXNEIE; // RXIE interrupt enable

	//NVIC_EnableIRQ(USART1_IRQn); // enable interrupt in NVIC
}

void SendChar(const char str)
{
	while ((USART1->ISR & USART_ISR_TXE)==0); // wait for ready
	USART1->TDR = str;
}

void SendString(const char* str)
{
	while(*str)
	{
		while ((USART1->ISR & USART_ISR_TXE)==0); // wait for ready
		USART1->TDR = *str++;
	}
}

uint8_t ReciveChar(void)
{
	UART_HandleTypeDef uart;
	uint8_t data;

	uart.Instance = USART1;
	uart.Init.WordLength = UART_WORDLENGTH_8B;

	if (__HAL_UART_GET_FLAG(&uart, UART_FLAG_RXNE) == SET)
	{
		data = USART1->RDR;
	}
	return data;
}

void rec(void)
{
	UART_HandleTypeDef uart;
	uint8_t data[10] = {0};

	while(1)
	{
		if (__HAL_UART_GET_FLAG(&uart, UART_FLAG_RXNE) == SET)
		{
			HAL_UART_Receive(&uart, data, 1, 100);
			HAL_UART_Transmit(&uart, data, 1, 100);
		}
	}
}
