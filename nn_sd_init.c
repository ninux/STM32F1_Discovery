/* ----------------------------------------------------------------------------
 * nn_sd_init.c
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
#include "stdio.h"
#include "nn_write_string.h"
#include "nn_pauses.h"
#include "nn_write_string.h"
#include "nn_display_commands.h"
#include "nn_sd_init.h"

void init_SD_CARD(void)
{
		USART_SendData(USART1, 0x40);
		pause_usart_slow();
		USART_SendData(USART1, 0x69);
		pause_usart_slow();
		pause_usart_slow();


}

void set_SD_adress(char adress1, char adress2, char adress3, char adress4)
{
		USART_SendData(USART1, 0x40);
		pause_usart_slow();
		USART_SendData(USART1, 0x41);
		pause_usart_slow();
		USART_SendData(USART1, adress1);
		pause_usart_slow();
		USART_SendData(USART1, adress2);
		pause_usart_slow();
		USART_SendData(USART1, adress3);
		pause_usart_slow();
		USART_SendData(USART1, adress4);
		pause_usart_slow();
}

void write_SD(char tmp)
{
		USART_SendData(USART1, 0x40);
		pause_usart_slow();
		USART_SendData(USART1, 0x77);
		pause_usart_slow();
		USART_SendData(USART1, tmp);
		pause_usart_slow();
}

char read_SD(char adr1, char adr2, char adr3, char adr4)
{
		set_SD_adress(adr1, adr2, adr3, adr4);
		USART_SendData(USART1, 0x40);
		pause_usart_slow();
		USART_SendData(USART1, 0x72);
		pause_usart_slow();
		return read_usart1();
}
