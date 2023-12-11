/*
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer AVR driver
 *
 * Author: ahmed waleed
 *
 */


#include "buzzer.h"
#include "gpio.h"

void Buzzer_init(){
	GPIO_setupPinDirection(PORTC_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_LOW);
}

void Buzzer_on(void){
	GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_HIGH);
}

void Buzzer_off(void){
	GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_LOW);
}
