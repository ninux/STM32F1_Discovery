/*-----------------------------------------------------------------------------
 * File:		nn_usart.c
 * Project:		STM32F1_Discovery
 * Version:		Version 1.0
 * Date:		2012-06-15 (yyyy-mm-dd)
 * Author:		Nino Ninux
 * Mail:		nino.ninux@gmail.com
 * Description:
 *---------------------------------------------------------------------------*/

#ifndef 	NN_USART_H
#define 	NN_USART_H

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

#ifndef		NN_PAUSES_H
#define		NN_PAUSES_H
#include	"nn_pauses.h"
#endif

#ifndef		NN_NVIC_H
#define		NN_NVIC_H
#include	"nn_nvic.h"
#endif

static int baudrate;
volatile char received_data;

void nn_usart_init(baudrate)
{
	/* RCC_DeInit (); */
	/* RCC system reset(for debug purpose)*/
	RCC_HSEConfig (RCC_HSE_ON);       /* Enable HSE */

	/* Wait till HSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

	RCC_HCLKConfig   (RCC_SYSCLK_Div1);   /* HCLK   = SYSCLK */
	RCC_PCLK2Config  (RCC_HCLK_Div1);     /* PCLK2  = HCLK */
	RCC_PCLK1Config  (RCC_HCLK_Div2);     /* PCLK1  = HCLK/2 */
	RCC_ADCCLKConfig (RCC_PCLK2_Div4);    /* ADCCLK = PCLK2/4 */

	/* PLLCLK = 8MHz * 9 = 72 MHz */
	RCC_PLLConfig (0x00010000, RCC_PLLMul_9);

	RCC_PLLCmd (ENABLE);                  /* Enable PLL */

	/* Wait till PLL is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

	/* Select PLL as system clock source */
	RCC_SYSCLKConfig (RCC_SYSCLKSource_PLLCLK);

	/* Wait till PLL is used as system clock source */
	while (RCC_GetSYSCLKSource() != 0x08);

	/* Enable USART1 and GPIOA clock */
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 configured as follow:
	- Hardware flow control disabled (RTS and CTS signals)
	- Receive and transmit enabled
	- USART Clock disabled
	- USART CPOL: Clock is active low
	- USART CPHA: Data is captured on the middle
	- USART LastBit: The clock pulse of the last data bit is not output to
	the SCLK pin
	*/
	USART_InitStructure.USART_BaudRate            = baudrate;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

	USART_ReceiverWakeUpCmd  (USART1, ENABLE);
}

void nn_usart_set_baudrate(int baudrate)
{
	#ifdef NN_DISPLAY_H
	nn_display_set_baudrate(baudrate);
	#endif
	/* Dont forget to steup the display baudrate! */


	/* RCC_DeInit (); */
	/* RCC system reset(for debug purpose)*/
	RCC_HSEConfig (RCC_HSE_ON);       /* Enable HSE */

	/* Wait till HSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

	RCC_HCLKConfig   (RCC_SYSCLK_Div1);   /* HCLK   = SYSCLK */
	RCC_PCLK2Config  (RCC_HCLK_Div1);     /* PCLK2  = HCLK */
	RCC_PCLK1Config  (RCC_HCLK_Div2);     /* PCLK1  = HCLK/2 */
	RCC_ADCCLKConfig (RCC_PCLK2_Div4);    /* ADCCLK = PCLK2/4 */

	/* PLLCLK = 8MHz * 9 = 72 MHz */
	RCC_PLLConfig (0x00010000, RCC_PLLMul_9);

	RCC_PLLCmd (ENABLE);                  /* Enable PLL */

	/* Wait till PLL is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

	/* Select PLL as system clock source */
	RCC_SYSCLKConfig (RCC_SYSCLKSource_PLLCLK);

	/* Wait till PLL is used as system clock source */
	while (RCC_GetSYSCLKSource() != 0x08);

	/* Enable USART1 and GPIOA clock */
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 configured as follow:
	- Hardware flow control disabled (RTS and CTS signals)
	- Receive and transmit enabled
	- USART Clock disabled
	- USART CPOL: Clock is active low
	- USART CPHA: Data is captured on the middle
	- USART LastBit: The clock pulse of the last data bit is not output to
	the SCLK pin
	*/
	USART_InitStructure.USART_BaudRate            = baudrate;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

	USART_ReceiverWakeUpCmd  (USART1, ENABLE);
}

char nn_usart_read(int usart_channel)
{
	if(usart_channel==1){
		while((USART_GetITStatus (USART1, USART_IT_RXNE)) == SET){
		}
		return (USART_ReceiveData(USART1));
	}
}

void USART1_IRQHandler(void)
{
     if((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
     {
    	 received_data = USART_ReceiveData ( USART1 );
     }

     USART_ReceiveData ( USART1 );
     USART_ClearFlag(USART1, USART_FLAG_CTS);
     USART_ClearFlag(USART1, USART_FLAG_LBD);
     USART_ClearFlag(USART1, USART_FLAG_TC);
}


#endif /* NN_USART_H */
