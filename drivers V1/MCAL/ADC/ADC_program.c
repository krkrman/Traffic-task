/*
 * ADC_program.c
 *
 * Created: 9/15/2021 2:17:55 PM
 *  Author: Karim Essam
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_interface.h"
#include "ADC_private.h"
#include "ADC_interface.h"


void ADC_voidInit(ADC_Mode_t mode,ADC_AutoTrigger_t triggerSource, ADC_Prescalar_t prescalar)
{
	 ADCSRA_REG = (mode<<5) | (prescalar) | (3<<6);
	 SFIOR_REG |= (triggerSource << 5);
	 // select right adjusted
	 
	 /*
	 CLR_BIT(ADMUX_REG , 5);
	 SET_BIT(ADMUX_REG , 6);
	 CLR_BIT(ADMUX_REG , 7);
	 */
	 ADMUX_REG = (2 << 5);

	 adcMode = mode;
}

void ADC_voidStartConversion(ADC_ChannelID_t channel)
{
	DIO_voidSetPinDirection(channel , PORTA , INPUT);
	// clear channels
	ADMUX_REG &= 0b11100000;
	//select channel
	ADMUX_REG |= channel;
	// start conversion
	SET_BIT(ADCSRA_REG , 6);
	adcChannel = channel;
}

u16 ADC_u16ReadChannel()
{
	if (adcMode == ADC_MODE_SINGLE_CONVERSION)
	{
		while(GET_BIT(ADCSRA_REG , 6));
		return ADCHL_REG;
	}else {
		return ADCHL_REG;
	}
}

void ADC_voidEnableInterruptWithCallback(ADC_ChannelID_t channel , void (*callback)(u16))
{
	//enable ADC interrupt
	SET_BIT(ADCSRA_REG , 3);
	// enable GIE
	SET_BIT(SREG_REG,7);
	ADC_callback = callback;
	ADC_voidStartConversion(channel);
};

void ADC_ISR_VECTOR(void)
{
	if (ADC_callback != 0)
	{
		ADC_callback(ADCHL_REG);
		SET_BIT(ADCSRA_REG , 4);
		if (adcMode == ADC_MODE_COUNTINOUS_CONVERSION)
		{
			ADC_voidStartConversion(adcChannel);
		}
	}
}