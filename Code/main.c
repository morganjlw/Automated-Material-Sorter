/*
########################################################################
# MILESTONE : 5
# LAB : Final Project
# PROGRAM : MECH 458
# PROJECT : Automated Sorting.
# GROUP : 3
# NAME 1 : Morgan Williams, V00804732
# NAME 2 : Dalton Braun, V00837951
# DESC : Full auto sorting.
# DATE : 18/11/2018
# REV : 1
########################################################################
*/

// C and AVR Headers
#include <stdio.h>
#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.
#include <avr/interrupt.h> // Interrupt

// Library Files
#include "diagnostic.h" // D2 and D5 LED mapping and functionality.
#include "stepper.h" // Stepper motor control and initialization.
#include "timer.h" // Delay timer control and initialization.
#include "pwm.h" // PWM output initialization and control.
#include "dcDrive.h" // DC Drive initialization and control.
#include "adc.h" // ADC initialization, control, and ISRs.
#include "sensors.h" // Sensor initialization, control, and ISRs. 
#include "lcd.h" // LCD driver library.
#include "control.h" // Control library. 
#include "queue.h" // Queue functions library.
#include "fsm.h"

// Function Prototypes
void systemInit(void);
void gpioInit(void);

// Demo Functions
void testCWStateTrans(void);
void testCCWStateTrans(void);
void testHFStateTrans(void); 

void testLCD(void);

int main (void)
{
	// Set clk frequency to 8 MHz... 
	CLKPR = 0x80;
	CLKPR = 0x00;
			
	cli(); // Clear global interrupts...
	systemInit(); // Initialize components...
	sei(); // Enable global interrupts...
	
	LCDClear();
	LCDWriteStringXY(7,0,"IN");
	LCDWriteStringXY(6,1,"MAIN");
	/*
	0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
	              I N
	            M A I N
	*/
	
	queueInit(&q); // Initialize Queue
	
	dcDrive(DC_CW, BELT_DUTY); // Start Motor
	
	STATE = POLLING;
		
	while(1){
			
		switch(STATE){
			case(POLLING)	:
				//STATE = POLLING;
				//stepperStateChange(front(&q)); // Move stepper
				break;
				
			case(REFLETIVE)	:
				STATE = POLLING;
				break;
				
			case(BUCKET)	:
				STATE = POLLING;
				break;
								
			case(PAUSE)	:
				
				// While system is paused and awaiting another button push...
				if ((pauseFlag==1))
				{
					
					// Diagnostic Display...
					LCDClear();
					LCDWriteStringXY(0,1,"Size: ");
					LCDWriteIntXY(6,1,queueSize(&q),2);
					LCDWriteIntXY(10,1,ADC_result,4);
					LCDWriteStringXY(0,0,"F:");
					LCDWriteObjectTypeXY(3,0,front(&q));
					LCDWriteStringXY(7,0,"O: ");
					LCDWriteObjectTypeXY(10,0,Object_result);
					
					/*
					// Display sorting statistics
					LCDClear();
					
					//Y  X  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 
					//0     B : X X _ W : X X _ S : X X
					//1     A : X X _ B E L T : X X
					
					LCDWriteStringXY(0,0,"B:");
					LCDWriteIntXY(2,0,BL_count,2);
					
					LCDWriteStringXY(4,0," W:");
					LCDWriteIntXY(7,0,WH_count,2);
					
					LCDWriteStringXY(9,0," S:");
					LCDWriteIntXY(12,0,ST_count,2);
					
					LCDWriteStringXY(0,1,"A:");
					LCDWriteIntXY(2,1,AL_count,2);
					
					LCDWriteStringXY(4,1," BELT:");
					LCDWriteIntXY(10,1,queueSize(&q),2);
					*/
				}  
				
				while(pauseFlag==1);//do nothing until flag toggle back to 0
				
				break;
			
			case(RAMPDOWN) : 
				
				cli(); // Disable global interrupts...
				
				// Display Sort statistics
				// B:XX_W:XX_S:XX
				// A:XX_C:XX 
				LCDClear();
				LCDWriteStringXY(0,0,"B:");
				LCDWriteIntXY(2,0,BL_count,2);
				
				LCDWriteStringXY(4,0," W:");
				LCDWriteIntXY(7,0,WH_count,2);
				
				LCDWriteStringXY(9,0," S:");
				LCDWriteIntXY(12,0,ST_count,2);
					
				LCDWriteStringXY(0,1,"A:");
				LCDWriteIntXY(2,1,AL_count,2);
					
				LCDWriteStringXY(4,1," BELT:");
				LCDWriteIntXY(10,1,queueSize(&q),2);
								
				STATE = POLLING;
				break;	
				
			default:
				STATE = POLLING;
		}
	}
			
	return 0;
}

void systemInit(void)
{
	timerInit();
	stepperInit();
	pwmInit();
	adcInit();
	dcDriveInit();
	sensorsInit();
	controlInit();
	
	//Initialize LCD module
	InitLCD(LS_BLINK|LS_ULINE);
	//Clear the screen
	LCDClear();
	
	gpioInit(); // if required... 
	
	// Find Home BLACK state...
	LCDWriteString("Looking...");
	stepperFindHome();
	LCDClear();
	LCDWriteString("Found home!");
}

void gpioInit(void)
{	
	// Configure additional GPIO if required...
	DDRD |= 0xF0; // On board LEDs
	DDRC = 0xFF; // Data output GPIO
}

void testHFStateTrans(void)
{
	// Black and White
	//LCDClear();
	stepperStateChange(BLACK);
	//LCDWriteObjectTypeXY(0,0,BLACK);
	//ledToggle(AMB, 500);
	stepperStateChange(WHITE);
	//LCDWriteObjectTypeXY(0,0,WHITE);
	//ledToggle(RED, 500);
	stepperStateChange(BLACK);
	//LCDWriteObjectTypeXY(0,0,BLACK);
	
	// Aluminum and Steel
	//ledToggle(GRN, 500);
	stepperStateChange(ALUMINUM);
	//LCDWriteObjectTypeXY(0,0,ALUMINUM);
	//ledToggle(AMB, 500);
	stepperStateChange(STEEL);
	//LCDWriteObjectTypeXY(0,0,STEEL);
	//ledToggle(AMB, 500);
	stepperStateChange(ALUMINUM);
	//LCDWriteObjectTypeXY(0,0,ALUMINUM);
	stepperStateChange(BLACK);
}

