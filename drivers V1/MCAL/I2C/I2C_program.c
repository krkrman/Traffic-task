/*
 * I2C.c
 *
 * Created: 9/23/2021 9:05:13 AM
 *  Author: Karim Essam
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../CLOCK/CLOCK_interface.h"

#include "I2C_private.h"
#include "I2C_interface.h"

void I2C_voidInitMaster(I2C_Prescalar_t prescalar , u32 frequency)
{
	TWBR_REG = (CLOCK_u32GetSystemClock()/(2*prescalars[prescalar]))-16;
	TWSR_REG = prescalar;
	//enable acknowledge
	SET_BIT(TWCR_REG , 6);
	// enable
	SET_BIT(TWCR_REG , 2);
}
  
void I2C_voidInitSlave(u8 slaveAddress)
{
	TWAR_REG = (slaveAddress<<1);
	// enable
	SET_BIT(TWCR_REG , 2);
}

void I2C_voidSendStartCondition()
{
	// clear flag to send
	SET_BIT(TWCR_REG , 7);
	// send start condition
	SET_BIT(TWCR_REG , 5);
	
	while (!GET_BIT(TWCR_REG , 7));
	while ((TWSR>>3) != START_CONDITION);
}

void I2C_voidSendRepeatedStart()
{
	// clear flag to send
	SET_BIT(TWCR_REG , 7);
	// send start condition
	SET_BIT(TWCR_REG , 5);
	
	while (!GET_BIT(TWCR_REG , 7));
	while ((TWSR>>3) != REPEATED_START_CONDITION);
}

void I2C_voidSendWriteCommand(u8 slaveAddress)
{
	TWDR_REG = (slaveAddress<<1);

	// clear flag to send
	SET_BIT(TWCR_REG , 7);
	// send start condition
	SET_BIT(TWCR_REG , 5);
	
	while (!GET_BIT(TWCR_REG , 7));
	while ((TWSR>>3) != SLAVE_ADDRESS_AND_WRITE);
}

void I2C_voidSendReadCommand(u8 slaveAddress)
{
	TWDR_REG = (slaveAddress<<1);
	//to read
	TWDR_REG |= 1;
	
	// clear flag to send
	SET_BIT(TWCR_REG , 7);
	// send start condition
	SET_BIT(TWCR_REG , 5);
	
	while (!GET_BIT(TWCR_REG , 7));
	while ((TWSR>>3) != SLAVE_ADDRESS_AND_READ);
}
 
 void I2C_voidTransmitData(u8 data){
	TWDR_REG = data;
	// clear flag to send
	SET_BIT(TWCR_REG , 7);
	// send start condition
	SET_BIT(TWCR_REG , 5);
	
	while (!GET_BIT(TWCR_REG , 7));
	while ((TWSR>>3) != DATA_TRANSMITTED);
 }
 
 u8 I2C_u8RecieveData(void)
 {
	 // clear flag to send
	 SET_BIT(TWCR_REG , 7);
	 // send start condition
	 SET_BIT(TWCR_REG , 5);
	 
	 while (!GET_BIT(TWCR_REG , 7));
	 while ((TWSR>>3) != DATA_TRANSMITTED);
	 return TWDR_REG;
 }
 
void I2C_voidSendStopCondition()
{
	// clear flag to send
	SET_BIT(TWCR_REG , 7);
	// send start condition
	SET_BIT(TWCR_REG , 4);
	
	while (!GET_BIT(TWCR_REG , 7));
	while ((TWSR>>3) != S);
}
