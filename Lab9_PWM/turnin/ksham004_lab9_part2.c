/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 9 Exercise # 
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=u75oLRLYFgE
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void set_PWM(double frequency) {
  static double current_frequency;
  if (frequency != current_frequency) {
    if (!frequency) { TCCR3B &= 0x08; }
    else { TCCR3B |= 0x03; }
    if (frequency < 0.954) { OCR3A = 0xFFFF; }
    else if (frequency > 31250) { OCR3A = 0x0000; }
    else { OCR3A = (short) (8000000 / (128 * frequency)) - 1; }
    TCNT3 = 0;
    current_frequency = frequency;
  }
}

void PWM_on() {
  TCCR3A = (1 << COM3A0);
  TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
  set_PWM(0);
}

void PWM_off() {
  TCCR3A = 0x00;
  TCCR3B = 0x00;
}

double notes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

enum STATES { start, init, up, down } state;
enum STATES2 { start2, init2, press1, release, press2 } state2;

unsigned char i, tmpA1, tmpA2, tmpA3, sound = 0x00;

void Tick_Sound() {
	switch(state2) {
		case start2:
			state2 = init2;
			sound = 0x01;
			break;
		case init2:
			if (tmpA3 == 0x04)
				state2 = press1;
			else
				state2 = init2;
			break;
		case press1:
			if (tmpA3 == 0x04)
				state2 = press1;
			else {
				state2 = release;
				sound = 0x00;
			}
			break;
		case release:
			if (tmpA3 == 0x04)
				state2 = press2;
			else 
				state2 = release;
			break;
		case press2:
			if (tmpA3 == 0x04)
				state2 = press2;
			else {
				state2 = init2;
				sound = 0x01;
			}
			break;
		default:
			state2 = start2;
			break;
	}
}

void Tick() {
	switch(state) {
		case start:
			state = init;
			i = 0x00;
			break;
		case init:
			if (tmpA1 == 0x01 && tmpA2 == 0x00)
				state = up;
			else if (tmpA1 == 0x00 && tmpA2 == 0x02)
				state = down;
			else 
				state = init;
			break;
		case up:
			if (tmpA1 == 0x01 && tmpA2 == 0x00)
				state = up;
			else {
				state = init;
				if (i < 7)
					i++;
			}
			break;
		case down:
			if (tmpA1 == 0x00 && tmpA2 == 0x002)
				state = down;
			else {
				state = init;
				if (i > 0)
					i--;
			}
			break;

		default:
			state = start;
			break;			
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = start;
	state2 = start2;
	sound = 0x01;
	PWM_on();
    /* Insert your solution below */
    while (1) {
	tmpA1 = ~PINA & 0x01;
	tmpA2 = ~PINA & 0x02;
	tmpA3 = ~PINA & 0x04;
	
	Tick();

	Tick_Sound();
	/*if (tmpA1 == 0x01 && tmpA2 == 0x00 && tmpA3 == 0x00) 
		set_PWM(261.63);
	else if (tmpA2 == 0x02 && tmpA1 == 0x00 && tmpA3 == 0x00)
		set_PWM(293.66);
	else if (tmpA3 == 0x04 && tmpA1 == 0x00 && tmpA2 == 0x00)
		set_PWM(329.63);
	else 
		set_PWM(0.00);*/
	if (!sound)
		set_PWM(0.00);
	else 
		set_PWM(notes[i]);

    }
    return 1;
}
