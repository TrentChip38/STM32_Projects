#include "ADC.h"

void ADC_Initialize(void){
	// Set GPIOA pins 2 and 3 as alternate function mode
	GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
	GPIOA->MODER |= GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1;
	
	// Set alternate function 7 for pins 2 and 3 on GPIOA
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3);
	GPIOA->AFR[0] |= 0x7700;
	
	// Set ospeed to high speed for pins 2 and 3 on GPIOA
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3;
	
	// Set PUPDR for GPIOA
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPD2_0 | GPIO_PUPDR_PUPD3_0);

	//enable ADC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	//disable ADC1
	ADC1->CR &= ~ADC_CR_ADEN;
	//enable IO analog switches voltage booster
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN;
	//enable conversion of internal channels
	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;
	//enable temperature sensor channel
	ADC123_COMMON->CCR |= 0x1 << 23;
	//set clock prescaler to 1
	ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;
	// set prscaler to 0x1 for channel 17(new change)
	ADC123_COMMON->CCR |= 0x1<<18;
	//set clock to synchronous mode
	ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;
	ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;
	//clear ADC CCR dual bits
	ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;
	if((ADC1->CR & ADC_CR_DEEPPWD)==ADC_CR_DEEPPWD){
		ADC1->CR &= ~ADC_CR_DEEPPWD;
	}
	ADC1->CR |= ADC_CR_ADVREGEN;
	for(int i = 0; i < 100; i++);
	//configure resolution bits
	ADC1->CFGR &= ~ADC_CFGR_RES;
	//set right alignment
	ADC1->CFGR &= ~ADC_CFGR_ALIGN;
	//select 1 conversion
	ADC1->SQR1 &= ~ADC_SQR1_L;
	//specify channel 17 as first conversion in regular sequence
	ADC1->SQR1 &= ~ADC_SQR1_SQ1;
	ADC1->SQR1 |= 0x11 << 6;
	//configure channel 17 as open ended
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_17;
	//set sample time
	ADC1->SMPR2 |= ADC_SMPR2_SMP17;
	//set discontiguous mode
	ADC1->CFGR &= ~ADC_CFGR_CONT;
	//select software trigger
	ADC1->CFGR &= ~ADC_CFGR_EXTEN;
	//enable ADC1
	ADC1->CR |= ADC_CR_ADEN;
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0);
}
ushort ADC_Read(void){
	//Start ADC
	ADC1->CR |= ADC_CR_ADSTART;
	//Wait untill SAR has finished
	while((ADC123_COMMON->CSR & ADC_CSR_EOC_MST)==0);
	return (ushort)ADC1->DR;//Send that data
}