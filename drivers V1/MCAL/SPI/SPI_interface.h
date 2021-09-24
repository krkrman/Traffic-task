/*
 * SPI_interface.h
 *
 * Created: 9/22/2021 4:28:45 AM
 *  Author: Karim Essam
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

typedef enum{
	MSB,
	LSB
}DataOrder_t;

typedef enum{
	SLAVE_MODE,
	MASTER_MODE
}SPI_Mode_t;

typedef enum{
	LEADING_IS_RISING,
	LEADING_IS_FALLING	
}ClockPolarity_t;

// this specify when data is sampled
typedef enum{
	LEADING_IS_SAMPLE,
	TRAILING_IS_SAMPLE
}ClockPhase_t;

typedef enum{
	SPI_PRESCALAR_4,
	SPI_PRESCALAR_16,
	SPI_PRESCALAR_64,
	SPI_PRESCALAR_128,
	SPI_PRESCALAR_2,
	SPI_PRESCALAR_8,
	SPI_PRESCALAR_32,
}SPI_Prescalar_t;

void SPI_voidInit(SPI_Mode_t mode , DataOrder_t dataOrder , ClockPolarity_t clockPolarity , ClockPhase_t clockPhase , SPI_Prescalar_t prescalar);

void SPI_voidMasterTransmit(u8 data);

u8 SPI_u8SlaveRecieve();

void SPI_voidMasterTransmitString(u8* string);
//void SPI_voidEnableInterruptWithCallback();

#endif /* SPI_INTERFACE_H_ */