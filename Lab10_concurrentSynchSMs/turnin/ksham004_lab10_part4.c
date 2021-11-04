/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 10 Exercise # 4 
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=78yB1x1GS2w 
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

unsigned char tmpA1, tmpA2, tmpA3, led1, led2, blinkingled, speaker = 0x00;
unsigned long freq;

enum TL_States {tlstart, tlinit, tl2, tl3} tlstates; 
enum BL_States {blstart, blinit, bl2} blstates;
enum CL_States {clstart, clinit} clstates;
enum F_States {fstart, finit, fup, fdown} fstates;
enum S_States {sstart, sinit, son, soff} sstates;


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

void FreqSM() {
	switch(fstates) {
		case fstart:
			fstates = finit;
			freq = 5;
			break;
		case finit:
			if (tmpA1 == 0x01 && tmpA2 == 0x00)
				fstates = fup;
			else if (tmpA1 == 0x00 && tmpA2 == 0x02)
				fstates = fdown;
			else 
				fstates = finit;
			break;
		case fup:
			if (tmpA1 == 0x01) 
				fstates = fup;
			else {
				fstates = finit;
				if (freq > 1) 
					freq = freq - 1;
			}	
			break;
		case fdown:
			if (tmpA2 == 0x02)
				fstates = fdown;
			else {
				fstates = finit;
				if (freq < 10) 
					freq = freq + 1;
			}
			break;
	}
}

void SpeakerSM() {
	switch(sstates) {
		case sstart:
			sstates = sinit;
			break;
		case sinit:
			if (tmpA3 == 0x04)
				sstates = son;
			else 
				sstates = sinit;
			speaker = 0x00;
			break;
		case son:
			if (tmpA3 == 0x04) 
				sstates = soff;
			else 
				sstates = sinit;
			speaker = 0x10;
			break;
		case soff:
			if (tmpA3 == 0x04)
				sstates = son;
			else
				sstates = sinit;
			speaker = 0x00;
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	blinkingled = 0x00;
	unsigned long period = 1;
	TimerSet(period);
	TimerOn();

	unsigned long tltime = 300;
	unsigned long bltime = 1000;
	unsigned long stime = 20;
	
	tlstates = tlstart;
	blstates = blstart;
	clstates = clstart;
	fstates = fstart;
	sstates = sstart;

    /* Insert your solution below */
    while (1) {
	//freq = 20;
	tmpA1 = ~PINA & 0x01;
	tmpA2 = ~PINA & 0x02;
	tmpA3 = ~PINA & 0x04;

	if (tltime >= 300) {
		ThreeLEDsSM();
		tltime = 0;
	}
	if (bltime >= 1000) {
		BlinkingLEDSM();
		bltime = 0;
	}
	FreqSM();
	if (stime >= freq) {
		SpeakerSM();
		stime = 0;
	}	
	CombineLEDsSM();
	PORTB = blinkingled | speaker;
	
	while(!TimerFlag);
	TimerFlag = 0;
	stime += period;
        tltime += period;
	bltime += period; 	
    }
    return 1;
}
