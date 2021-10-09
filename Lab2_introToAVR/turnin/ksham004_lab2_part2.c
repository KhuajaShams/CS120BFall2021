/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 2 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *
 */


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void){
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	while(1){
		unsigned char tempA = PINA & 0x0F;
		unsigned char cntavail = 0x04;

		for (unsigned int i = 0; i < 4; i++) {
			if ((tempA & 0x01) == 1) 
				cntavail--;
			tempA = tempA >> 1;
		}

		PORTC = cntavail;
		
	}
	return 1;
}



