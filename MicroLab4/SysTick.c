#include "SysTick.h"
#include "stm32l476xx.h"
#define uchar unsigned char
#define uint unsigned int
#include "LCD.h"

volatile int counter;
volatile int running;

void SysTick_Initialize(void){
	SysTick->CTRL = 0;							//Disable SysTick
	SysTick->LOAD = (1600000 - 1);	//Set load reg
	
}
void SysTick_Handler(void){
	counter += 1;
	unsigned char clockstring[8] = "00:00:0";
	counter = 0;
	uint minutes = 0;
	uint seconds = 0;
	uint tens = 0;
		minutes = counter/600;
		clockstring[0] = minutes / 10;
		clockstring[1] = minutes % 10;
		seconds = (counter/10) % 60;
		clockstring[3] = seconds / 10;
		clockstring[4] = seconds % 10;
		tens = counter % 10;
		clockstring[6] = tens;
		LCD_DisplayString(1, clockstring);
}