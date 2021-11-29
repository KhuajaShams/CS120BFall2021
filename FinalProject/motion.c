/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 11 Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=GwGamCsQtUc 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "io.h"
#include <math.h>
#endif




int main(void) {
    /* Insert DDR and PORT initializations */
	
	DDRA = 0x00; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(500);
	TimerOn();
	unsigned char tmpA, tmpD = 0x00;
    while (1) {
	tmpA = PINA & 0x01;
	if (tmpA == 0x01)
		tmpD = 0xFF; 
	else
		tmpD = 0x00;	
	PORTD = tmpD;
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
