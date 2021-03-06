#include <stdio.h>
#ifndef F_CPU
#define F_CPU 8000000 // The atmega1284 has an 8MHz clock
#endif
#include <avr/sleep.h>
#include "include/simavr/avr/avr_mcu_section.h"

AVR_MCU(F_CPU,"atmega1284");
AVR_MCU_VCD_FILE("build/results/Lab2_introToAVR_trace.vcd",1000);

const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
	{ AVR_MCU_VCD_SYMBOL("PORTC"), .what = (void*)&PORTC, } ,
};
//FILE mystdout = FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);

