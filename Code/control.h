/* Control Header File */

#ifndef CONTROL_H_ /* Include guard */

//Defines
#define CONTROL_H_

#define RAMP_TIMER_3S 0x5DC0 // 24,000

// Prototypes
void controlInit(void);
void rampTimer(void);

volatile unsigned int pauseFlag; 

#endif //CONTROL_H_