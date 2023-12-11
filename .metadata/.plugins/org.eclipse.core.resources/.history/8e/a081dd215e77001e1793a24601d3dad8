/*
 * Module: Timer
 *
 * File Name: Timer.c
 *
 * Description: Source file for the TIMER1 AVR driver
 *
 * Author: ahmed waleed
 */

#include "Timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr)(void) = NULL_PTR;

#ifdef  Compare_unit_A
ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function */
		(*g_callBackPtr)();
	}
}
#endif

#ifdef Compare_unit_B
ISR(TIMER1_COMPB_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function */
		(*g_callBackPtr)();
	}
}
#endif

ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function */
		(*g_callBackPtr)();
	}
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr){


	/* set initial value for the timer */
	TCNT1H=Config_Ptr->initial_value>>8;
	TCNT1L=Config_Ptr->initial_value&0x0f;

	/* Set Prescalar for the timer*/
	TCCR1B=(Config_Ptr->prescaler);



	if(Config_Ptr->mode==CTC){
		/* Choose the compare mode */
		TCCR1B|=(1<<WGM12);
		/* Set Compare Value */
		OCR1A=Config_Ptr->compare_value;

#ifdef  Compare_unit_A
		/*Toggle OC1A on compare match*/
		TCCR1A=(1<<COM1A0);
		/* Enable Interrupt Output Compare A Match */
		TIMSK=(1<<OCIE1A);
#endif

#ifdef Compare_unit_B
		/*Toggle OC1B on compare match*/
		TCCR1A=(1<<COM1B0);
		/* Enable Interrupt Output Compare B Match */
		TIMSK=(1<<OCIE1B);
#endif

	}else if(Config_Ptr->mode==NORMAL){
		/* Enable Interrupt OverFlow */
		TIMSK=(1<<TOIE1);
	}

}

void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}

void Timer1_deInit(void){
	TIMSK=0;
	OCR1B=0;
	OCR1A=0;
	TCCR1B=0;
	TCCR1B=0;
	TCNT1=0;
}
