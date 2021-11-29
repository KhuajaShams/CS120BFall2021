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
#include <string.h>
#endif


typedef struct task {
	unsigned char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct) (int);
} task;



void ADC_init() {
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0x00; PORTC = 0x7F;
	DDRD = 0xFF; PORTD = 0x00;


	TimerSet(300);
	TimerOn();
	LCD_init();
	ADC_init();
	unsigned char text[40] = "                                        ";
	unsigned char motion_msg[6] = "MOTION";
	unsigned char tmpC, motion, tmpD = 0x00;

    while (1) {
	tmpD = 0x00;
	tmpC = ~PINC & 0x07;
	motion = PINC & 0x80;
	strcpy( (unsigned char*) text, "                               ");

	if (tmpC == 0x02) { //horz
		tmpD = tmpD | 0x02;
		strcpy( (unsigned char*) text, "            horz        ");
	}
	if (tmpC == 0x04) { //vert
		tmpD = tmpD | 0x04;
                strcpy( (unsigned char*) text, "            vert        ");
	}
	if (tmpC == 0x01) { //selc 
		tmpD = tmpD | 0x01;
                strcpy( (unsigned char*) text, "            selc        ");
	}

	if (motion == 0x80) {
		tmpD = tmpD | 0x08;
		for ( int i = 16; i < 22; i++) 
			text[i] = motion_msg[i - 16]; 
	}

	PORTD = tmpD;

	float temper = ADC;
	float temperature = (30 + ((10.888 - sqrt(118.548544 + 0.01388*(1777.3 - temper)))/-0.00694)) - 129 ;

	unsigned char tmp = temperature/10  + '0';
	unsigned char tmp1 = (int)temperature % 10 + '0';
	text[0] = tmp;
	text[1] = tmp1;
	text[3] = 'C';
	LCD_DisplayString(1, text);
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
