/* ADC Method File */
#include <stdio.h>
#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupt
#include "adc.h"
#include "timer.h"
#include "diagnostic.h"
#include "lcd.h"
#include "stepper.h"
#include "queue.h"
#include "fsm.h"

void adcInit(void)
{
	ADCSRA |= _BV(ADEN);// enable adc
	ADCSRA |= _BV(ADIE);// enable interrupt of adc
	//ADCSRA |= (_BV(ADPS2) | _BV(ADPS0));// adc scaler division factor of 32
	
	//ADCSRA |=  (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0)); // adc scaler division factor of 128
	
	ADMUX |= _BV(REFS0);
	ADMUX |= _BV(MUX0);
	
	// Initialize sorted materials
	BL_count = 0;
	WH_count = 0;
	ST_count = 0;
	AL_count = 0;
}

/*		ADC ISR		*/
// ISR when ADC conversion is complete...
ISR(ADC_vect)
{
	// When conversion done read ADC (10-bit)
		
	//check for minimum value
	if (ADC < ADC_result)
	{
		ADC_result = ADC;
	}	
	// Check if OR is high (piece is still in sensor)
	if ((PIND&0x02)== 0x02)
	{
		ADCSRA |= _BV(ADSC);	 
	}
	// Piece is out of sensor, begin classification...
	else {
		if (ADC_result < ALUMINUM_MAX_ADC) {
			Object_result = ALUMINUM;
			} 
		else if (ADC_result < STEEL_MAX_ADC) {
			Object_result = STEEL;
			} 
		else if (ADC_result < WHITE_MAX_ADC) {
			Object_result = WHITE;
			}
		else if (ADC_result < BLACK_MAX_ADC) {
			Object_result = BLACK;
		}
		else {
			Object_result= UNKNOWN;
		}
		//push result to queue 
		push(&q, Object_result);
		STATE = REFLETIVE;
	}
	
}