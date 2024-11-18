#ifndef __STM32L476R_NUCLEO_WII_H
#define __STM32L476R_NUCLEO_WII_H
#include "stm32l476xx.h"
//#include "stm32f4xx_hal.h"
#define uchar unsigned char
#define uint unsigned int
void WiiChuck_Initialize(I2C_TypeDef * I2Cx);
void I2C_Start(I2C_TypeDef * I2Cx, uint DevAddress, uint Size, uint Direction);
void I2C_Stop(I2C_TypeDef * I2Cx);
void I2C_WaitLineIdle(I2C_TypeDef * I2Cx);
uint I2C_SendData(I2C_TypeDef * I2Cx, uint SlaveAddress, uint * pData, uint Size);
uint I2C_ReceiveData(I2C_TypeDef * I2Cx, uint SlaveAddress, uint *pData, uint Size);
#endif