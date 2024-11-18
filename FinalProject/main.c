#include "stm32l476xx.h"
//#include "SysTick.h"
#include "StepMotor.h"
#include "WiiChuck.h"

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
	WiiChuck_Initialize(I2C1);
	StepMotor_Initialize();
	//SysTick_Initialize();
	
	//Go forever waiting for inturupts and turn on motor
	while(1){
	int time = 10000;
	//delay_ms(1000);
	WindMotor(time);
	}
}