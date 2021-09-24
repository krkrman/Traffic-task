/*
 * motor_interface.h
 *
 * Created: 9/18/2021 1:28:45 PM
 *  Author: Karim Essam
 */ 


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef struct
{
	DIO_PORT_t port;
	u8 pin1;
	u8 pin2;
	u8 PWM_pin;

}Motor_t;

typedef enum{
	ROTATION_CLOCK_WISE,
	ROTATION_COUNTER_CLOCK_WISE
}RotationDirection_t;

void MOTOR_voidInit(Motor_t* motor);
void MOTOR_voidRotateWithSoftwarePWM(Motor_t* motor,u8 duty_cycle ,RotationDirection_t );
void MOTOR_voidStop(Motor_t* motor);


#endif /* MOTOR_INTERFACE_H_ */