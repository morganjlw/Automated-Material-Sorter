/* PWM Header File */
#ifndef PWM_H_ /* Include guard */

// Guard Definition
#define PWM_H_

// Duty definitions - 10% increments
#define DUTY0 0x00 //0% -> 0/255
#define DUTY10 0x1A // 10% -> 26/255 *(rounded up)
#define DUTY20 0x33 // 20% -> 51/255
#define DUTY25 0x40 // 25% -> 64/255
#define DUTY30 0x4D // 30% -> 77/255 *
#define DUTY40 0x66 // 40% -> 102/255
#define DUTY50 0x80 // 50% -> 128/255 *
#define DUTY60 0x7B // 60% -> 153/255 
#define DUTY70 0xB3 // 70% -> 179/255*
#define DUTY80 0xCC // 80% -> 204/255
#define DUTY90 0xE6 // 90% -> 230/255*
#define DUTY100 0xFF // 100% -> 255/255

#define BELT_DUTY DUTY40  

// Prototypes
void pwmInit(void);
void pwmOut(char duty);

#endif //PWM_H_
