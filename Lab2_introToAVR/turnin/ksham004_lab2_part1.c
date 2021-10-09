/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 2 Exercise # 1
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
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	while(1){
		unsigned char tempA = PINA & 0x03;
		unsigned char tempB = 0x00;

		if (tempA == 0x01) 
			tempB = 0x01;
		
		PORTB = tempB;
		
	}
	return 1;
}



