/*
 * USART_program.c
 *
 * Created: 9/20/2021 1:38:23 PM
 *  Author: Karim Essam
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../CLOCK/CLOCK_interface.h"
#include "USART_private.h"
#include "USART_interface.h"


void USART_voidInit(USART_Type type ,USART_Mode mode ,USART_DataBitNumber dataBitNumber, USART_ParityMode parityMode , USART_StopBitNumber stopBitsNumber,u16 baudRate)
{
	u16 UBRR;
	if (mode == ASYNCRONOUS)
	{
		UBRR = CLOCK_u32GetSystemClock()/(16 * baudRate)-1;
	}else {
		UBRR = CLOCK_u32GetSystemClock()/(2 * baudRate)-1;
	}
	CLR_BIT(UBRRH_REG , 7);
	UBRRH_REG = (UBRR>>8);
	UBRRL_REG = (UBRR);
	
	UCSRB_REG = (type << 3);

	SET_BIT(UBRRH_REG , 7);
	UCSRC_REG = (1<<7)|(mode << 6)|(parityMode<<4)|(stopBitsNumber<<3)|(dataBitNumber << 1);
}

void USART_voidEnableInterruptWithCallback(USART_Interrupt interrupt , void *callBack)
{
	SET_BIT(SREG_REG , 7);
	SET_BIT(UCSRB_REG , interrupt);
	if (interrupt == RECIEVE_COMPLETE_INTERRUPT)
	{
		USART_recieveCallBack = (void (*)(u8))callBack;

	}else{
		USART_callBacks[interrupt-5] = (void (*)(void))callBack;
	}
}

void USART_voidDisableInterrupt(USART_Interrupt interrupt)
{
	CLR_BIT(UCSRB_REG , interrupt);
}

u8 USART_u8RecieveData(void)
{
	/* Wait for data to be received */
	while ( !GET_BIT(UCSRA_REG , 7));

	return UDR_REG;
}
void USART_voidTransmitChar(u8 data)
{
	/* Wait for empty transmit buffer */
	while (!GET_BIT(UCSRA_REG , 5));
	/* Put data into buffer, sends the data */
	UDR_REG = data;
}
void USART_voidTransmitString(u8* string)
{
	u8 i = 0;
	while(string[i] != '\0')
	{
		USART_voidTransmitChar(string[i]);
		i++;
	}
}

void USART_ISR_RECIEVE_COMPLETE(void)
{
	if (*USART_recieveCallBack != 0)
	{
		USART_recieveCallBack(UDR_REG);
	}
}

void USART_ISR_TRANSMIT_COMPLETE(void)
{
	if (USART_callBacks[1] != 0)
	{
		USART_callBacks[1]();
	}
}
void USART_ISR_REGISTER_EMPTY(void)
{
	if (USART_callBacks[0] != 0)
	{
		USART_callBacks[0]();
	}
}
