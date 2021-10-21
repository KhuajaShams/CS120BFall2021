/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 6  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif


enum B_States { B_SMStart, B_Init, B_Blink2, B_Blink3 } B_State;
unsigned char tmpB;

void TickFct_Blink() {
   switch(B_State) { // Transitions
      case B_SMStart:
         B_State = B_Init;
	 tmpB = 0x01;
         break;
      case B_Init: 
         B_State = B_Blink2;
	 tmpB = 0x02;
         break;
      case B_Blink2: 
         B_State = B_Blink3;
	 tmpB = 0x04;
         break;
      case B_Blink3: 
         B_State = B_Init;
	 tmpB = 0x01;
         break;
      default:
         B_State = B_SMStart;
   } 
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	B_State = B_SMStart; 
	tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
	TickFct_Blink();
	PORTB = tmpB;
	while (!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
