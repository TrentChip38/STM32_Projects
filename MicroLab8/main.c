#include "stm32l476xx.h"
#include "UART.h"

#define uchar unsigned char
#define uint unsigned int

int main(void){
	//IDK if we need clocks or not... I just left them
	//Enable the Internal High Speed oscillator (HSI)
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	//Enable GPIOB clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	//Enable GPIOC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	
	//Initialize UART
	UART_Initialize();
	
	//Go forever taking new inputs and setting clock
	while(1){
		//Interupts will constantly check for UART in
		//Check character
		//If T entered, start ADC
		//Interupt for when ADC finishes
		//Send temp over UART
		//Keep waiting
	}
}