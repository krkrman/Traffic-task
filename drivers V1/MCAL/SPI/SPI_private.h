/*
 * SPI_private.h
 *
 * Created: 9/22/2021 4:28:31 AM
 *  Author: Karim Essam
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define SPCR_REG			(*(volatile u8*)0x2D)
#define SPSR_REG			(*(volatile u8*)0x2E)
#define SPDR_REG			(*(volatile u8*)0x2F)
#define DDRB_REG			(*(volatile u8*)0x37)

void (*SPI_callBacks)(void) = 0;

#define SPI_ISR			__vector_12
void SPI_ISR(void)	__attribute__((signal,used));




#endif /* SPI_PRIVATE_H_ */