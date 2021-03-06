/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 10 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=XJl47IF4O5w 
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

unsigned char led1, led2, blinkingled = 0x00;

enum TL_States {tlstart, tlinit, tl2, tl3} tlstates; 
enum BL_States {blstart, blinit, bl2} blstates;
enum CL_States {clstart, clinit} clstates;

void ThreeLEDsSM() {
	switch(tlstates) {
		case tlstart:
			tlstates = tlinit;
			led1 = 0x00;
			break;
		case tlinit:
			tlstates = tl2;
			led1 = 0x01;
			break;
		case tl2:
			tlstates = tl3;
			led1 = 0x02;
			break;
		case tl3:
			tlstates = tlinit;
			led1 = 0x04;
			break;
	}
}

void BlinkingLEDSM() {
	switch (blstates) {
		case blstart:
			blstates = blinit;
			led2 = 0x00;
			break;
		case blinit:
			blstates = bl2;
			led2 = 0x00;
			break;
		case bl2:
			blstates = blinit;
			led2 = 0x08;
			break;
	}
}

void CombineLEDsSM() {
	switch(clstates) {
		case clstart:
			clstates = clinit;
			blinkingled = 0x00;
			break;
		case clinit:
			clstates = clinit;
			blinkingled = led1 | led2; 
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	blinkingled = 0x00;
	unsigned long period = 100;
	TimerSet(period);
	TimerOn();

	unsigned long tltime = 300;
	unsigned long bltime = 1000;

	tlstates = tlstart;
	blstates = blstart;
	clstates = clstart;
    /* Insert your solution below */
    while (1) {
	if (tltime >= 300) {
		ThreeLEDsSM();
		tltime = 0;
	}
	if (bltime >= 1000) {
		BlinkingLEDSM();
		bltime = 0;
	}

	CombineLEDsSM();
	PORTB = blinkingled;
	
	while(!TimerFlag);
	TimerFlag = 0;
        tltime += period;
	bltime += period; 	
    }
    return 1;
}
