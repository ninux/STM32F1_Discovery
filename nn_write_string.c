/* ----------------------------------------------------------------------------
 * nn_write_string.c
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


void write_string(char * dat, char column, char line, char font, char color_1, char color_2)
{
		char * pStr;
		pStr = dat;


		// send the "draw char" command (0x73) to the display controller
		USART_SendData(USART1, 0x73);
		pause_usart_fast();
		USART_SendData(USART1, column);
		pause_usart_fast();
		USART_SendData(USART1, line);
		pause_usart_fast();
		USART_SendData(USART1, font);
		pause_usart_fast();
		USART_SendData(USART1, color_1);
		pause_usart_fast();
		USART_SendData(USART1, color_2);
		pause_usart_fast();

		// send every letter in single transmitting mode
		for(;*pStr!=0;pStr++)
		{
			USART_SendData(USART1, *pStr);
			pause_usart_fast();
		}

		pause_usart();
		// send "END" for string Data
		USART_SendData(USART1, 0x00);

		pause_usart();
}
