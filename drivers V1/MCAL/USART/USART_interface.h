/*
 * USART_interface.h
 *
 * Created: 9/20/2021 1:38:02 PM
 *  Author: Karim Essam
 */ 


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

typedef enum
{
	EMPTY_REGISTER_INTERRUPT = 5,
	TRANSMIT_COMPLETE_INTERRUPT,
	RECIEVE_COMPLETE_INTERRUPT,
}USART_Interrupt;

typedef enum
{
	TRANSMIT = 1,
	RECIEVE ,
	TRANSMIT_RECIEVE,
}USART_Type;

typedef enum
{
	ASYNCRONOUS,
	SYNCRONOUS
}USART_Mode;

typedef enum
{
	DISAPLED,
	EVEN_PARITY=2,
	ODD_PARITY,
}USART_ParityMode;

typedef enum
{
	ONE_STOP_BIT,
	TWO_STOP_BIT
}USART_StopBitNumber;

typedef enum
{
	FIVE_BITS,
	SIX_BITS,
	SEVEN_BITS,
	EIGHT_BITS,
}USART_DataBitNumber;

// Recommended init 	USART_voidInit(TRANSMIT_RECIEVE , ASYNCRONOUS , EIGHT_BITS , DISAPLED , TWO_STOP_BIT , 2400);
void USART_voidInit(USART_Type type ,USART_Mode mode ,USART_DataBitNumber dataBitNumber, USART_ParityMode parityMode , USART_StopBitNumber stopBitsNumber  , u16 baudrate);

void USART_voidEnableInterruptWithCallback(USART_Interrupt interrupt , void *callBack);
void USART_voidDisableInterrupt(USART_Interrupt interrupt);

u8 USART_u8RecieveData(void);
void USART_voidTransmitChar(u8 data);
void USART_voidTransmitString(u8* string);

#endif /* USART_INTERFACE_H_ */