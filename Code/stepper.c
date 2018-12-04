/* DC Stepper motor control method file */

#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupts.

#include "stepper.h"
#include "timer.h"

//	E1	L1	L2	E2	L3	L4
//	||	||	||	||	||	||
//	PA0	PA1	PA2	PA3	PA4	PA5
//Stepper sequence. switch bits
//	1	1	0	1	0	1	
//	1	0	1	1	0	1	
//	1	0	1	1	1	0	
//	1	1	0	1	1	0	
//Single coil, this one works 
//volatile char stepperSequence [4] = {0x03, 0x18, 0x05, 0x28}; // refer to stepper table

// Full stepping, both coils, more torque
volatile char stepperSequence [4] = {0b011011, 0b011101, 0b101101, 0b101011};

// Trapezoidal stepper acceleration and deceleration profiles...	
volatile int stepperAccel [20] = {20, 19, 18, 16, 15, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 9, 9, 9, 9}; 
volatile int stepperDeccel [20] = {9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 17, 18, 19, 20, 20};
//volatile int stepperAccelDecell [50] = {20, 19, 18, 17, 16, 15, 14, 13, 12, };

// Max Delay (ms) = 4.5 , k= 2.5
volatile int stepperCruve90 [50] = { 9000, 8998, 8970, 8659, 6750, 4841, 4530, 4502, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4502, 4530, 4841, 6750, 8659, 8970, 8998, 9000, 9000 };

// Max Delay (ms) = 4.5 , k= 2.5
volatile int stepperCruve180 [100] = { 9000, 9000, 9000, 9000, 9000, 9000, 8998, 8970, 8659, 6750, 4841, 4530, 4502, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500,4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500,4500,4500,4500, 4500, 4502, 4530, 4841, 6750, 8659, 8970, 8998, 9000, 9000, 9000, 9000, 9000, 9000, 9000};

/*
// S-Curve stepper acceleration and deceleration profiles...
volatile int stepperAcccel90 [10] = {};
volatile int stepperDecel90 [10] = {};
volatile int stepperAccel180 [20] = {};
volatile int stepperDecel180 [20] = {}; 
*/
void stepperInit(void)
{
	// Configure PA[5:0] as outputs as per stepper.h
	// Configure PA[7:6] as inputs 
	// PA6 => HE sensor, PA7 => TBD
	DDRA |= 0x3F; 
}

void stepperFindHome(void)
{
	while ((PINA & 0x80) == 0x80)
	{
		PORTA = stepperSequence[stepperValue];
		
		if (stepperValue == 3)
		{
			stepperValue = 0;
		}
		else
		{
			stepperValue += 1;
		}
		
		msTimer(20); // 20 ms delay
	}
	PORTA = stepperSequence[stepperValue];
	stepperPosition = 0;
	stepperState = BLACK;
}

void stepperRotate(char dir, int count)
{
	int i = 0;
	
	switch(dir)
	{
		case CW:
		
			// clockwise by count
			while (i < count)
			{
				PORTA = stepperSequence[stepperValue];
				
				if (stepperValue == 3)
				{
					stepperValue = 0;
				}
				else
				{
					stepperValue += 1;
				}		
				
				msTimer(20);
				i++;
			}
			
			break;
			
		case CCW:
			// counter clockwise by count
			while (i < count)
			{
				PORTA = stepperSequence[stepperValue];
				if (stepperValue == 0)
				{
					stepperValue = 3;
				}
				else
				{
					stepperValue -= 1;
				}
				
				msTimer(20); //20 ms delay
				i++;
			}
			
			//stepperPosition = (stepperPosition - count) % 200;			
			break;
			
		default:
			// dir input error
			break;
	}
	
}

void stepperStateChange(int destination)
{	
	int cmp = destination - stepperState;
	
	if (cmp != 0) // Is stepper in same state? May not require this check w/ supplemental FSM logic...
	{
		if ( (cmp == -1) || (cmp == 3) ) // Clockwise rotate logic
		{
			//stepperRotate(CW, DEG90);
			stepperRotateCW90();
			stepperState = destination;
			stepperDirection = CW;
			return;
		}
		
		if ( (cmp == 1) || (cmp == -3) ) // Counter clockwise rotate logic
		{
			//stepperRotate(CCW, DEG90);
			stepperRotateCCW90();
			stepperState = destination;
			stepperDirection = CCW;
			return;
		}
		
		if ( (cmp == 2) || (cmp == -2) )
		{
			if (stepperDirection == CW)
			{
				stepperRotateCW180();
			}
			else
			{
				stepperRotateCCW180();
			}
			//stepperRotateCW180();
			stepperState = destination;
			return;
		}
		
	}
	
	stepperState = destination;
}

void stepperRotateCCW90(void)
{
	int i = 0; //turn counter
	
	while (i < DEG90)
	{
		
		PORTA = stepperSequence[stepperValue];
		if (stepperValue == 0)
		{
			stepperValue = 3;
		}
		else
		{
			stepperValue -= 1;
		}
		usTimer(stepperCruve90[i]);	
		i++;
	}
}

void stepperRotateCCW180(void)
{
	int i = 0;
	//int j = 0;
	//int k = 0;
	//int delay;
	
	while (i < DEG180)
	{
		PORTA = stepperSequence[stepperValue];
		if (stepperValue == 0)
		{
			stepperValue = 3;
		}
		else
		{
			stepperValue -= 1;
		}
		usTimer(stepperCruve180[i]);
		i++;
	}
}

void stepperRotateCW90(void)
{
	int i = 0;

	while (i < DEG90)
	{
		PORTA = stepperSequence[stepperValue];
		
		if (stepperValue == 3)
		{
			stepperValue = 0;
		}
		else
		{
			stepperValue += 1;
		}
		usTimer(stepperCruve90[i]);		
		i++;
	}
	
	
}

void stepperRotateCW180(void)
{
	int i = 0;
	
	while (i < DEG180)
	{
		PORTA = stepperSequence[stepperValue];
		
		if (stepperValue == 3)
		{
			stepperValue = 0;
		}
		else
		{
			stepperValue += 1;
		}
		usTimer(stepperCruve180[i]);
		i++;
	}
}