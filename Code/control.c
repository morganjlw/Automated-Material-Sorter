/* Control method file */

#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupts.

#include "control.h"
#include "diagnostic.h"
#include "timer.h"
#include "lcd.h"
#include "dcDrive.h"
#include "pwm.h"
#include "queue.h"
#include "fsm.h"

void controlInit(void)
{
	//Configure System Pause to PE4 and System Ramp Down to PE5 
	// Configured as a pull-ups
	// Configure external interrupts w/ correct edge triggers
	
	EIMSK |= ( _BV(INT4) | _BV(INT5) ); // Enable INT[5-4]
	EICRB |= ( _BV(ISC41) |  _BV(ISC51) ); // Configure buttons for falling edge trigger
	
	DDRB &= 0xCF;
	pauseFlag = 0;
}

void rampTimer(void)
{
	// Configure ramp down timer interrupt
	TCCR3B |= ( _BV(WGM32) | _BV(CS30) | _BV(CS32) ); // CTC mode, timer clock prescaled by 1024
	OCR3A = RAMP_TIMER_3S; // 24,000 ticks @ 7.8125 KHz clock = 3.072 seconds
	TCNT3 = 0x0000; // Initialize count register to zero.
	//TIMSK3 |= _BV(TOIE3); // Enables timer interrupt
	TIMSK3 |= _BV(OCIE3A);
	
	TIFR3 |= _BV(OCF3A); // Start timer
}

// System Pause Button (Leftmost)
ISR(INT4_vect)
{
	dcDrive(BRK, 0);
	//toggle pause flag
	//pause 
	if (pauseFlag==0)
	{
		pauseFlag = 1;
		STATE = PAUSE;
	} else {
		pauseFlag = 0;
		dcDrive(DC_CW,BELT_DUTY);
		STATE = POLLING;
	}
	//de-bounce switch 	
	msTimer(20);
}

// System Ramp-down Button (Rightmost)
ISR(INT5_vect)
{
	//start the ramp down timer...
	rampTimer();
	
	// Go back to polling
	STATE = POLLING;	
}

// Ramp down timer ISR
ISR(TIMER3_COMPA_vect)
{
	if(queueSize(&q)!=0)
	{
		rampTimer(); // Restart 3s ramp timer
	}
	else
	{
		dcDrive(BRK,0); // Turn off belt
		STATE = RAMPDOWN;
	}
}
