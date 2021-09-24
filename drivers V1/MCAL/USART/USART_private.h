/*
 * USART_private.h
 *
 * Created: 9/21/2021 1:47:16 PM
 *  Author: Karim Essam
 */ 


#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_
	
#define UDR_REG					(*(volatile u8*)0x2C)
#define UCSRA_REG				(*(volatile u8*)0x2B)
#define UCSRB_REG				(*(volatile u8*)0x2A)
#define UCSRC_REG				(*(volatile u8*)0x40)
#define UBRRH_REG				(*(volatile u8*)0x40)
#define UBRRL_REG				(*(volatile u8*)0x29)
//for GIE
#define SREG_REG 				(*(volatile u8*)(0x5F))



#define  USART_ISR_RECIEVE_COMPLETE		__vector_13
#define  USART_ISR_TRANSMIT_COMPLETE	__vector_15
#define  USART_ISR_REGISTER_EMPTY		__vector_14

void USART_ISR_RECIEVE_COMPLETE(void)	__attribute__((signal,used));
void USART_ISR_TRANSMIT_COMPLETE(void)	__attribute__((signal,used));
void USART_ISR_REGISTER_EMPTY(void)	__attribute__((signal,used));

void (*USART_callBacks[2])(void) = {0,0};
void (*USART_recieveCallBack)(u8) = 0;

#endif /* USART_PRIVATE_H_ */