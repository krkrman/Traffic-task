/*
 * SPI_program.c
 *
 * Created: 9/22/2021 4:29:00 AM
 *  Author: Karim Essam
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO_interface.h"

#include "SPI_private.h"
#include "SPI_interface.h"

void SPI_voidInit(SPI_Mode_t mode , DataOrder_t dataOrder , ClockPolarity_t clockPolarity , ClockPhase_t clockPhase , SPI_Prescalar_t prescalar)
{
	if (mode == MASTER_MODE)
	{
		DDRB_REG |= 0b10110000;
	}else
	{
		DDRB_REG |= 0b01000000;
	}
	SPSR_REG = GET_BIT(prescalar , 2);
	CLR_BIT(prescalar , 2);
	SPCR_REG = (1<<6) | (dataOrder << 5) | (mode << 4) | (clockPolarity << 3) | (1 << 2) | (prescalar);
}

void SPI_voidMasterTransmit(u8 data)
{
	/* Start transmission */
	SPDR_REG = data;
	/* Wait for transmission complete */
	while(GET_BIT(SPSR_REG,7) == 0);
}

u8 SPI_u8SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!GET_BIT(SPSR_REG,7));
	/* Return data register */
	return SPDR_REG;
}