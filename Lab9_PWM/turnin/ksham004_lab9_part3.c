/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 9 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=fZ0LjSP6mXw
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
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

unsigned char tmpA1, i = 0x00;

double m1[6] = {440.00, 293.66, 392.00, 349.23, 392.00, 261.63};

enum STATES { start, init, p1, r1 } state;

void Tick() {
	switch(state) {
		case start:
			state = init;
			break;
		case init:
			i = 0;
			set_PWM(0.00);
			if (tmpA1 == 0x01)
				state = p1;
			else 
				state = init;
			break;
		case p1:
			if (i < 6) { 
				set_PWM(m1[i]);
				state = p1;
				i++;
			}
			else 
				state = r1;
			break;
		case r1:
			set_PWM(0.00);
			if (tmpA1 == 0x01)
				state = r1;
			else 
				state = init;
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
	TimerSet(500);
	TimerOn();
	PWM_on();
    /* Insert your solution below */
    while (1) {
	tmpA1 = ~PINA & 0x01;
	
	Tick();
	while (!TimerFlag);
	TimerFlag = 0;

    }
    return 1;
}
