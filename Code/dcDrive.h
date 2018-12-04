/* dcDrive.h */
/* DC Drive Header File */


#ifndef DCDRIVE_H_ /* Include guard */

// Guard Definition
#define DCDRIVE_H_

// Prototypes
void dcDriveInit(void);
void dcDrive(char cmd, char speed);

// DC Drive command definitions
// INA -> PB3, INB -> PB2, ENA -> PB1, ENB -> PB0

/* DC Drive wiring */
// n/c = not connected
//	IA	EA	EB	IB	PWM	CS
//	||	||	||	||	||	||	
//	PB3	PB1	PB0	PB2	PB7	n/c

#define DC_CW 0x04 //INA(L), INB(L), ENA(L), and ENB(L)
#define DC_CCW 0x08 //INA(H), INB(L), ENA(L), and ENB(L)
#define BRK 0x00 //INA(L), INB(L), ENA(L), and ENB(L)

#endif //DCDRIVE_H_
