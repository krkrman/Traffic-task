/*
 * LM35.c
 *
 * Created: 9/19/2021 11:50:36 PM
 *  Author: Karim Essam
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "LM35_interface.h"


f32 static getDegree(u16 adcValue){
	f32 voltage = (f32) (adcValue * 5.0 / 1024.0 );
	return voltage*100;
}
void LM35_voidInit()
{
	ADC_voidInit(ADC_MODE_SINGLE_CONVERSION , ADC_AUTO_TRIGGER_FREE_RUNNING , ADC_PRESCALAR_DIV_8);
}
u8 LM35_u8GetTemp(LM35* lm35)
{
	ADC_voidStartConversion(ADC_CHANNEL_SINGLE_0);
	return (u8)getDegree(ADC_u16ReadChannel());
}


