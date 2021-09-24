/*
 * drivers V1.c
 *
 * Created: 9/20/2021 1:33:51 PM
 * Author : Karim Essam
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/USART/USART_interface.h"
#include "MCAL/SPI/SPI_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/LED/LED_interface.h"
#include "MCAL/DIO/DIO_interface.h"

void turnOffLeds(LED_t* redLed ,LED_t* yellowLed ,LED_t* greenLed )
{
	LED_voidTurnOff(greenLed);
	LED_voidTurnOff(yellowLed);
	LED_voidTurnOff(redLed);
}
int main(void)
{
	LED_t redLed = {.pin = 0 , .port = PORTA};
	LED_t yellowLed = {.pin = 1 , .port = PORTA};
	LED_t greenLed = {.pin = 2 , .port = PORTA};

	LED_voidInit(&redLed);
	LED_voidInit(&yellowLed);
	LED_voidInit(&greenLed);

    /* Replace with your application code */
	USART_voidInit(TRANSMIT_RECIEVE , ASYNCRONOUS , EIGHT_BITS , DISAPLED , TWO_STOP_BIT , 2400);
	LCD_voidInit();
	/*
	SPI_voidInit(MASTER_MODE , MSB , LEADING_IS_RISING , LEADING_IS_SAMPLE , SPI_PRESCALAR_16);
	for (u8 i = 0 ; i < 10 ; i++)
	{
		SPI_voidMasterTransmit(i);
		_delay_ms(100);
	}
	*/
	u8 string[10];
	u8 index = 0;
    while (1) 
    {
		u8 data = USART_u8RecieveData();
		// if backspace
		if (data == 0x08)
			index--;
		// add data if it is not enter
		else if (data != '\r')	
			string[index++] = data;
		if (data == '\r' && string[0] != NULL)
		{
			turnOffLeds(&redLed ,&yellowLed , &greenLed);
			if (strcmp(string ,"START") == 0)
			{
				LED_voidTurnOn(&greenLed);
				USART_voidTransmitString("Green Led is turned on");
			}else if(strcmp(string ,"STOP") == 0)
			{
				LED_voidTurnOn(&redLed);
				USART_voidTransmitString("Red Led is turned on");
			}else if (strcmp(string ,"WAIT") == 0)
			{
				LED_voidTurnOn(&yellowLed);
				USART_voidTransmitString("Yellow Led is turned on");
			}else if (strcmp(string ,"AT") == 0)
			{
				USART_voidTransmitString("OK");
			}
			// clear string
			memset(string, 0, sizeof(string));
			index = 0;
		}
		
    }
}
