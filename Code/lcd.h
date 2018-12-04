/* LCD Header File */

#ifndef LCD_H_ /* Include guard */

//Defines
#define LCD_H_

/* LCD Wiring */ 
//	RS	RW	E	DB0	DB1	DB2	DB3	RS
//	||	||	||	||	||	||	||
//	PC4	PC5	PC6	PC0	PC1	PC2	PC3

// Character Definitions
// characters are just ASCII codes

/******** Start of  old library code **********/

#define LCD_DATA_PORT 	PORT(LCD_DATA)
#define LCD_E_PORT 		PORT(LCD_E)
#define LCD_RS_PORT 	PORT(LCD_RS)
#define LCD_RW_PORT 	PORT(LCD_RW)

#define LCD_DATA_DDR 	DDR(LCD_DATA)
#define LCD_E_DDR 		DDR(LCD_E)
#define LCD_RS_DDR 		DDR(LCD_RS)
#define LCD_RW_DDR 		DDR(LCD_RW)

#define LCD_DATA_PIN	PIN(LCD_DATA)

#define SET_E() (LCD_E_PORT|=(1<<LCD_E_POS))
#define SET_RS() (LCD_RS_PORT|=(1<<LCD_RS_POS))
#define SET_RW() (LCD_RW_PORT|=(1<<LCD_RW_POS))

#define CLEAR_E() (LCD_E_PORT&=(~(1<<LCD_E_POS)))
#define CLEAR_RS() (LCD_RS_PORT&=(~(1<<LCD_RS_POS)))
#define CLEAR_RW() (LCD_RW_PORT&=(~(1<<LCD_RW_POS)))

// start of "myutils.h"

#define _CONCAT(a,b) a##b
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)

//end of "myutils.h"

/************************************************
	LCD CONNECTIONS
   Uses PORTD.7 - Strobe, PORT.6 - RS, PORT.5 - RW, DataNibble PORTC.4 - PORTC.7
   Code Modified to use PORTC Only
   * LCD Wiring */
   //	RS	RW	E	DB4	DB5	DB6	DB7
   //	||	||	||	||	||	||	||
   //	PC6	PC5	PC7	PC0	PC1	PC2	PC3

   
/*************************************************/

#define LCD_DATA C	//Port PC0-PC3 are connected to D4-D7

#define LCD_E C 		//Enable OR strobe signal
#define LCD_E_POS	PC7	//Position of enable in above port

#define LCD_RS C	
#define LCD_RS_POS 	PC6

#define LCD_RW C
#define LCD_RW_POS 	PC5


//************************************************

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010



/***************************************************
			F U N C T I O N S
****************************************************/




void LCDWriteObjectTypeXY(int x, int y, unsigned int object);

void InitLCD(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,unsigned int field_length);
void LCDGotoXY(uint8_t x,uint8_t y);

void testLCD(void);


//Low level
void LCDByte(uint8_t c,uint8_t isdata);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();

/***************************************************
			F U N C T I O N S     E N D
****************************************************/

/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome() LCDCmd(0b00000010);

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}
/***************************************************/

#endif //LCD_H_