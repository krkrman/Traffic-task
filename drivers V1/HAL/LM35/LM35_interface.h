/*
 * LM35.h
 *
 * Created: 9/19/2021 11:50:18 PM
 *  Author: Karim Essam
 */ 


#ifndef LM35_H_
#define LM35_H_

typedef struct {
	u8 analogPin;
}LM35;

void LM35_voidInit();
u8 LM35_u8GetTemp(LM35* lm35);

#endif /* LM35_H_ */