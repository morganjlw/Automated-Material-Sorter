/* PWM Method File */
#include <stdio.h>
#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupt

#include "pwm.h"

void pwmInit(void)
{
		// Configure Timer/Counter(0) Control Register A (TCCR0A).
		// 8-bit timer/counter
		// Mode 3 - Fast PWM, resets at top.
		//TCCR0A = _BV(WGM00) | _BV(WGM01) |_BV(COM0A1);
		TCCR0A |= _BV(WGM00);
		TCCR0A |=_BV(WGM01);
		TCCR0A |=_BV(COM0A1); //resets at top
		
		// Set clock pre-scale to by 8 to get PWM ~500 Hz.
		TCCR0B|=_BV(CS01);
		TCCR0B |=_BV(CS00); // Add to get a total of 64 pre-scale for PWM ~500 Hz. 
		
		// Output Compare A - directly proportionate to duty w.r.t. TCNT0
		// Force to 0 initially.
		OCR0A = 0x00; //set OCRA value to 0. 
		
		// Enable OCOA as output port PB7
		DDRB |= 0xF0;
}

void pwmOut(char duty)
{
	// Output Compare A - directly proportionate to duty w.r.t. TCNT0
	OCR0A = duty;	
}

