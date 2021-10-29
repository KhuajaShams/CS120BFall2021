/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 8 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=1qAkie2KkWQ 
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
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned char tmpB, tmpD = 0x00;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	unsigned short my_short = ADC;
	tmpB = (char) my_short;
	tmpD = (char) (my_short >> 8);
	PORTB = tmpB;
	PORTD = tmpD;
    }
    return 1;
}
