#include "stm32l476xx.h"
#include "SysTick.h"
#include "StepMotor.h"
#include "KeyPad.h"

//#include <STC15.H>
//#include <string.h>
//#include <INTRINS.H>
#define uchar unsigned char
#define uint unsigned int

int main(void){
	//Enable the Internal High Speed oscillator (HSI)
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	//Enable GPIOB clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	//Enable GPIOC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	//Initialize things
	KeyPad_Initialize();
	StepMotor_Initialize();
	SysTick_Initialize();
	
	//Go forever taking new inputs and setting clock
	while(1){
	//Get minutes from user
	char ch = 0;
	char min1 = 0;
	char min2 = 0;
	int min = 0;
	//Get first button press character
	ch = WaitForNextPress();
	//Wait until number entered followed by #
	while(ch != '#' || (min1 == 0 && min2 == 0)){
		//Check if valid number
		if (ch >= 0x30 && ch <= 0x39){
			//Shift into character line
			min2 = min1;
			min1 = ch;
		}
		//Get next button press character
		ch = WaitForNextPress();
		//Delay
		delay_ms(1000);
	}
	//Seconds in tens and ones place
	int sec1 = min2 - 48;
	int sec2 = min1 - 48;
	sec1 = sec1*10;
	min = sec1 + sec2;
	//Actually these are all in seconds...
	
	//Set motor to minutes with ratio to move fast
	int min_time = min * (.48);
	//Spin CCW fast
	WindMotor(min_time);
	
	//Wait for # again
	ch = 0;
	while(ch != '#'){
		ch = WaitForNextPress();
	}
	
	//Start motor countdown slower with ratio and slowdown
	RunMotor(min*0.49, 43);//Spin CW at pace of time
	
	//Buzz for a bit when done
	for(int i = 0; i < 80; i++){
		//On and off at 6us period
		GPIOB->ODR |= 0x00000010;
		delay_ms(3);
		GPIOB->ODR &= 0xFFFFFF0F;
		delay_ms(3);
	}
	/* Ended up not actually needing systick...
	Motor function was accurate enough using its own timing
	//Start the count down, and let SysTick_Handler unwind the motor
	SysTick_Start(min);
	
	//Wait until clock stopped
	int stopped = 1;
	while(stopped){
		//If running, then this function will wait
		stopped = SysTick_IsGoing();
	}*/
	}
}