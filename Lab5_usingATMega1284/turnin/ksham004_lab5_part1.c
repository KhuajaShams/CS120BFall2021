/*	Author: Khuaja Shams, ksham004@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=8FgRI8Dwjyk	
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	PORTA = 0x00;
	DDRC = 0xFF; 
	PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
	unsigned char tmpA, tmpA2, tmpB;
	tmpA = PINA & 0x0F;
	tmpA2 = PINA & 0x70;
	tmpB = PINC;
	if (tmpA <= 0)
		tmpB = 0x00;
	else if (tmpA <= 2) 
		tmpB = 0x20;
	else if (tmpA <= 4)
		tmpB = 0x30;
	else if (tmpA <= 6) 
		tmpB = 0x38;
	else if (tmpA <= 9)
		tmpB = 0x3C;
	else if (tmpA <= 12)
		tmpB = 0x3E;
	else if (tmpA <= 15)
		tmpB = 0x3F;
	else 
		tmpB = 0x00;

	if (tmpA <= 4)
		tmpB = tmpB | 0x40; 
	if (tmpA2 == 0x30)
		tmpB = tmpB | 0x80;
		
	PORTC = tmpB;
    }
    return 1;
}
