#include "WiiChuck.h"

void WiiChuck_Initialize(I2C_TypeDef * I2Cx){
	//Alternate mode
	GPIOB->MODER |= 0x0000F000;
	GPIOB->MODER &= 0xFFFFAFFF;
	//Open drain
	GPIOB->OTYPER &= 0x000000C0;
	//Medium speed??
	//GPIOB->OSPEEDR |= 0x00005000;
	//01 = Pull-up
	GPIOB->PUPDR &= 0xFFFF0FFF;
	//GPIOB->PUPDR |= 0x00005000;
	
	// Set alternate function AF4 for pins 6 and 7 on GPIOB
	//GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3);
	//GPIOB->AFR[0] |= 0x7700;
	//GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6 | GPIO_AFRL_AFSEL7); // Clear AF bits
	//GPIOB->AFR[0] |= (4 << (GPIO_AFRL_AFSEL6)) | (4 << (GPIO_AFRL_AFSEL7)); // Set AF4
	// 3. Configure AF4 for PB6 and PB7 in AFRL
	//GPIOB->AFR[0] &= ~((0xF << (6 * 4)) | (0xF << (7 * 4))); // Clear AFRL for PB6 and PB7
	//GPIOB->AFR[0] |= (4 << (6 * 4)) | (4 << (7 * 4));        // Set AFRL to '4' (AF4)
	//set alt function
	GPIOB->AFR[0] &= 0x00FFFFFF;
	GPIOB->AFR[0] |= 0x44000000;
	
	//Initialize I2C communication for Wii Nunchuck
	RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN; // I2Cl clock enable 
	// 00 = PCLK, 61 = SYSCLK, 16 = HSI16, 11 = Reserved 
	RCC->CCIPR &= ~RCC_CCIPR_I2C1SEL; //Clear bits 
	RCC->CCIPR |= RCC_CCIPR_I2C1SEL_0; //Select SYSCLK 
	
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C1RST; // 1 = Reset/2C1 
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C1RST; // Complete the reset
	
	//I2C CR1 configuration
	I2Cx->CR1 &= ~I2C_CR1_PE;  //Disable I2C
	I2Cx->CR1 &= ~I2C_CR1_ANFOFF; //Analog noise filter enabled
	I2Cx->CR1 &= ~I2C_CR1_DNF;	//Digital filter disabled
	I2Cx->CR1 |= I2C_CR1_ERRIE;	//Errors interupt enable
	//I2Cx->CR1 &= ~I2C_CR1_SMBUS;	//SMBus Mode
	I2Cx->CR1 &= ~I2C_CR1_NOSTRETCH; //Enable clock stretching
	
	//I2C timng configuration
	I2Cx->TIMINGR = 0;
	//If Systimer = 80MHx, PRESC = 7, 80m/(1+presc) = 10MHz
	//Ours: PRESC = 39, 4MHz/(1+PRESC) = 100kHz
	I2Cx->TIMINGR &= ~I2C_TIMINGR_PRESC; //Clear the prescaler
	I2Cx->TIMINGR |= 7U << 28;	//Set clock prescaler
	//Might need to multiply all these by 10? But idk how this format works
	I2Cx->TIMINGR |= 49U;			//SCLL Low period
	I2Cx->TIMINGR |= 49U << 8; //SCLH High period
	I2Cx->TIMINGR |= 14U << 20;	//SCLDEL Data setup time
	I2Cx->TIMINGR |= 15U << 16;	//SDADEL Data hold time*/
	//I2Cx->TIMINGR = (0 << 28) | (14 << 20) | (4 << 16) | (50 << 8) | 52;
	
	//I2C own address 1 register (I2C_OAR1)
	I2Cx->OAR1 &= ~I2C_OAR1_OA1EN;
	//I2Cx->OAR1 = I2C_OAR1_OA1EN | OwnAddr;//7-bit address
	I2Cx->OAR1 &= ~I2C_OAR2_OA2EN;//Disable own address 2
	
	//I2C CR2 Configuration
	I2Cx->CR2 &= ~I2C_CR2_ADD10;	//0 = 7 bit mode, 1 = 10 bit mode
	I2Cx->CR2 |= I2C_CR2_AUTOEND; //Enable the auto end
	I2Cx->CR2 |= I2C_CR2_NACK;		//For slave mode set NACK
	I2Cx->CR2 |= I2C_CR1_PE;			//Enable I2C1
}

void I2C_Start(I2C_TypeDef * I2Cx, uint DevAddress,uint Size, uint Direction){
    // Direction = 0: Master requests a write transfer 
    // Direction = 1: Master requests a read transfer 
     uint32_t tmpreg = I2Cx->CR2;
     tmpreg &= (uint32_t)~((int32_t)(I2C_CR2_SADD   |  I2C_CR2_NBYTES  |
                                      I2C_CR2_RELOAD |  I2C_CR2_AUTOEND |
                                      I2C_CR2_RD_WRN |  I2C_CR2_START   |
                                      I2C_CR2_STOP)); 

    if (Direction == 1) //READ_FROM_SLAVE
        	tmpreg |= I2C_CR2_RD_WRN;   // Read from Slave 
    else 
        	tmpreg &= ~I2C_CR2_RD_WRN; // Write to Slave 

    tmpreg |= (uint32_t)(((uint32_t) DevAddress & I2C_CR2_SADD) | 
                        (((uint32_t) Size << 16) & I2C_CR2_NBYTES)); 

    tmpreg |= I2C_CR2_START; 
    I2Cx->CR2 = tmpreg; 
}

void I2C_Stop(I2C_TypeDef * I2Cx){
    // Master: Generate STOP bit after the current byte has been transferred 
    I2Cx->CR2 |= I2C_CR2_STOP; 

    // Wait until STOPF flag is reset 
    while( (I2Cx->ISR & I2C_ISR_STOPF) == 0 ); 

    I2Cx->ICR |= I2C_ICR_STOPCF; // Write 1 to clear STOPF flag
}

void I2C_WaitLineIdle(I2C_TypeDef * I2Cx){
	//Wait until I2C bus is ready
	while((I2Cx->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY);//If busy, wait
}

uint I2C_SendData(I2C_TypeDef * I2Cx, uint SlaveAddress, uint * pData, uint Size){
    uint i; 
    if (Size <= 0 || pData == 0) return -1;

    // Wait until the Line is idle 
    I2C_WaitLineIdle(I2Cx); 

    // The Last argument: e = Sending data to the slave 
    I2C_Start(I2Cx, SlaveAddress, Size, 0);

    for (i = 0; i < Size; i++) 
    {
        // TXIS bit is set by hardware when the TXDR register is empty and the 
        // data to be transmitted must be written in the TXDR register. It is 
        // cleared when the next data to be sent is written in the TXDR register. 
        // The TXIS flag is not set when a NACK is received. 
        while( (I2Cx->ISR & I2C_ISR_TXIS) == 0 ){
					if (I2Cx->ISR & I2C_ISR_NACKF) {
					I2C_Stop(I2Cx);  // Generate a stop condition to reset the bus
					return -1;       // Return error
					}
				}
//Debugging stuck here (Changed TXIS to TXE)
        // TXIS is cleared by writing to the TXDR register 
        I2Cx->TXDR = pData[i] & I2C_TXDR_TXDATA;
			//Correctly puts value into TXDR
    }

    // Wait until TC flag is set 
    while((I2Cx->ISR & I2C_ISR_TC) == 0){
//Also stuck here^^
    if( (I2Cx->ISR & I2C_ISR_NACKF) != 0 ) 
        return -1; 
	}
		if( (I2Cx->ISR & I2C_ISR_NACKF) != 0 ) 
        return -1; 
		
    I2C_Stop(I2Cx);

    return 0;
}

uint I2C_ReceiveData(I2C_TypeDef * I2Cx, uint SlaveAddress, uint *pData, uint Size){
	
    uint i; 

    if (Size <= 0 || pData == 0) return -1; 

    I2C_WaitLineIdle(I2Cx);
		I2C_Start(I2Cx, SlaveAddress, Size, 1);
		for(i = 0; i < Size; i++){
			//wait until RXNE flag is set
			while((I2Cx->ISR & I2C_ISR_RXNE) == 0);
			pData[i] = I2Cx->RXDR & I2C_RXDR_RXDATA;
		}
		//Wait until TCR flag is set
		while((I2Cx->ISR & I2C_ISR_TC) == 0);
		I2C_Stop(I2Cx);
		return 0;
}
