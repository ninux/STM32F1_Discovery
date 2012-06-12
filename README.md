STM32F1_Discovery
=================

This is a "get in touch with" project for the stm32f100 MCU nested in the discovery board.

Goals

    The main goal is to get in touch with the stm32f100 and CooCox CoIDE. 
    There are also specific software interest like
        
        - General Purpose of the uController (Timers, Interrupts... )
        - UART (or USART) communications
        - In-Application-Programming (IAP) with I/O Peripherals like USART...

Current stats on SW Development

    OK  Initializing the general functions of the MCU (clock settings)
    OK  Sending data from the MCU to USART
    CD  Recieving data to the MCU (~60% done)
    ND  Interrupt Init and handling
    ND  Timersettings
    
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
    
    The main setting to develop and test the source is like this:
    
    ---------       ----------------------       -----------
    | PC    |  USB  |       |STM32       |  PWR  | 4D      |
    |       |--->---|ST-Link|Discovery   |--->---| Systems |
    |       |  CP   |       |            | Rx/Tx | 3.2"    |
    |       |---<---|                    |--->---| uLCD    |
    ---------       ----------------------       -----------
    
Developers

    Current developer is Nino Ninux.
    For any informations/questions contact nino.ninux@gmail.com


