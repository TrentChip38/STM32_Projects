#include "UART.h"
#include "ADC.h"
#define TS_CAL1 (*(volatile unsigned short*)0x1FFF75A8)
#define TS_CAL2 (*(volatile unsigned short*)0x1FFF75CB)
//Some global variables
ushort Buffer;

void UART_Initialize(void){
	
	//Set USART2 Clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
	RCC->CCIPR &= ~(RCC_CCIPR_USART2SEL);
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
	
	//USART2 is on by default
	//Disable
	USART2->CR1 &= ~USART_CR1_UE;
	//Set data length 8, 00 = 8 data bits
	USART2->CR1 &= ~USART_CR1_M;
	//Select stop bit, 00 = 1 stop bit
	USART2->CR2 &= ~USART_CR2_STOP;
	//Set no parity
	USART2->CR1 &= ~USART_CR1_PCE;
	//Oversampling?
	USART2->CR1 &= ~USART_CR1_OVER8;
	//Baud rate 9600
	USART2->BRR &= ~(0x0FFFF);
	USART2->BRR |= 0x1A0;//0x683;////208D;
	
	//Initialize the interupt
	USART2->CR1 |= USART_CR1_RXNEIE;
	//USART2->CR1 &= ~USART_CR1_TXEIE;
	NVIC_SetPriority(USART2_IRQn, 0);
	NVIC_EnableIRQ(USART2_IRQn);
	//Enable transmission and reception
	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	//Enable USART
	USART2->CR1 |= USART_CR1_UE;
	//Verify reception and transmisison optional
}

void USART2_IRQHandler(void){
	//If data being sent
	if(USART2->ISR & USART_ISR_RXNE){
		//Get the singe character from Read register
		Buffer = USART2->RDR;
		//Check if T or t
		if(Buffer == 't' || Buffer == 'T'){
			//Reset for future check
			Buffer = 0;
			ushort intemp;
			//Read ADC temp
			intemp = ADC_Read();
			//Calculate actual temp using calibration values
			float temp = 80.0f*(intemp - TS_CAL1)/(TS_CAL2 - TS_CAL1) + 30;
			//Characters to print
			uchar characters[9];
			//Float into ascii values
			sprintf(characters, "%.4f\n",temp);
			//Write Temperature to serial USART, read with PUTTY
			USART_Write(USART2, characters, 9);
		}
	}
}

void USART_Write(USART_TypeDef * USARTx, uchar * buffer, uint nBytes){
	uint i;
	for(i = 0; i < nBytes; i++){
		while(!(USARTx->ISR & USART_ISR_TXE));//Wait until TXE set
		USARTx->TDR = buffer[i] & 0xFF;//Write to TDR to clear TXE flag
	}
	//Wait until TC bit set
	while(!(USARTx->ISR & USART_ISR_TC));
	//Write 1 to TCCF in ICR clears the TC bit in ISR
	USARTx->ICR |= USART_ICR_TCCF;
}