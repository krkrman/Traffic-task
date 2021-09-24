/*
 * I2C_private.h
 *
 * Created: 9/23/2021 8:19:30 AM
 *  Author: Karim Essam
 */ 


#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define START_CONDITION				0x08
#define REPEATED_START_CONDITION	0x10
#define SLAVE_ADDRESS_AND_WRITE		0x18
#define DATA_TRANSMITTED			0x28
#define ARBITRATION_LOST			0x38
#define SLAVE_ADDRESS_AND_READ		0x40
#define DATA_RECIEVED				0x50

#define TWBR_REG				(*(volatile u8*	)0x20)
#define TWSR_REG				(*(volatile u8*	)0x21)
#define TWAR_REG				(*(volatile u8*	)0x22)
#define TWDR_REG				(*(volatile u8*	)0x23)
#define TWCR_REG				(*(volatile u8*	)0x56)

u8 prescalars[] = {1,4,16,64};
#endif /* I2C_PRIVATE_H_ */