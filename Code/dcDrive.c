/* PWM Function File */
#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupt
#include "dcDrive.h"
#include "pwm.h"

void dcDriveInit(void)
{
	// Initialize GPIO PORTD to output PB[3:0]
	DDRB |= 0x0F;  
}

void dcDrive(char cmd, char speed)
{
	switch (cmd)
	{
	//INA(H), INB(H), ENA(H), and ENB(H)
	case DC_CW: 
		PORTB = DC_CW; // CW Port D config
		pwmOut(speed); // CW PWM config 
		break;
		
	//INA(H), INB(L), ENA(H), and ENB(H)
	case DC_CCW:
		PORTB = DC_CCW; // CCW Port D config
		pwmOut(speed); // CCW PWM config
		break;
		
	//INA(L), INB(H), ENA(H), and ENB(H)
	case BRK:
		PORTB = BRK; // CW_BRK Port D config
		break;
		
	default:		
		break;
	}
		
}

