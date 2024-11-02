#ifndef __STM32L476R_NUCLEO_KEY_H
#define __STM32L476R_NUCLEO_KEY_H
#define uchar unsigned char
#define uint unsigned int
void KeyPad_Initialize(void);
void delay_ms(uint);
char WaitForNextPress(void);
char CheckButtons(void);
#endif