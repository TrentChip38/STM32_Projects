#include "stm32l476xx.h"
#include <stdio.h>
#include "UART.h"
#include "ADC.h"
#define uchar unsigned char
#define uint unsigned int

int main(void){
	//Enable the Internal High Speed oscillator (HSI)
	RCC->CR |= RCC_CR_HSION;
	//RCC->CR |= RCC_CR_MSION;
	//while((RCC->CR & RCC_CR_HSIRDY) == 0);
	//Enable GPIOA clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	//Enable GPIOC clock
	//RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	//Initialize UART and ADC
	ADC_Initialize();
	UART_Initialize();
	//Go forever taking new inputs and setting clock
	while(1){
		//Interupts Constantly check for UART sent
		//Check if character is T or t
		//Interupt when ADC finishes
		//Send temp over UART
		//Keep waiting
	}
}
