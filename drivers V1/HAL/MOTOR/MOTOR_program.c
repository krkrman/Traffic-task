/*
 * MOTOR_program.c
 *
 * Created: 9/18/2021 1:33:50 PM
 *  Author: Karim Essam
 */ 

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER0/TIMER0_interface.h"
#include "../../LIB/STD_TYPES.h"
#include "MOTOR_interface.h"

void MOTOR_voidInit(Motor_t* motor)
{
	TIMER0_voidInit(TIMER0_CTC_MODE , TIMER0_CTC_DISCONNECT , TIMER0_PRESCALAR_64 , 0);
	DIO_voidSetPinDirection(motor->pin1 , motor->port , OUTPUT);
	DIO_voidSetPinDirection(motor->pin2 , motor->port , OUTPUT);	
}

void MOTOR_voidRotateWithSoftwarePWM(Motor_t* motor , u8 dutyCycle , RotationDirection_t rotationDirection)
{
	if (rotationDirection)
	{
		DIO_voidSetPinValue(motor->pin1 , motor->port , LOW);
		DIO_voidSetPinValue(motor->pin2 , motor->port , HIGH);
	}else 
	{
		DIO_voidSetPinValue(motor->pin1 , motor->port , HIGH);
		DIO_voidSetPinValue(motor->pin2 , motor->port , LOW);
	}
	TIMER0_voidSoftwarePWM(motor->port , motor->PWM_pin , dutyCycle);
}

void MOTOR_voidStop(Motor_t* motor)
{
	DIO_voidSetPinValue(motor->pin1 , motor->port , LOW);
	DIO_voidSetPinValue(motor->pin2 , motor->port , LOW);
}
