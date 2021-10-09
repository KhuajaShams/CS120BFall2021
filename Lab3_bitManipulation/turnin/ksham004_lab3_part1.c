/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	PORTA = 0x00;
	DDRB = 0x00; 
	PORTB = 0x00;
	DDRC = 0x00; 
	PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
	    unsigned char tmpA, tmpB, num_ones;
	    tmpA = PINA;
	    tmpB = PINB;
	    num_ones =  0;

	    for (unsigned int i = 0;i < 8; i++) {
		if ((tmpA & 0x01) == 1) 
           	 	num_ones++;
         	if ((tmpB & 0x01) == 1) 
            		num_ones++;
         	tmpA = tmpA >> 1;
		tmpB = tmpB >> 1;
	    }
	    PORTC = num_ones; 
	    

    }
    return 1;
}
