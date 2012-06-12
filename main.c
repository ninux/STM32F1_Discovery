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

	while(1){

	}
}

void USART1_IRQHandler(void)
{
    	if((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
    	{
    		data[0] = USART_ReceiveData ( USART1 );
    		
		/* put in here your ISR */

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
