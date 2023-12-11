/*
 * Module: Timer
 *
 * File Name: Timer.h
 *
 * Description: Source file for the TIMER1 AVR driver
 *
 * Author: ahmed waleed
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

#define Compare_unit_A


typedef enum{
	NO_CLOCK,CLK_1,CLK_8,CLOCK_64,CLOCK_256,CLOCK_1024,
	EXTERNAL_CLK_FALLING,EXTERNAL_CLK_RISING
}Timer1_Prescaler;

typedef enum{
	NORMAL,PWM_8_BIT,PWM_9_BIT,PWM_10_BIT,
	CTC,FAST_PWM_8_BIT,FAST_PWM_9_BIT,FAST_PWM_10_BIT,
	FAST_PWM=15
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value;
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


void Timer1_init(const Timer1_ConfigType * Config_Ptr);

void Timer1_deInit(void);

void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
