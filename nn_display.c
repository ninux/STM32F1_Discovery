/*-----------------------------------------------------------------------------
 * File:		nn_display.c
 * Project:		STM32F1_Discovery
 * Version:		Version 1.0
 * Date:		2012-06-15 (yyyy-mm-dd)
 * Author:		Nino Ninux
 * Mail:		nino.ninux@gmail.com
 * Description:
 *---------------------------------------------------------------------------*/

#ifndef		NN_DISPLAY_H
#define		NN_DISPLAY_H
#include	"nn_display.h"
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

#ifndef		NN_USART_H
#define		NN_USART_H
#include	"nn_usart.h"
#endif

#ifndef		NN_NVIC_H
#define		NN_NVIC_H
#include	"nn_nvic.h"
#endif

/*---------------------------------------------------------------------------*/
/* Display Commands hex values                                               */
/*---------------------------------------------------------------------------*/

/* General Commands */
#define		AUTOBAUD		0x55
#define		CLEAR_SCREEN	0x45
#define		VERSION_INFO	0x56
#define		SET_BAUDRATE	0x51

/* Writing Commands */
#define		DRAW_CHAR		0x73
#define		STRING_END		0x00

/* Baud rates */
#define		BAUD_110		0x00
#define		BAUD_300		0x01
#define		BAUD_600		0x02
#define		BAUD_1200		0x03
#define		BAUD_2400		0x04
#define		BAUD_4800		0x05
#define		BAUD_9600		0x06
#define		BAUD_14400		0x07
#define		BAUD_19200		0x08
#define		BAUD_31250		0x09
#define		BAUD_38400		0x0a
#define		BAUD_56000		0x0b
#define		BAUD_57600		0x0c
#define		BAUD_115200		0x0d
#define		BAUD_129032		0x0e
#define		BAUD_282353		0x0f
#define		BAUD_128000		0x10
#define		BAUD_256000		0x11

/*---------------------------------------------------------------------------*/

static char acknowledge = 0;
static char cursor_x = 0;
static char cursor_y = 0;

static void nn_display_send_cmd(char DISPLAY_CMD)
{
	pause_usart();
	USART_SendData(USART1, DISPLAY_CMD);
}

static char nn_display_get_baud(char input)
{
	switch(input){
	case 110:
		return BAUD_110;
		break;
	case 300:
		return BAUD_300;
		break;
	case 600:
		return BAUD_600;
		break;
	case 1200:
		return BAUD_1200;
	case 2400:
		return BAUD_2400;
		break;
	case 4800:
		return BAUD_4800;
		break;
	case 9600:
		return BAUD_9600;
		break;
	case 14400:
		return BAUD_19200;
		break;
	case 19200:
		return BAUD_19200;
		break;
	case 31250:
		return BAUD_31250;
		break;
	case 38400:
		return BAUD_38400;
		break;
	case 56000:
		return BAUD_56000;
		break;
	case 57600:
		return BAUD_57600;
		break;
	case 115200:
		return BAUD_115200;
		break;
	case 129032:
		return BAUD_129032;
		break;
	case 282353:
		return BAUD_282353;
		break;
	case 128000:
		return BAUD_128000;
		break;
	case 256000:
		return BAUD_256000;
		break;
	default:
		return BAUD_9600;
		break;
	}
}

void nn_display_init(void)
{
	nn_display_send_cmd(AUTOBAUD);
	nn_display_send_cmd(CLEAR_SCREEN);
	nn_display_send_cmd(VERSION_INFO);
	nn_pause_text();
	nn_display_send_cmd(CLEAR_SCREEN);
}

void nn_dispaly_set_baudrate(char baudrate)
{

	nn_display_send_cmd(AUTOBAUD);
	nn_display_send_cmd(SET_BAUDRATE);
	nn_display_send_cmd(nn_display_get_baud(baudrate));
}

char nn_display_acknowledge(void)
{
	while((USART_GetITStatus (USART1, USART_IT_RXNE)) == SET){

	}
	return (USART_ReceiveData(USART1));
}

void nn_display_write(char * dat, char mode, char column, char line, char font,
						char color1, char color2)
{
	char * pStr;
	pStr = dat;

	if(mode == 1)
	{

	}else{
	nn_display_send_cmd(DRAW_CHAR);
	nn_display_send_cmd(column);
	nn_display_send_cmd(line);
	nn_display_send_cmd(font);
	nn_display_send_cmd(color1);
	nn_display_send_cmd(color2);

	for(;*pStr!=0; ){
		USART_SendData(USART1, *pStr);
		nn_pause_usart();
	}
	USART_SendData(USART1, STRING_END);

	}
}































