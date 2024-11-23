#include "StepMotor.h"
	
//Some global variables

void StepMotor_Initialize(void){
	//Motor ouputs to set
	GPIOB->MODER |= 0xFFFF00FF;		//Moder = 111..
	GPIOB->MODER &= 0x5555FF55;		//Mask to be 555.. set all as outputs
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

void RunMotorBaseRight(int steps){
	//Run continuously for time
	int wait = 10;
	//int steps = time*10;
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
void RunMotorBaseLeft(int steps){
	//Run continuously for time
	int wait = 10;
	//int steps = time*10;
	for(int i = 0; i < steps; i++){
		//Mask output 0011
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF9;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFFC;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF6;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1001
		GPIOB->ODR |= 0x0000000F;
		GPIOB->ODR &= 0xFFFFFFF3;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFFFFF0;
		//delay_ms(delay*10);
	}
}
void RunMotorArmUp(int steps){
	//Run continuously for time
	int wait = 15;
	//int steps = time*10;
	for(int i = 0; i < steps; i++){
		//Mask output 0011
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFF3FF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFF6FF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFFCFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1001
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFF9FF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFFF0FF;
		//delay_ms(delay*10);
	}
}
void RunMotorArmDown(int steps){
	//Run continuously for time
	int wait = 15;
	//int steps = time*10;
	for(int i = 0; i < steps; i++){
		//Mask output 0011
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFF9FF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFFCFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFF6FF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1001
		GPIOB->ODR |= 0x00000F00;
		GPIOB->ODR &= 0xFFFFF3FF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFFF0FF;
		//delay_ms(delay*10);
	}
}
void RunMotorMagUp(int steps){
	//Run continuously for time
	int wait = 10;
	//int steps = time*10;
	for(int i = 0; i < steps; i++){
		//Mask output 0011
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFF3FFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFF6FFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFFCFFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1001
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFF9FFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFF0FFF;
		//delay_ms(delay*10);
	}
}
void RunMotorMagDown(int steps){
	//Run continuously for time
	int wait = 10;
	//int steps = time*10;
	for(int i = 0; i < steps; i++){
		//Mask output 0011
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFF9FFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 0110
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFFCFFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1100
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFF6FFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask output 1001
		GPIOB->ODR |= 0x0000F000;
		GPIOB->ODR &= 0xFFFF3FFF;
		//Delay for step to happen
		delay_ms(wait);
		//Mask to turn off
		GPIOB->ODR &= 0xFFFF0FFF;
		//delay_ms(delay*10);
	}
}