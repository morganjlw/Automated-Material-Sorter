/* PORTD On-Board LED Mapping */

// D5 AND D2 DIAGNOSTIC COLOR DEFINITIONS
// PORTD register contents to achieve desired color.
// ex. PORTD |= D5_OFF_D2_OFF
// ex. PORTD &= D5_D2_CLEAR

#ifndef DIAGNOSTIC_H_   /* Include guard */
#define DIAGNOSTIC_H_

// Diagnostic Prototype
void ledToggle(char colour, int delay);

// Diagnostic function definitions
#define RED 0
#define GRN 1
#define AMB 2

// Test Timer
#define TIMER_TEST 1000

//D5 & D2 Clears
#define D5_D2_CLEAR 0x0F
#define D5_CLEAR 0x3F
#define D2_CLEAR 0xCF

//D5 OFF & D2 ON
#define D5_OFF_D2_RED 0x10
#define D5_OFF_D2_GRN 0x20
#define D5_OFF_D2_AMB 0x30

//D5 ON & D2 OFF
#define D5_GRN_D2_OFF 0x40
#define D5_RED_D2_OFF 0x80
#define D5_AMB_D2_OFF 0xC0

//D5 ON & D2 RED
#define D5_GRN_D2_RED 0x50
#define D5_RED_D2_RED 0x90
#define D5_AMB_D2_RED 0xD0

//D5 ON & D2 GRN
#define D5_GRN_D2_GRN 0x60
#define D5_RED_D2_GRN 0xA0
#define D5_AMB_D2_GRN 0xE0

//D5 ON & D2 AMB
#define D5_GRN_D2_AMB 0x70
#define D5_RED_D2_AMB 0xB0
#define D5_AMB_D2_AMB 0xF0

#endif //DIAGNOSTIC_H_