/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 8 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=t8VdTKRZQdY 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0xFF; PORTD = 0x00;
	unsigned char tmpB = 0x00;
	unsigned short MAX = 0x138;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	unsigned short my_short = ADC;
	if (my_short >= MAX/2)
		tmpB = 0x01;
	else 
		tmpB = 0x00;

	PORTD = tmpB;
    }
    return 1;
}
