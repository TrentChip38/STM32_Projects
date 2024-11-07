#include "SysTick.h"
#include "stm32l476xx.h"
#define uchar unsigned char
#define uint unsigned int
	
//Some global variables
volatile int counter;
volatile int running;
uint clock;
uint clockSetTime;

void SysTick_Initialize(void){
	//Initialize all my global variables here
	counter = 0;		//Count, keep track of 1/10's of seconds
	running = 0;		//If supposed to be on or not
	//Start clocksting as all 0's
	clock = 0;
	
	//Start initializing Systick
	SysTick->CTRL = 0;						//Disable SysTick
	SysTick->LOAD = (400000 - 1);	//Set load reg to divide by 400kHz for 100ms timing
	// Set interrupt priority of SysTick to least urgency (i.e., largest priority value)
	NVIC_SetPriority (SysTick_IRQn, 1); //set to 1 or //(1<<__NVIC_PRIO_BITS) - 1);
	//Finish setting upt SysTick and start it
	SysTick->VAL = 0;// Reset the SysTick counter value
	// Select processor clock: 1 = processor clock; 0 = external clock
	//SysTick->CTRL |= 1;//SysTick_CTRL_CLKSOURCE;
	// Enables SysTick interrupt, 1 = Enable, 0 = Disable
	SysTick->CTRL |= 7; //SysTick_CTRL_TICKINT;
}
//Runs every tenth of a second
void SysTick_Handler(void){
	//Only run if (running)
	if(running){
	//Every tenth of a second increase count
		counter += 1;
	//Set each time type
		clock = counter/600;//Calculate minutes
	if (clock == clockSetTime){
		//When time reached, set flag
		running = 0;
		counter = 0;
	}
	
	//Set motor based on time
	
	}
}


