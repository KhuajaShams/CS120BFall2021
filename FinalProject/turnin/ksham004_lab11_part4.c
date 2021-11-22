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
#endif


typedef struct task {
	unsigned char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct) (int); 
} task;

unsigned char text[1] = " ";

unsigned char GetBit(unsigned char port, unsigned char number) 
{
	return ( port & (0x01 << number) );
}

unsigned char GetKeypadKey() {
	PORTC = 0xEF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return('1'); }
        if(GetBit(PINC, 1) == 0) { return('4'); }
        if(GetBit(PINC, 2) == 0) { return('7'); }
        if(GetBit(PINC, 3) == 0) { return('*'); }
	
	PORTC = 0xDF;
	asm("nop"); 
	if(GetBit(PINC, 0) == 0) { return('2'); }
        if(GetBit(PINC, 1) == 0) { return('5'); }
        if(GetBit(PINC, 2) == 0) { return('8'); }
        if(GetBit(PINC, 3) == 0) { return('0'); }

	PORTC = 0xBF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return('3'); }
        if(GetBit(PINC, 1) == 0) { return('6'); }
        if(GetBit(PINC, 2) == 0) { return('9'); }
        if(GetBit(PINC, 3) == 0) { return('#'); }

        PORTC = 0x7F;
        asm("nop");
        if(GetBit(PINC, 0) == 0) { return('A'); }
        if(GetBit(PINC, 1) == 0) { return('B'); }
        if(GetBit(PINC, 2) == 0) { return('C'); }
        if(GetBit(PINC, 3) == 0) { return('D'); }

	return('\0');
}

enum States {init};

int KeypadSMTick(int state) {
	switch (state)
	     case init:
		state = init; 
		unsigned char x = GetKeypadKey();
		switch (x) {
			case '\0': text[0] = '\0';  break;
			case '1': text[0] = '1'; break;
			case '2': text[0] = '2'; break;
			case '3': text[0] = '3'; break;
			case '4': text[0] = '4'; break;
			case '5': text[0] = '5'; break;
               	 	case '6': text[0] = '6'; break;
          	        case '7': text[0] = '7'; break;
          	        case '8': text[0] = '8'; break;
        	       	case '9': text[0] = '9'; break;
			case 'A': text[0] = 'A'; break;
                	case 'B': text[0] = 'B'; break;
                	case 'C': text[0] = 'C'; break;
                	case 'D': text[0] = 'D'; break;
                	case '*': text[0] = '*'; break;
			case '0': text[0] = '0'; break;
                	case '#': text[0] = '#'; break;
                	default:  break;
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
	task1.TickFct = &KeypadSMTick;


	TimerSet(300);
	TimerOn();
	LCD_init();
	unsigned char txt[] = "Congratulations!";
	LCD_DisplayString(1, txt);
	unsigned short counter = 0;
	unsigned short i;

    while (1) {	   
	for (i = 0; i < numTasks; i++) {
		if (tasks[i]->elapsedTime == tasks[i]->period) {
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 300;
	}

	if (text[0] != '\0') {
		LCD_Cursor(counter); 
		LCD_WriteData(text[0]);	
		counter++;
    	}
    	if (counter > 16) 
		counter = 0;

	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
