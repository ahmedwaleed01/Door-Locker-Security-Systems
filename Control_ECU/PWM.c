/*
 * PWM.c
 *
 *  Created on: 9 Oct 2023
 *      Author: ahmed waleed
 */

#include "PWM.h"
#include "avr/io.h"
#include "GPIO.h"

void PWM_Timer0_Start(uint8 duty_cycle){

	TCNT0=0;
	OCR0=(((float)duty_cycle)/100)*255;
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	TCCR0=(1<<WGM00)|(1<<COM01)|(1<<CS01);

}

