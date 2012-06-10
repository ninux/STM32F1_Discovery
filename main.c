/* ----------------------------------------------------------------------------
 * main.c
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
#include "misc.h"
//#include "nn_write_string.h"
//#include "nn_pauses.h"
//#include "nn_usart1_init.c"
//#include "nn_display_commands.c"
//#include "nn_sd_init.c"

int main(void)
{
		char tmp = 0;

		usart1_init();
		init_display();
		clear_display();
		/* Here is the main */

		set_baudrate_usart1(9600);
		clear_display();
		write_string("> END OF PROGRAM!", 0x00, 0x11, 0x03, 0xFF, 0xFF);
		write_string("> Baud reset to 9600", 0x00, 0x13, 0x03, 0xFF, 0xFF);

}
