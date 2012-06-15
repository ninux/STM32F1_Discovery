/*-----------------------------------------------------------------------------
 * File:		nn_nvic.c
 * Project:		STM32F1_Discovery
 * Version:		Version 1.0
 * Date:		2012-06-15 (yyyy-mm-dd)
 * Author:		Nino Ninux
 * Mail:		nino.ninux@gmail.com
 * Description:
 *---------------------------------------------------------------------------*/

#ifndef		NN_NVIC_H
#define		NN_NVIC_H
#include	"nn_nvic.h"
#endif

#ifndef		STM32F10X_H
#define		STM32F10X_H
#include 	"stm32f10x.h"
#endif

#ifndef		STM32F10X_GPIO_H
#define		STM32F10X_GPIO_H
#include 	"stm32f10x_gpio.h"
#endif

#ifndef		STM32F10X_RCC_H
#define		STM32F10X_RCC_H
#include 	"stm32f10x_rcc.h"
#endif

#ifndef		STM32F10X_USART_H
#define		STM32F10X_USART_H
#include 	"stm32f10x_usart.h"
#endif

#ifndef		STDIO_H
#define		STDIO_H
#include 	"stdio.h"
#endif

#ifndef		MISC_H
#define		MISC_H
#include 	"misc.h"
#endif

#ifndef		NN_PAUSES_H
#define		NN_PAUSES_H
#include	"nn_pauses.h"
#endif

#ifndef		NN_DISPALY_H
#define		NN_DISPLAY_H
#include	"nn_display.h"
#endif

#ifndef		NN_USART_H
#define		NN_USART_H
#include	"nn_usart.h"
#endif

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
