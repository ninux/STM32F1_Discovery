/* ----------------------------------------------------------------------------
 * nn_display_commands.c
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
#include "stdio.h"
#include "nn_write_string.h"
#include "nn_pauses.h"
#include "nn_write_string.h"
#include "nn_display_commands.h"

void init_display(void)
{
		pause_usart_slow();
		USART_SendData(USART1, 0x55);
		pause_usart_slow();
		USART_SendData(USART1, 0x45);
		pause_usart_slow();
		USART_SendData(USART1, 0x56);
		pause_usart_slow();
		USART_SendData(USART1, 0x55);
		pause_usart_slow();
		USART_SendData(USART1, 0x46);
		pause_usart_slow();
		USART_SendData(USART1, 0x03);
		pause_usart_slow();
}

void clear_display(void)
{
		pause_usart_slow();
		USART_SendData(USART1, 0x45);
		pause_usart_slow();
}

void version_display(void)
{
		pause_usart_slow();
		USART_SendData(USART1, 0x56);
		pause_usart_slow();

}
