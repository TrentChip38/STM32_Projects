#include "StepMotor.h"
	
//Some global variables

void StepMotor_Initialize(void){
	//Motor ouputs to set
	GPIOB->MODER |= 0xFFFFFF00;		//Moder = 111..
	GPIOB->MODER &= 0x555555FF;		//Mask to be 555.. set all as outputs
}

void delay_ms(uint ms) {
	volatile uint i, j;
	//loop for ms
	for(i = 0; i < ms; i++)
		for(j = 0; j < 200; j++);
}

void RunMotor(int time, int delay){
	//Set input param to wait time between steps
	int wait = delay;
	//Time*ratio = total amount of 4 step cycles to make
	int steps = time*18;
	//Run continuously for steps
	for(int i = 0; i < steps; i++){
		//Mask output 1001
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFF9F;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFFCF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFFFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0011
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFF3F;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFFFF0F;
		//delay_ms(delay);
	}
}

void WindMotor(int time){
	//Run continuously for time
	int wait = 10;
	int steps = time*18;
	for(int i = 0; i < steps; i++){
		//Mask output 0011
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFF3F;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFF6F;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFFCF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1001
		GPIOB->ODR |= 0x000000F0;
		GPIOB->ODR &= 0xFFFFFF9F;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFFFF0F;
		//delay_ms(delay*10);
	}
}