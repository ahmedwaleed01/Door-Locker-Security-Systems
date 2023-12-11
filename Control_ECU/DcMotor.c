/*
 * DcMotor.c
 *
 *
 * Author: ahmed waleed
 */


#include "DcMotor.h"
#include "GPIO.h"
#include "PWM.h"

void DcMotor_Init(void){
	/*Set Direction pins of motor to be output */
	GPIO_setupPinDirection(INPUT_PORT_ONE_MOTOR,INPUT_PIN_ONE_MOTOR,PIN_OUTPUT);
	GPIO_setupPinDirection(INPUT_PORT_TWO_MOTOR,INPUT_PIN_TWO_MOTOR,PIN_OUTPUT);
    /*Initlize PWM Timer0 with duty cycle equal 0% */
	PWM_Timer0_Start(0);
	/*Initlize Motor To be stopped */
	GPIO_writePin(INPUT_PORT_ONE_MOTOR,INPUT_PIN_ONE_MOTOR,LOGIC_LOW);
	GPIO_writePin(INPUT_PORT_TWO_MOTOR,INPUT_PIN_TWO_MOTOR,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	/*set the modes for motor to be clock or anti or at rest */
	GPIO_writePin(INPUT_PORT_ONE_MOTOR,INPUT_PIN_ONE_MOTOR,(state>>1)&0x01);
	GPIO_writePin(INPUT_PORT_TWO_MOTOR,INPUT_PIN_TWO_MOTOR,state&0x01);
	/*Set the speed for motor by giving it to PWM function*/
	PWM_Timer0_Start(speed);
}

