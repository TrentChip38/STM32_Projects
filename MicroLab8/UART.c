#include "SysTick.h"
#include "stm32l476xx.h"
#define uchar unsigned char
#define uint unsigned int
	
//Some global variables
volatile int counter;
volatile int running;

void UART_Initialize(void){
	//USART2 is on by default
	//Disable
	USART2->CR1 &= ~USART_CR1_UE;
	//Set data length 8, 00 = 8 data bits
	USART2->CR2 &= ~USART_CR1_M;
	//Select stop bit, 00 = 1 stop bit
	USART2->CR2 &= ~USART_CR2_STOP;
	//Set no parity
	USART2->CR1 &= ~USART_CR1_PCE;
	//Oversampling?
	//USART2->CR1 &= ~USART_CR1_OVER8;
	//Baud rate 9600
	USART2->BRR = 0x208D;
	//Enable transmission and reception
	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	//Enable USART
	USART2->CR1 |= USART_CR1_UE;
	//Verify reception and transmisison optional
}

void USART_Write(USART_TypeDef * USARTx, uint * buffer, int nBytes){
	
}