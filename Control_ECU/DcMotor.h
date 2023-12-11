/*
 * DcMotor.h
 *
 *
 * Author: ahmed waleed
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

#define INPUT_PORT_ONE_MOTOR       PORTB_ID
#define INPUT_PIN_ONE_MOTOR        PIN0_ID

#define INPUT_PORT_TWO_MOTOR       PORTB_ID
#define INPUT_PIN_TWO_MOTOR        PIN1_ID


typedef enum{
	STOP,CLOCK_WISE,ANTI_CLOCK_WISE
}DcMotor_State;

void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
