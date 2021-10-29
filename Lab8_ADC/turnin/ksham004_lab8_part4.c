/*      Author: Khuaja Shams
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab # 8 Exercise # 4
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 *      Demo Link: https://www.youtube.com/watch?v=lMWEpbgxc34 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
        ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRB = 0xFF; PORTB = 0x00;
        unsigned char tmpB = 0x00;
        unsigned short MAX = 0x138;
        unsigned short MIN = 0x1F;
        unsigned short MID = MAX/2;
        ADC_init();
    /* Insert your solution below */
    while (1) {
        unsigned short a = ADC;
        if (a < MIN)
               tmpB = 0x01;
        else if (a < MAX/5)
                tmpB = 0x03;
        else if (a < MAX/4)
                tmpB = 0x07;
        else if (a < MID)
                tmpB = 0x0F;
        else if (a < MID + MAX/5)
                tmpB = 0x1F;
        else if (a < MID + MAX/4)
                tmpB = 0x3F;
        else if (a < MID + MAX/3)
               tmpB = 0x7F;
        else if (a <= MAX && a > MID + MAX/3) {
                tmpB = 0xFF;
        }

        PORTB = tmpB;
    }
    return 1;
}