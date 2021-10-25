/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 7 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link:
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	LCD_init();
	LCD_DisplayString(1, "Hello World");
    while (1) {
	continue;
    }
    return 1;
}
