/* Timer Header Files */
#ifndef TIMER_H_ /* Include guard */

//Defines
#define TIMER_H_

// OCR1A definitions
// MS 
#define TIMER_MS_1MHZ 0x03E8 // 1000 counts => 1 ms @ 1 MHz
#define TIMER_MS_8MHZ 0x1F40 // 8000 counts => 1 ms @ 8 MHz
// US
#define TIMER_US_1MHZ 0x0001 // 1 count => 1 us @ 1 MHz
#define TIMER_US_8MHZ 0x0008 // 8 count => 1 us @ 8 MHz

// Prototypes
void timerInit(void);
void msTimer(int ms);
void usTimer(int us);

#endif //TIMER_H_
