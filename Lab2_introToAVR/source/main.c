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
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	while(1){
		unsigned char temp1 = 0x00;
		unsigned char temp2 = 0x00;
		unsigned char tempB = 0x00;

		temp1 = PINA & 0x01;
		temp2 = PINA & 0x02;
		if (temp1 && !temp2)
			tempB = 0x01;
		else
			tempB = 0x00;

		PORTB = tempB;
		
	}
	return 1;
}



