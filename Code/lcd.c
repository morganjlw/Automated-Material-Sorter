/* LCD method file */

#include <stdlib.h> // General purpose standard library of C programming language.
#include <avr/io.h>// I/O port header.

// Custom header
#include "lcd.h"
#include "stepper.h"
#include "timer.h"

void testLCD(void)
{
	//test LDC display
	
	//setup display 4 bit mode
	
	//clear display
	
	//display "hello world"
	//the display just uses ACSII
	//need to send upper and lower bit in 4-bit mode
	unsigned char i;

	//Initialize LCD module
	//InitLCD(LS_BLINK|LS_ULINE);

	//Clear the screen
	//LCDClear();

	//Simple string printing
	LCDWriteString("Congrats ");
	
	//A string on line 2
	LCDWriteStringXY(0,1,"Loading ");

	//Print some numbers
	for (i=0;i<99;i+=1)
	{
		LCDWriteIntXY(9,1,i,3);
		LCDWriteStringXY(12,1,"%");
		//_delay_loop_2(0);
		//_delay_loop_2(0);
		//_delay_loop_2(0);
		//_delay_loop_2(0);

		//mTimer(1000);
		msTimer(1000);
	}

	//Clear the screen
	LCDClear();

	//Some more text

	LCDWriteString("Hello world");
	LCDWriteStringXY(0,1,"By Pat");		// <--- Write ur NAME HERE !!!!!!!!!!!

	//Wait ~ 25 secs
	//for(i=0;i<100;i++) _delay_loop_2(0);
	//mTimer (25000);
	msTimer(25000);

	//Some More ......
	LCDClear();
	LCDWriteString("    eXtreme");
	LCDWriteStringXY(0,1,"  Electronics");
	
	
}


void LCDWriteObjectTypeXY(int x, int y, unsigned int object){
	switch(object){
		case(BLACK)	:
		LCDWriteStringXY(x,y,"BL");
		break;
		case(STEEL)	:
		LCDWriteStringXY(x,y,"ST");
		break;
		case(WHITE)	:
		LCDWriteStringXY(x,y,"WH");
		break;
		case(ALUMINUM)	:
		LCDWriteStringXY(x,y,"AL");
		break;
		case(UNKNOWN)	:
		LCDWriteStringXY(x,y,"UN");
		break;
		default:
		LCDWriteStringXY(x,y,"DE");
		break;
	}
}

/******** Start of  old library code **********/

// defines and macros are in ldc.h file.
// all "_delay_us()" have been replaced with "msTimer()". 


void LCDByte(uint8_t c,uint8_t isdata)
{
//Sends a byte to the LCD in 4bit mode
//cmd=0 for data
//cmd=1 for command


//NOTE: THIS FUNCTION RETURS ONLY WHEN LCD HAS PROCESSED THE COMMAND

	uint8_t hn,ln;			//Nibbles
	uint8_t temp;
	
	
	hn=c>>4;
	//select lower nibble by masking out upper bits
	ln=(c & 0x0F);

	if(isdata==0)
		CLEAR_RS();
	else
		SET_RS();

	//_delay_us(0.500);		//tAS
	msTimer(2);

	SET_E();

	//Send high nibble

	temp=(LCD_DATA_PORT & 0XF0)|(hn);
	LCD_DATA_PORT=temp;

	//_delay_us(1);			//tEH
	msTimer(2);

	//Now data lines are stable pull E low for transmission

	CLEAR_E();

	//_delay_us(1);
	msTimer(2);

	//Send the lower nibble
	SET_E();

	temp=(LCD_DATA_PORT & 0XF0)|(ln);

	LCD_DATA_PORT=temp;

	//_delay_us(1);			//tEH
	msTimer(2);

	//SEND

	CLEAR_E();

	//_delay_us(1);			//tEL
	msTimer(2);

	LCDBusyLoop();
}

void LCDBusyLoop()
{
	//This function waits till lcd is BUSY

	uint8_t busy,status=0x00,temp;

	//Change Port to input type because we are reading data
	LCD_DATA_DDR&=0xF0;

	//change LCD mode
	SET_RW();		//Read mode
	CLEAR_RS();		//Read status

	//Let the RW/RS lines stabilize

	//_delay_us(0.5);		//tAS
	msTimer(1);

	
	do
	{

		SET_E();

		//Wait tDA for data to become available
		//_delay_us(0.5);
		msTimer(1);

		status=LCD_DATA_PIN;
		status=status<<4;

		//_delay_us(0.5);
		msTimer(1);

		//Pull E low
		CLEAR_E();
		//_delay_us(1);	//tEL
		msTimer(1);

		SET_E();
		//_delay_us(0.5);
		msTimer(1);

		temp=LCD_DATA_PIN;
		temp&=0x0F;

		status=status|temp;

		busy=status & 0b10000000;

		//_delay_us(0.5);
		msTimer(1);
		
		CLEAR_E();
		//_delay_us(1);	//tEL
		msTimer(1);
		
	}while(busy);

	CLEAR_RW();		//write mode
	//Change Port to output
	LCD_DATA_DDR|=0x0F;

}

void InitLCD(uint8_t style)
{
	/*****************************************************************
	
	This function Initializes the lcd module
	must be called before calling lcd related functions

	Arguments:
	style = LS_BLINK,LS_ULINE(can be "OR"ed for combination)
	LS_BLINK :The cursor is blinking type
	LS_ULINE :Cursor is "underline" type else "block" type

	*****************************************************************/
	
	//After power on Wait for LCD to Initialize
	//_delay_ms(30);
	msTimer(100);
	
	//Set IO Ports
	LCD_DATA_DDR|=(0x0F);
	LCD_E_DDR|=(1<<LCD_E_POS);
	LCD_RS_DDR|=(1<<LCD_RS_POS);
	LCD_RW_DDR|=(1<<LCD_RW_POS);
	
	//clear all ports
	LCD_DATA_PORT&=0XF0;
	CLEAR_E();
	CLEAR_RW();// registers set to write mode 
	CLEAR_RS();//set to instruction input

	//Set 4-bit mode
	//_delay_us(0.3);	//tAS
	msTimer(2);

	SET_E();
	LCD_DATA_PORT|=(0b00000010); //[B] To transfer 0b00100000 i was using LCD_DATA_PORT|=0b00100000
	//_delay_us(1);
	msTimer(2);
	CLEAR_E();
	//_delay_us(1);
	msTimer(2);
	
	//Wait for LCD to execute the Function set Command
	LCDBusyLoop();                                    //[B] Forgot this delay

	//Now the LCD is in 4-bit mode

	LCDCmd(0b00001100|style);	//Display On
	LCDCmd(0b00101000);			//function set 4-bit,2 line 5x7 dot format
	msTimer(20);
	LCDClear(); //clear display
	msTimer(50);
	
}
void LCDWriteString(const char *msg)
{
	/*****************************************************************
	
	This function Writes a given string to lcd at the current cursor
	location.

	Arguments:
	msg: a null terminated string to print


	*****************************************************************/
	while(*msg!='\0')
	{
		LCDData(*msg);
		msg++;
	}
}

void LCDWriteInt(int val,unsigned int field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
		str[i]=val%10;
		val=val/10;
		i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) LCDData('-');
	for(i=j;i<5;i++)
	{
		LCDData(48+str[i]);
	}
}
void LCDGotoXY(uint8_t x,uint8_t y)
{
	if(x<40)
	{
		if(y) x|=0b01000000;
		x|=0b10000000;
		LCDCmd(x);
	}
}



/******* End of libray code *********/


/*

void LCDSendByteDB(uint8_t byte, uint8_t cmd){
	// if cmd = 1 for command 
	// if cmd = 0 for data
	
	
	// LCD Wiring 
	//	RS	RW	E	DB0	DB1	DB2	DB3	RS
	//	||	||	||	||	||	||	||
	//	PC4	PC5	PC6	PC0	PC1	PC2	PC3
	
	//use 4 bit mode 
	//higher and lower nibble
	uint8_t hNib, lNib; 
	uint8_t temp; 
	
	//select higher nibble
	hNib = (byte>>4);
	//select lower nibble by masking out upper bits
	lNib = (byte & 0x0F);
	
	if (cmd = 1)
	{
		//setup display to receive commands 
		//set RS = 0
		// "~" 1s compliment 
		PORTC &=(~(1<<PC4));		
	} else //cmd = 0
		{
			//setup display to receive data 
			//set RS = 1
			PORTC |=(1<<PC4);
		}
	//set enable pin
	PORTC|=(1<<PC6);
	
}*/