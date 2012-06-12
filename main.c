

/* ----------------------------------------------------------------------------
* main.c
* Author: Nino Ninux
* Mail: nino.ninux@gmail.com
* Target: STM32F100RB Discovery
* Version: V0.2
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

int j = 0;
int i = 0;
char data[1];
void USART1_IRQHandler(void);
void NVIC_Configuration(void);

int main(void)
{
		char tmp = 0;

		usart1_init();
		init_display();
		clear_display();

		/* Here is the main */

		/* NVIC Configuration */
		NVIC_Configuration();

		USART_ClearFlag(USART1, USART_FLAG_CTS);
		USART_ClearFlag(USART1, USART_FLAG_LBD);
		USART_ClearFlag(USART1, USART_FLAG_TC);

		NVIC_InitTypeDef NVIC_InitStructure;

		NVIC_Configuration();

		data[0] = USART_ReceiveData ( USART1 );
		//data[0] = USART_ReceiveData ( USART1 );

		/* Enable the USART1 Receive interrupt: this interrupt is generated when the
				   USART1 receive data register is not empty */
				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
				USART_ClearFlag(USART1, USART_FLAG_CTS);
				USART_ClearFlag(USART1, USART_FLAG_LBD);
				USART_ClearFlag(USART1, USART_FLAG_TC);
/*
				init_SD_CARD();

		set_baudrate_usart1(9600);
		clear_display();
		write_string("> END OF PROGRAM!", 0x00, 0x11, 0x03, 0xFF, 0xFF);
		write_string("> Baud reset to 9600", 0x00, 0x13, 0x03, 0xFF, 0xFF);

		*/

		while(1){
			write_string(0x06, 0x00, j, 0x02, 0xFF, 0xFF);
			init_SD_CARD();
			init_SD_CARD();
			init_SD_CARD();
		}
}


void USART1_IRQHandler(void)
{
    	if((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
    	{
    			data[0] = USART_ReceiveData ( USART1 );
    			j++;
    			if(j>=24){
    					clear_display();
    					j=0;
    			}
    			if(data[0]==0x06){
    					write_string("ACK OK", 0x00, j, 0x02, 0xFF, 0xFF);
    			}else if(data[0]=0x15){
    					write_string("ACK FAIL!", 0x00, j, 0x02, 0xFF, 0xFF);
    			}else{
    					write_message("Unknown CMD/DATA", 0x00, j, 0x02, 0xFF, 0xFF);
    			}
    	//write_string("Received data:", 0x00, 0x00, 0x02, 0xFF, 0xFF);

    	}
    			USART_ReceiveData ( USART1 );
    			USART_ClearFlag(USART1, USART_FLAG_CTS);
    	    	USART_ClearFlag(USART1, USART_FLAG_LBD);
    	    	USART_ClearFlag(USART1, USART_FLAG_TC);
}

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
