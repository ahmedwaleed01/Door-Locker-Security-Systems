/*
 * LCD.c
 *
 *  Created on: 30 Sept 2023
 *      Author: ahmed waleed
 */

#include "LCD.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include <util/delay.h>

void LCD_SendCommand(uint8 command){
	/*    Make RS equal ZERO      */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	_delay_ms(1);                                           /*  delay for T(as)= 50nsec  */
	/*  make enable equal one    */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);                                           /*  delay for T(pw)-T(dsw)   */

#if (LCD_DATA_BITS_MODE==8)
	/*  send character to LCD DATA PORT   */
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	_delay_ms(1);                                           /*  delay for T(dsw)= 50nsec */
	/*     disable enable        */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1);
	/*     disable enable        */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	/*  make enable equal one    */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1);
	/*     disable enable        */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif
}

void LCD_displayCharacter(uint8 character){
	/*    Make RS equal 1       */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);                                           /*  delay for T(as)= 50nsec  */
	/*  make enable equal one    */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);                                           /*  delay for T(pw)-T(dsw)   */

#if (LCD_DATA_BITS_MODE==8)
	/*  send character to LCD DATA PORT   */
	GPIO_writePort(LCD_DATA_PORT_ID, character);
	_delay_ms(1);                                           /*  delay for T(dsw)= 50nsec */
	/*     disable enable        */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,7));

	_delay_ms(1);
	/*     disable enable        */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	/*  make enable equal one    */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,3));

	_delay_ms(1);
	/*     disable enable        */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif


}

void LCD_displayString(const char*Str){
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_init(){
	/* make Rs pin and Enable pin output pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	_delay_ms(20);
#if (LCD_DATA_BITS_MODE==8)

	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	/*2 lines + 8 bits mode */
	LCD_SendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#elif(LCD_DATA_BITS_MODE==4)

	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif

	/* cursor off */
	LCD_SendCommand(LCD_CURSOR_OFF);
	/* clear screen */
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

void LCD_moveCursor(uint8 row,uint8 col){
	uint8 cursor_location;
	switch(row){
	case 0:
		cursor_location=col;
		break;
	case 1:
		cursor_location=0x40+col;
		break;
	case 2:
		cursor_location=0x10+col;
		break;
	case 3:
		cursor_location=0x50+col;
		break;
	}
	LCD_SendCommand(cursor_location | LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str){
	LCD_moveCursor(row,col);
	LCD_displayString(Str);
}

void LCD_intgerToString(int data){
	char buffer[16];
	itoa(data,buffer,10);
	LCD_displayString(buffer);
}
void LCD_clearScreen(void){
	LCD_SendCommand(LCD_CLEAR_COMMAND );
}
