/* Diagnostic method file */
#include <stdio.h>
#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.

#include "diagnostic.h"
#include "timer.h"

void ledToggle(char colour, int delay)
{
	switch (colour)
	{
	case RED:
		PORTD |= D5_RED_D2_RED;
		break;
	
	case GRN:
		PORTD |= D5_GRN_D2_GRN;
		break;
	
	case AMB:
		PORTD |= D5_AMB_D2_AMB;
		break;
	
	default:
		break;
	}
	
	msTimer(delay);
	PORTD &= D5_D2_CLEAR;
}