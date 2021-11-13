/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 11 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://www.youtube.com/watch?v=OUtk8RnuxF8 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h" 
#include "io.h"
#endif


typedef struct task {
	unsigned char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct) (int); 
} task;

unsigned char text[54] = "CS120B is Legend... wait for it DARY!                 ";
unsigned char displayed_text[16] = "                ";

enum States {init,  msg};
unsigned char k = 0;

int LEDSMTick(int state) {
	switch (state) {
		case init:
			state = msg;
			break;
		case msg:
		        if (k < 54) {
				for (unsigned char j = 0; j <= k; j++) {
					if (j > 15) 
						continue; 
					displayed_text[15-j] = text[k-j];	
				}
				k++;
				state = msg;
			}
			else {
				k = 0;
				state = init;
			}
			LCD_DisplayString(1, displayed_text);
			break;
		default:
			state = init;
			break;
	}

	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	const char start = -1;

	task1.state = start;
	task1.period = 300;
	task1.elapsedTime = task1.period;
	task1.TickFct = &LEDSMTick;


	TimerSet(300);
	TimerOn();
	LCD_init();

	unsigned short i;
    while (1) {
	for (i = 0; i < numTasks; i++) {
		if (tasks[i]->elapsedTime == tasks[i]->period) {
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 300;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
