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
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	

	TimerSet(300);
	TimerOn();
	LCD_init();
	ADC_init();
	unsigned char text[10] = "    ";
	
	unsigned char vert, horz, sel, tmpD = 0x00;
	
    while (1) {
	tmpD = 0x00;
	horz = ~PINC & 0x01;
	vert = ~PINC & 0x02;
	sel = ~PINC & 0x04;
	
	if (horz == 0x01)
		tmpD = tmpD | 0x01;
	if (vert == 0x02)
		tmpD = tmpD | 0x02;
	if (sel == 0x04) 
		tmpD = tmpD | 0x04;
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
