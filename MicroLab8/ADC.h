#ifndef __STM32L476R_NUCLEO_ADC_H
#define __STM32L476R_NUCLEO_ADC_H
#include "stm32l476xx.h"
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ushort unsigned short
void ADC_Initialize(void);
ushort ADC_Read(void);
#endif