/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

enum STATES { SMStart, Init, PressB1, ReleaseB1, PressB0, ReleaseB0} STATE;
void Tick_LoHi() {
       switch(STATE) {
		case SMStart:
			STATE = Init;
			break;
		case Init:
			if (tmpA)
				STATE = PressB1;
			else if (!tmpA)
				STATE = Init;
			else 
				STATE = Init;
			break;
		case PressB1:
			if (tmpA)
				STATE = PressB1;
			else if (!tmpA)
				STATE = ReleaseB1;
			else
				STATE = PressB1;
			break;
		case ReleaseB1:
			if (tmpA)
				STATE = PressB0;
			else if (!tmpA)
				STATE = ReleaseB1;
			else
				STATE = ReleaseB1;
			break;
		case PressB0:
			if (tmpA)
				STATE = PressB0;
			else if (!tmpA)
				STATE = ReleaseB0;
			else
				STATE = PressB0;
			break;
		case ReleaseB0:
			if (tmpA)
				STATE = PressB1;
			else if (!tmpA)
				STATE = ReleaseB0;
			else
				STATE = ReleaseB0;
			break;				
		default: 
			STATE = PressB1;
			break;
	}	       
   	switch(STATE) { 
      		case SMStart:
         		break;
      		case Init:
			tmpB = 0x01;
     		 	break;
		case PressB1:
			tmpB = 0x02;
			break;
		case ReleaseB1:
			break;
		case PressB0:
			tmpB = 0x01;
			break;
		case ReleaseB0:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
	DDRA = 0xFF; PORTB = 0x00;	
    /* Insert your solution below */
	while (1) {
		tmpA = PINA & 0x01;
		Tick_LoHi();
		PORTB = tmpB;	
   	 }
   	 return 1;
}
