/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #2
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
unsigned char tmpC = 0x00;

enum SM1_STATES { SM1_SMStart, SM1_Init } SM1_STATE;
void Tick_LoHi() {
   switch(SM1_STATE) {
      case SM1_SMStart:
         SM1_STATE = SM1_Init;
	 tmpC = 0x07;
         break;
      case SM1_Init:
         if (tmpA == 0x00) { 
            SM1_STATE = SM1_Init;}
	 else if (tmpA == 0x01) { 
            SM1_STATE = SM1_Init;
	    if (tmpC < 9) {
		tmpC = tmpC + 1;}
	 }
	 else if (tmpA == 0x02) {
	    SM1_STATE = SM1_Init;
	    if (tmpC > 0){
		tmpC = tmpC - 1;}
	 }
	 else if (tmpA == 0x03) {
            SM1_STATE = SM1_Init;
	    tmpC = 0;
	 }
         break;
      default:
         SM1_STATE = SM1_Init;
         break;
   }
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
    	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	SM1_STATE = SM1_SMStart;
    	while (1) {
		tmpA = PINA;
		Tick_LoHi();
		PORTC = tmpC;
    	}
    	return 1;
}
