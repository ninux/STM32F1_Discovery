STM32F1_Discovery
=================

This is a "get in touch with" project for the stm32f100 MCU nested in the 
discovery board. For further information on the board go to: 

	http://www.st.com/internet/evalboard/product/250863.jsp

Goals

    The primary goal is to get in touch with the stm32f100 and CooCox CoIDE. 
    There are also specific software interest like
        
        - General Purpose of the uController (Timers, Interrupts... )
        - UART (or USART) communications
        - In-Application-Programming (IAP) with I/O Peripherals like USART...
		
	After evaluation of the internals, there will be also an evaluation on the 
	hardware. If everythings going on well, there will be an selfmadeboard 
	based on the stm23f1xx. There is also an interest to run a selfmade basic
	vm on the MCU.

Current stats on SW Development

    OK  Initializing the general functions of the MCU (clock settings)
    OK  Sending data from the MCU to USART
	OK	Receiving data from USART to MCU per Interrupt
	CD	Initialise and run ISR (Interrupt Sevice Routines) [30% developed yet]
    ND  Timers (Init, Interrupt etc.)

    Indexes
        OK = get it work
        CD = currently on development
        ND = not developed yet but in agenda
        
Configuration for current development/debugging/testing

    OS:                 Windows, XP, SP3
    IDE:                CooCox CoIDE (Version: 1.4.1, Build id: 20120401-1336)
    Toolchain:          arm-none-eabi-gcc
    USB/Serial:         CP2102
    Board-External I/O: 4D Systems 3.2" uLCD SGC
    Digital-Analyzer:   DigiView TechTools Logic Analyzer DV1-100 (18 Channel)
	Coming soon:		RIGOL DS1052E Digital Storage Oscilloscope

    The main setting to develop and test the source is like this:

	 _______		 _____________________		   _________
    /		\       /		  | 		  \       /		    \
    | PC    |  USB  |         |STM32      |  PWR  | 4D      |
    |       |--->---| ST-Link |Discovery  |--->---| Systems |
    |       |  CP   |         |           | Rx/Tx | 3.2"    |
    |       |-<-x   |         |           |-->x<--| uLCD    |
    \_______/   |   \_________|___________/   |   \_________/
				|							  |	
				|__________(optional!)________|
				
	The connection from the Rx/Tx lines between 4D Sytems uLCD and the STM32
	board is not "that" good for debugging the Rx/Tx signals with the CP2102
	because of the signal voltage level differences between them. If the 
	CP2102 is connected to these lines it will disable the Tx of the 4D Systems 
	Display. So in short:
	
		IF THE CP2102 IS CONNECTED TO THE RX/TX BETWEEN 4D AND STM32,
		THEN THE TX OF 4D IS DISABLED (neither able to enable nor detect)
 
Developers

    Primary developer is Nino Ninux.
    For further information or questions contact him on this e-mail:
	
		nino.ninux@gmail.com
