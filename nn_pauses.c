/* ----------------------------------------------------------------------------
 * nn_pause.c
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

// timesetting to read a displayed text
void pause_text(void)
{
		int x = 0;
		for(x=0; x<=0x5FFFFF; x++){
		}
}

// waiting time between two USART commands
void pause_usart(void)
{
		int x = 0;
		for(x=0; x<=0xFFFF; x++){
		}
}

// waiting time between two bytes in a data-string
void pause_usart_fast(void)
{
		int x = 0;
		for(x=0; x<=0xFFFF; x++){
		}
}

void pause_usart_slow(void)
{
		int x = 0;
		for(x=0; x<=0x5FFFF; x++){
		}
}


