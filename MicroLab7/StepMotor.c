#include "StepMotor.h"
#include "stm32l476xx.h"
#include "KeyPad.h"
#define uchar unsigned char
#define uint unsigned int
	
//Some global variables

void StepMotor_Initialize(void){
	//Figure out what ouputs to set
	//GPIOB already set as output
	//GPIOB->MODER |= 0xFFFFFFFF;		//Moder = 111..
	//GPIOB->MODER &= 0x55555555;		//Mask to be 555.. set all as outputs
}

void RunMotor(int time, int delay){
	//Set input param to wait time between steps
	int wait = delay;
	//Time*ratio = total amount of 4 step cycles to make
	int steps = time*18;
	//Run continuously for steps
	for(int i = 0; i < steps; i++){
		//Mask output 1001
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF9;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFFC;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF6;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0011
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF3;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFFFFF0;
		//delay_ms(delay);
	}
}

void WindMotor(int time){
	//Run continuously for time
	int wait = 10;
	int steps = time*18;
	for(int i = 0; i < steps; i++){
		//Mask output 0011
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF3;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF6;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFFC;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1001
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF9;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFFFFF0;
		//delay_ms(delay*10);
	}
}