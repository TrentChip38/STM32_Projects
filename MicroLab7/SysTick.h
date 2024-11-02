#ifndef __STM32L476R_NUCLEO_SYS_H
#define __STM32L476R_NUCLEO_SYS_H
#define uchar unsigned char
#define uint unsigned int
void SysTick_Initialize(void);
void SysTick_Handler(void);
int SysTick_IsGoing(void);
void SysTick_Start(int);
#endif