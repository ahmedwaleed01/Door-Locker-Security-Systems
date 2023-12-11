/*
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: ahmed waleed
 */
#include "uart.h"
#include <avr/io.h>
#include "common_macros.h"



void UART_init(Config_Uart*config_ptr){
	/* Set Double Transmission Speed */
	UCSRA=(1<<U2X);
	/*Set Enable Transmitter
	 *Set Enable Receiver
	 *Set UCSZ2 Character Size
	 * */

	UCSRB=(1<<RXEN) | (1<<TXEN)|(config_ptr->dataSize&0x04);
    /*
     * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * set parity bit
	 * set stop bit
	 * set data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
     * */
	UCSRC= (1<<URSEL) | (config_ptr->parity<<4)| (config_ptr->StopSelect<<3)
			| ((config_ptr->dataSize&0x03)<<1);

	uint16 ubrr_value = 0;
	/*calculate the value of ubrr from mu baudrate and fcpu */
	ubrr_value = (uint16)(((F_CPU / (config_ptr->baud_rate* 8UL))) - 1);

	UBRRL=ubrr_value;
	UBRRH=ubrr_value>>8;

}

void UART_sendByte(uint8 data){

	/*polling until TX buffer is empty to start sending byte
	 * */
	while(BIT_IS_CLEAR(UCSRA,UDRE));
    /*putting my data on UDR reg
     * */
	UDR=data;
}

uint8 UART_recieveByte(){
	/*polling until RXC buffer is empty to start sending byte
		 * */
	while(BIT_IS_CLEAR(UCSRA,RXC));
	/*putting my data on UDR reg
	     * */
	return UDR;
}

void UART_sendString(char*str){

	uint8 i=0;

	while(str[i]!='\0'){
		UART_sendByte(str[i]);
		i++;
	}


}

void UART_recieveString(char*str){
	uint8 i=0;

	do{
		str[i]=UART_recieveByte();
	}while(str[i++]!='#');

	str[i-1]='\0';
}
