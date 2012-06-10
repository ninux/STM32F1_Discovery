/* ----------------------------------------------------------------------------
 * nn_usart1_init.c
 * Author: 		Nino Ninux
 * Mail:		nino.ninux@gmail.com
 * Target: 		STM32F100RB Discovery
 * Version: 	V0.2
 * Description:
---------------------------------------------------------------------------- */

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#include "stdio.h"
#include "nn_write_string.h"
#include "nn_pauses.h"
#include "nn_write_string.h"
#include "nn_display_commands.h"

unsigned int data = 0;

// initialization for the usart1
void usart1_init()
{
		int x = 0;

		//RCC_DeInit (); /* RCC system reset(for debug purpose)*/
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
			- BaudRate = 115200 baud
		    - Word Length = 8 Bits
		    - One Stop Bit
		    - No parity
		    - Hardware flow control disabled (RTS and CTS signals)
		    - Receive and transmit enabled
		    - USART Clock disabled
		    - USART CPOL: Clock is active low
		    - USART CPHA: Data is captured on the middle
		    - USART LastBit: The clock pulse of the last data bit is not output to
		      	  	  	  	 the SCLK pin
		*/
		USART_InitStructure.USART_BaudRate            = 9600;
		USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits            = USART_StopBits_1;
		USART_InitStructure.USART_Parity              = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);

		USART_ReceiverWakeUpCmd  (USART1, ENABLE);

}

void set_baudrate_usart1(int new_baudrate)
{
		char c_baudrate = 0;

		switch(new_baudrate)
		{
		case 9600:
			c_baudrate = 0x06;
			break;
		case 115200:
			c_baudrate = 0x0D;
			break;
		}

		USART_SendData(USART1, 0x55);
		pause_usart_slow();
		USART_SendData(USART1, 0x51);
		pause_usart_slow();
		USART_SendData(USART1, c_baudrate);
		pause_usart_slow();
		pause_usart_slow();

		//RCC_DeInit (); /* RCC system reset(for debug purpose)*/
		RCC_HSEConfig (RCC_HSE_ON);       /* Enable HSE */

		/* Wait till HSE is ready */
		while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

		RCC_HCLKConfig   (RCC_SYSCLK_Div1);   /* HCLK   = SYSCLK */
		RCC_PCLK2Config  (RCC_HCLK_Div1);     /* PCLK2  = HCLK  */
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
			- BaudRate = 115200 baud
			- Word Length = 8 Bits
			- One Stop Bit
			- No parity
			- Hardware flow control disabled (RTS and CTS signals)
			- Receive and transmit enabled
			- USART Clock disabled
			- USART CPOL: Clock is active low
			- USART CPHA: Data is captured on the middle
			- USART LastBit: The clock pulse of the last data bit is not output to
							 the SCLK pin
		*/
		USART_InitStructure.USART_BaudRate            = new_baudrate;
		USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits            = USART_StopBits_1;
		USART_InitStructure.USART_Parity              = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);

		USART_ReceiverWakeUpCmd  (USART1, ENABLE);

		pause_usart_slow();
}

void read_acknowledge(void)
{
		while((USART_GetITStatus (USART1, USART_IT_RXNE)) == SET){
		}

		data = (USART_ReceiveData(USART1));
				if(data == 0x15){
						write_string("> ACK: FAIL", 0x00, 0x13, 0x03, 0xFF, 0xFF);
				}else if(data == 0x06){
						write_string("> ACK: OK ", 0x00, 0x13, 0x03, 0xFF, 0xFF);
				}else if(data != 0x00){
						write_string("> UART ERROR", 0x00, 0x13, 0x03, 0xFF, 0xFF);
				}else if(data == 0x00){
						write_string("> NO INPUT!", 0x00, 0x13, 0x03, 0xFF, 0xFF);
				}
}

char read_usart1(void)
{
		while((USART_GetITStatus (USART1, USART_IT_RXNE)) == SET){

		}

		return (USART_ReceiveData(USART1));
}
