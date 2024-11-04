#include "KeyPad.h"
#include "stm32l476xx.h"
#define uchar unsigned char
#define uint unsigned int
	
void KeyPad_Initialize(void){
	//Mask Modes of B and C
	GPIOB->MODER |= 0xFFFFFFFF;		//Moder = 111..
	GPIOB->MODER &= 0x55555555;		//Mask to be 555.. set all as outputs
	GPIOB->OTYPER |= 0x0000F000;	//Mask pins 12-15 to 1 in otyper
	GPIOC->MODER &= 0xFFFFFF00;		//First 4 pins mode to 00 input
	GPIOC->PUPDR &= 0xFFFFFF00;		//First 4 registers to 00
	GPIOC->PUPDR |= 0x00000055;		//To be set to pull up (01)
}

void delay_ms(uint ms) {
	volatile uint i, j;
	//loop for ms
	for(i = 0; i < ms; i++)
		for(j = 0; j < 200; j++);
}

char WaitForNextPress(void){
	char character = 0;
	//Keep calling checkbuttons untill character returned
	while(character == 0){
		character = CheckButtons();
	}
	//return that character
	return character;
}

char CheckButtons(void){
	//Check buttons and return
	int col = 0;			//colum variable
	char inchar = 0;		//input character
	char lastchar = 0;	//keep track of last char
	int nochar = 0;		//keep track if no character pressed
		//check first row
		GPIOB->ODR &= 0xFFFF0FFF;		//set outputs
		GPIOB->ODR |= 0x0000E000;		//mask E to set first row
		delay_ms(10);//delay each button checking time
		col = GPIOC->IDR & 0x0000000F;//get output
		switch(col){//decide if a char was pressed
			case 0xE:
				inchar = '1';
				break;
			case 0xD:
				inchar = '4';
				break;
			case 0xB:
				inchar = '7';
				break;
			case 0x7:
				inchar = '*';
				break;
			default:
				nochar ++;
				break;
			}
		//check second row
		GPIOB->ODR &= 0xFFFF0FFF;
		GPIOB->ODR |= 0x0000D000;
		//delay_ms(1);
		col = GPIOC->IDR & 0x0000000F;
		switch(col){//decide if a char was pressed
			case 0xE:
				inchar = '2';
				break;
			case 0xD:
				inchar = '5';
				break;
			case 0xB:
				inchar = '8';
				break;
			case 0x7:
				inchar = '0';
				break;
			default:
				nochar ++;
				break;
			}
		//check third row
		GPIOB->ODR &= 0xFFFF0FFF;
		GPIOB->ODR |= 0x0000B000;
		//delay_ms(1);
		col = GPIOC->IDR & 0x0000000F;
		switch(col){//decide if a char was pressed
			case 0xE:
				inchar = '3';
				break;
			case 0xD:
				inchar = '6';
				break;
			case 0xB:
				inchar = '9';
				break;
			case 0x7:
				inchar = '#';
				break;
			default:
				nochar ++;
				break;
			}
		//check third row
		GPIOB->ODR &= 0xFFFF0FFF;
		GPIOB->ODR |= 0x00007000;
		//delay_ms(1);
		col = GPIOC->IDR & 0x0000000F;
		switch(col){//decide if a char was pressed
			case 0xE:
				inchar = 'A';
				break;
			case 0xD:
				inchar = 'B';
				break;
			case 0xB:
				inchar = 'C';
				break;
			case 0x7:
				inchar = 'D';
				break;
			default:
				nochar ++;
				break;
			}
		//turn off rows
		GPIOB->ODR &= 0xFFFF0FFF;
		if(inchar == lastchar){
			//also debounce and check if already pressed
			inchar = 0;
		}else{
		lastchar = inchar;//keep track of last char used
		}
		if(nochar == 4){//if all case statements defaulted
			//reset inchar to 0, no button pressed
			inchar = 0;
		}
		//then reset nochar to 0
		nochar = 0;
	return inchar;
}