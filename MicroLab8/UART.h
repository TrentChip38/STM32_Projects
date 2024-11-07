#ifndef __STM32L476R_NUCLEO_SYS_H
#define __STM32L476R_NUCLEO_SYS_H
#define uchar unsigned char
#define uint unsigned int
void UART_Initialize(void);
void USART_Write(USART_TypeDef * USARTx, uint * buffer, int nBytes);
//int SysTick_IsGoing(void);
//void SysTick_Start(int);
#endif