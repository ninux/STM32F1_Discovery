/*-----------------------------------------------------------------------------
 * File:		nn_pauses.c
 * Project:		STM32F1_Discovery
 * Version:		Version 1.0
 * Date:		2012-06-15 (yyyy-mm-dd)
 * Author:		Nino Ninux
 * Mail:		nino.ninux@gmail.com
 * Description:
 *---------------------------------------------------------------------------*/

#ifndef 	NN_PAUSES_H
#define 	NN_PAUSES_H

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

#ifndef		NN_DISPALY_H
#define		NN_DISPLAY_H
#include	"nn_display.h"
#endif

#ifndef		NN_USART_H
#define		NN_USART_H
#include	"nn_usart.h"
#endif

#ifndef		NN_NVIC_H
#define		NN_NVIC_H
#include	"nn_nvic.h"
#endif

#define TEXT            0x5FFFFF
#define USART           0xFFFF
#define USART_SLOW      0x5FFFFF
#define USART_FAST      0xFFFF

static int x = 0;

static void universal_pause(int PAUSETYPE)
{
	for(x=0; x<=PAUSETYPE; ++x){
	}
}

void pause_text(void)
{
        universal_pause(TEXT);
}

void pause_usart(void)
{
        universal_pause(USART);
}

void pause_usart_fast(void)
{
        universal_pause(USART_FAST);
}

void pause_usart_slow(void)
{
        universal_pausee(USART_SLOW);
}

#endif /* NN_PAUSES_H */



