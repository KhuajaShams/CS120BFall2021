/*	Author: Khuaja Shams
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

enum SM1_STATES { SM1_SMStart, SM1_Init, SM1_PressB1, SM1_ReleaseB1, SM1_PressB0, SM1_ReleaseB0} SM1_STATE;
void Tick_LoHi() {
   switch(SM1_STATE) {
      case SM1_SMStart:
         SM1_STATE = SM1_Init;
         break;
      case SM1_Init:
         if (tmpA) 
            SM1_STATE = SM1_PressB1;
         else if (!tmpA) 
            SM1_STATE = SM1_Init;
         break;
      case SM1_PressB1:
         if (tmpA) 
            SM1_STATE = SM1_PressB1;
         else if (!tmpA) 
            SM1_STATE = SM1_ReleaseB1;
         break;
      case SM1_ReleaseB1:
         if (!tmpA) 
            SM1_STATE = SM1_ReleaseB1;
         else if (tmpA) 
            SM1_STATE = SM1_PressB0;
         break;
      case SM1_PressB0:
         if (tmpA) 
            SM1_STATE = SM1_PressB0;
         else if (!tmpA) 
            SM1_STATE = SM1_ReleaseB0;
         break;
      case SM1_ReleaseB0:
         if (!tmpA) 
            SM1_STATE = SM1_ReleaseB0;
         else if (tmpA) 
            SM1_STATE = SM1_PressB1;
         break;
      default:
         SM1_STATE = SM1_Init;
         break;
   }
   switch(SM1_STATE) {
      case SM1_SMStart:
         break;
      case SM1_Init:
	 tmpB = 0x01;
         break;
      case SM1_PressB1:
         tmpB = 0x02;
         break;
      case SM1_ReleaseB1:
         break;
      case SM1_PressB0:
         tmpB = 0x01;
         break;
      case SM1_ReleaseB0:
         break;
   }
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
    	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    	while (1) {
		tmpA = PINA & 0x01;
		Tick_LoHi();
		PORTB = tmpB;
    	}
    	return 1;
}
