/* Stepper Header File */

#ifndef STEPPER_H_ /* Include guard */

//Defines
#define STEPPER_H_ 

/* Global Variables */
volatile int stepperValue;
volatile int stepperPosition;
volatile int stepperState;
volatile int stepperDirection;

/* Function Prototypes */
void stepperInit(void);
void stepperFindHome(void);
void stepperRotate(char dir, int count);
void stepperStateChange(int destination);

// Stepper accel test functions...
void stepperRotateCCW90(void);
void stepperRotateCCW180(void);

void stepperRotateCW90(void);
void stepperRotateCW180(void);

/* Stepper motor controller connection definitions */

/* 90 fast turn definitions */
#define AccelSteps 6 // acceleration steps
#define maxAccel 5 // max acceleration

#define DeccelSteps 6 // decceleration steps
#define deccelStart 44 // deceleration start step

//	E1	L1	L2	E2	L3	L4
//	||	||	||	||	||	||
//	PA0	PA1	PA2	PA3	PA3	PA4

// Stepper enable pins
#define E1 0x01 // PA0
#define E2 0x08 // PA3

// Stepper coils pins
#define L1 0x02 // PA1
#define L2 0x04 // PA2
#define L3 0x10 // PA4
#define L4 0x20 // PA5

/* Stepper State definitions */
#define BLACK 1
#define STEEL 2
#define WHITE 3
#define ALUMINUM 4
#define UNKNOWN 5
#define DEFAULT 6

/* Stepper turn definitions */

#define DEG30 17
#define DEG60 33
#define DEG90 50
#define DEG180 100
#define DEG360 200

/* Stepper control definitions */

#define CW 0x01 // clock wise case 
#define CCW 0x02 // counter-clock wise case 

#endif //STEPPER_H_