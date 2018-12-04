/* Timer Method File */

#include <stdio.h>
#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupt
#include "diagnostic.h"
#include "timer.h"

void timerInit(void)
{
	// Timer Configurations
	TCCR1B |= _BV(CS10); // 1 << (CS10 = 1) Select internally scaled clock source (fclk = 1 MHz).
	TCCR1B |=_BV(WGM12); // 1 << (WGM12 = 3) Select CTC mode.
	
	//OCR1A = TIMER_MS_1MHZ; // Set timer maximum value before reset.
	//OCR1A = TIMER_MS_8MHZ;
	
	TCNT1 = 0x0000; // Force timer register to zero.
	
	// Setting bit 1 of the Timer Interrupt Mask Register to enable Output Compare A Match Interrupt.
	//TIMSK1 |= _BV(OCIE1A);
}

void msTimer(int ms)
{
	int i = 0; // Counter variable
	
	OCR1A = TIMER_MS_8MHZ; // Output compare
	
	TIFR1 |= _BV(OCF1A); // start timer
	
	while (i < ms)
	{
		if ((TIFR1 & 0x02) == 0x02)
		{
			TIFR1 |=_BV(OCF1A);
			i++;
		}
	}
}

void usTimer(int us)
{
	int i = 0; // counter variable
	
	OCR1A = TIMER_US_8MHZ; // 

	TIFR1 |= _BV(OCF1A); // start timer
	
	while (i < us)
	{
		if ((TIFR1 & 0x02) == 0x02)
		{
			TIFR1 |=_BV(OCF1A);
			i++;
		}
	}
}
