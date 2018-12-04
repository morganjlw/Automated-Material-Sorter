/* Sensors Header File */

#ifndef SENSORS_H_ /* Include guard */

// Defines
#define SENSORS_H_

//Prototypes
void sensorsInit(void);

volatile unsigned int EX_flag;

/* Sensor wiring */
//	HE	EX	RL	OR	IN	OI
//	||	||	||	||	||	||
//	PA7	PD0	PF0	PD1	PD3	PD2


// Conveyor Sensor array definitions
#define EX 0x00 // PD0 => Active falling edge
#define OR 0x01 // PD1 => Active rising edge
#define OI 0x02 // PD2 => Active falling edge
#define IN 0x03 // PD3 => Active falling edge

// Reflective analog optical sensor definition
#define RL 0x00 // PF0


// Hall Effect Sensor definition
#define HE 0x80 // PA7



#endif //SENSORS_H_