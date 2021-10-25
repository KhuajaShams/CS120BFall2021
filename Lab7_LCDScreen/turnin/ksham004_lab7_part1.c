/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 7 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=dK097MEAZI0
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpA, tmpC; 

enum States {SMStart, Init, Increment, Decrement } State;

void Tick() {
	switch(State) {
		case SMStart:
		       State = Init;
		       tmpC = 0x00;
		       break;
	        case Init:
			if (tmpA == 0x01) 
		 		State = Increment;
			else if (tmpA == 0x02)
				State = Decrement;
			else if (tmpA == 0x03) 
				State = SMStart;
			else 
				State = Init;
			break;
		case Increment:
			if (tmpA == 0x01) 
                                State = Increment;
                        else if (tmpA == 0x02)
                                State = Decrement;
                        else if (tmpA == 0x03)
                                State = SMStart;
                        else
                                State = Init;
			if (tmpC < 9)
				tmpC++;
			break;
		case Decrement:
			if (tmpA == 0x01) 
                                State = Increment;
                        else if (tmpA == 0x02)
                                State = Decrement;
                        else if (tmpA == 0x03)
                                State = SMStart;
                        else
                                State = Init;
			if (tmpC > 0)
				tmpC--;
			break;
		default:
			State = SMStart;
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	TimerSet(1000);
	TimerOn();
	tmpA = 0x00;
    /* Insert your solution below */
	LCD_init();
	State = SMStart;
    while (1) {
	    LCD_ClearScreen();
	    tmpA = ~PINA & 0x03;
	    Tick();
	    PORTC = tmpC;
	    LCD_WriteData(tmpC + '0');
	    while(!TimerFlag);
	    TimerFlag = 0; 
    }
}
