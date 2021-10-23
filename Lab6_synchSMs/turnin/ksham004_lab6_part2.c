/*      Author: Khuaja Shams
 *  Partner(s) Name: 
 *      Lab Section: 21
 *      Assignment: Lab # 6  Exercise # 2
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 *      Demo Link: https://www.youtube.com/watch?v=Cb-WG9PXMnE
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif


enum B_States { B_SMStart, B_Init, B_Blink2, B_Blink3, B_Win_Press, B_Win_Release } B_State;
unsigned char tmpA, tmpB;

void TickFct_Blink() {
   switch(B_State) { // Transitions
      case B_SMStart:
         B_State = B_Init;
         tmpB = 0x01;
         break;
      case B_Init:
	 if (tmpA == 0x01)
         	B_State = B_Win_Press;
	 else
		 B_State = B_Blink2;
         tmpB = 0x01;
         break;
      case B_Blink2:
         if (tmpA == 0x01)
                B_State = B_Win_Press;
         else
                 B_State = B_Blink3;
         tmpB = 0x02;
         break;
      case B_Blink3:
	 if (tmpA == 0x01) 
		 B_State = B_Win_Press;
	 else
         	B_State = B_Init;
         tmpB = 0x04;
         break;
      case B_Win_Press:
         if (tmpA == 0x01)
                B_State = B_Win_Press;
         else
                 B_State = B_Win_Release;
	 break;
      case B_Win_Release:
         if (!tmpA)
                 B_State = B_Win_Release;
         else
                 B_State = B_Init;
	 break;
      default:
         B_State = B_SMStart;
	 break;
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	tmpA = 0x00;

        TimerSet(300);
        TimerOn();
        B_State = B_SMStart;
        tmpB = 0x00;

    /* Insert your solution below */
    while (1) {
	
	tmpA = ~PINA & 0x01; 
        TickFct_Blink();
        PORTB = tmpB;
        while (!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}
                                
