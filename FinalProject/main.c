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
/*	// 1. Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait until HSI is ready

	// 2. Set HSI as the system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;            // Clear SW bits
	RCC->CFGR |= RCC_CFGR_SW_HSI;         // Set SW bits to select HSI as system clock

	// 3. Wait until HSI is used as the system clock
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

	/////////////////////////chat gpt
// 1. Enable HSI (already done in your code)
// 2. Configure the PLL
RCC->PLLCFGR = 0; // Reset PLL configuration
RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI; // Set HSI as PLL source
RCC->PLLCFGR |= (10 << RCC_PLLCFGR_PLLN_Pos); // Set PLLN to 10 (16 MHz * 10 = 160 MHz)
RCC->PLLCFGR |= (0 << RCC_PLLCFGR_PLLM_Pos); // Set PLLM to 1 (16 MHz / 1 = 16 MHz)
RCC->PLLCFGR |= (2 << RCC_PLLCFGR_PLLR_Pos); // Set PLLR to 2 (160 MHz / 2 = 80 MHz)

	// 3. Enable the PLL
RCC->CR |= RCC_CR_PLLON;
while((RCC->CR & RCC_CR_PLLRDY) == 0);

	// 4. Set the PLL as the system clock source
RCC->CFGR |= RCC_CFGR_SW_PLL;
//while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	// Now the system clock is 80 MHz
	/////////////////////////////////*/
	//Enable GPIOB clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	//Enable GPIOC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	//Initialize things
	StepMotor_Initialize();
	WiiChuck_Initialize(I2C1);
	//SysTick_Initialize();
	
	//Go forever waiting for inturupts and turn on motor
	while(1){
		uint sent;
		uint data1[2];
		uint data2[1];
		uint data3[6];
		data1[0] = 0x40;
		data1[1] = 0x00;
		data2[0] = 0x00;
		
		//Send to enable wii registers
		//sent = I2C_SendData(I2C1, 0x52U << 1, data1, 2);
		//sent = I2C_SendData(I2C1, 0x52U << 1, data2, 1);
		//Get response register data
		//sent = I2C_ReceiveData(I2C1, 0x52U << 1, data3, 6);
		/*
		int time = 50;
		RunMotorBaseRight(time);
		RunMotorBaseLeft(time);
		delay_ms(2000);
		RunMotorArmDown(time);
		RunMotorArmUp(time);
		delay_ms(2000);
		RunMotorMagDown(time);
		RunMotorMagUp(time);
		delay_ms(2000);*/
	}
}