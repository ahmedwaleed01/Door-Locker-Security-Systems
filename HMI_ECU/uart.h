/*
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: ahmed waleed
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

#define  F_CPU                16000000

typedef enum{
	DISABLED,RESERVED,EVEN_PARITY,ODD_PARITY
}Parity_mode;

typedef enum{
	ONE_BIT,TWO_BIT
}Stop_Select;

typedef enum{
	BIT_5,BIT_6,BIT_7,BIT_8,
	BIT_9=7
}Character_Size;

typedef struct{
	Parity_mode parity;
	Stop_Select  StopSelect;
	Character_Size dataSize;
	uint32 baud_rate;
}Config_Uart;


void UART_init(Config_Uart*config_ptr);

void UART_sendByte(uint8 data);

uint8 UART_recieveByte();

void UART_sendString(char*str);

void UART_recieveString(char*str);

#endif /* UART_H_ */
