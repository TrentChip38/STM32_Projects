#ifndef __STM32L476R_NUCLEO_SYS_H
#define __STM32L476R_NUCLEO_SYS_H
#define uchar unsigned char
#define uint unsigned int
void UART_Initialize(void);
void USART_Write(USART_TypeDef * USART2, uint * buffer, int nBytes);
void USART_Read (USART_TypeDef *USART2, uint *buffer, uint nBytes);
//int SysTick_IsGoing(void);
//void SysTick_Start(int);
#endif