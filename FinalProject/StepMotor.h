#ifndef __STM32L476R_NUCLEO_MOT_H
#define __STM32L476R_NUCLEO_MOT_H
#include "stm32l476xx.h"
#define uchar unsigned char
#define uint unsigned int
void StepMotor_Initialize(void);
void delay_ms(uint);
void RunMotor(int, int);
void RunMotorBaseRight(int);
void RunMotorBaseLeft(int);
void RunMotorArmUp(int);
void RunMotorArmDown(int);
void RunMotorMagUp(int);
void RunMotorMagDown(int);
#endif