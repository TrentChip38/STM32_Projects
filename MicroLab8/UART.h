#ifndef __STM32L476R_NUCLEO_UART_H
#define __STM32L476R_NUCLEO_UART_H
#include "stm32l476xx.h"
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ushort unsigned short
void UART_Initialize(void);
void USART2_IRQHandler(void);
void USART_Write(USART_TypeDef * USARTx, uchar * buffer, uint nBytes);
#endif