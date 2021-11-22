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
#endif



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char vert, horz, sel, tmpD = 0x00;
	
    while (1) {
	    horz = ~PINC & 0x01;
	    vert = ~PINC & 0x02;
	    sel = ~PINC & 0x04;
	tmpD = 0xF0;
	if (horz == 0x01)
		tmpD = tmpD | 0x01;
	if (vert == 0x02)
		tmpD = tmpD | 0x02;
	if (sel == 0x04) 
		tmpD = tmpD | 0x04;
	PORTD = tmpD;

    }
    return 1;
}
