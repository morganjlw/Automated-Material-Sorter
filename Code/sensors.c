/* Sensors Method File */
#include <stdio.h>
#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupt
//#include "adc.h"
#include "sensors.h"
#include "dcDrive.h"
#include "pwm.h"
#include "adc.h"
#include "timer.h"
#include "diagnostic.h"
#include "control.h"
#include "stepper.h"
#include "queue.h"
#include "fsm.h"

void sensorsInit(void)
{
	// Configure external interrupts w/ correct edge activations
	
	// Enable INT[0-3]
	//EIMSK |= ( _BV(INT0) | _BV(INT1) | _BV(INT2) | _BV(INT3) );
	
	//EIMSK |= ( _BV(INT0) | _BV(INT1) | _BV(INT3) );
	
	EIMSK |= ( _BV(INT0) | _BV(INT1) ); // disables IN and disable OI
	
	EICRA |= ( _BV(ISC01) ); // EX configure falling edge trigger 
	
	EICRA |= ( _BV(ISC11) | _BV(ISC10) ); // OR configure rising edge trigger
	
	//EICRA |= ( _BV(ISC21) ); // OI falling edge trigger
	
	//EICRA |= ( _BV(ISC31) ); // IN falling edge trigger
}


/* Sensor ISRs */

// EX ISR
ISR(INT0_vect)
{ 
	dcDrive(BRK, 0); // Stop conveyor belt
	stepperStateChange(front(&q)); // Move stepper

	// Sorting statistics update
	switch(front(&q))
	{
		case ALUMINUM :
			AL_count++;
			break;
		
		case BLACK :
			BL_count++;
			break;
		
		case WHITE :
			WH_count++;
			break;
		
		case STEEL :
			ST_count++;
			break;
		
		default :
			break;		
	}
	
	pop(&q); // Remove sorted item from queue
	dcDrive(DC_CW, BELT_DUTY); // Put item into bucket
	STATE = BUCKET; 
}

// OR ISR
ISR(INT1_vect)
{
	//set to max value 
	ADC_result = 0xFFFF;

	//start conversion
	ADCSRA |= _BV(ADSC);
}

/*
// OI ISR
ISR(INT2_vect)
{
	//PORTC |= 0x01; // Diagnostic
	//dcDrive(BRK, 0);
	//ledToggle(RED, 500);
}

// IN ISR
ISR(INT3_vect)
{
	// Do nothing
}
*/