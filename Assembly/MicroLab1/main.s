;******************** (C) Yifeng ZHU *******************************************
; @file    main.s
; @author  Yifeng Zhu
; @date    May-17-2015
; @note
;           This code is for the book "Embedded Systems with ARM Cortex-M 
;           Microcontrollers in Assembly Language and C, Yifeng Zhu, 
;           ISBN-13: 978-0982692639, ISBN-10: 0982692633
; @attension
;           This code is provided for education purpose. The author shall not be 
;           held liable for any direct, indirect or consequential damages, for any 
;           reason whatever. More information can be found from book website: 
;           http:;www.eece.maine.edu/~zhu/book
;Loop turning LED on and off
;Original psuedocode got deleted
;*******************************************************************************

INCLUDE core_cm4_constants.s
	INCLUDE stm32l476xx_constants.s
	
	AREA    main, CODE, READONLY
	EXPORT	__main
	ENTRY			
				
__main	PROC			;Start the main program
		
    							; Enable the clock to GPIO Port A	
	LDR r0, =RCC_BASE			;Load reset and clock control into r0
	LDR r1, [r0, #RCC_AHB2ENR]		;Load Base with specific offset into r1
	ORR r1, r1, #RCC_AHB2ENR_GPIOAEN	;Or r1 with this mask
	STR r1, [r0, #RCC_AHB2ENR]		;Store r1 into Base with offset
	
		; MODE: 00: Input mode, 01: General purpose output mode
    		; 10: Alternate function mode, 11: Analog mode (reset state)
	
				; Turn on the LED
	LDR r0, =GPIOA_BASE		;Load r0 with GPIOA
	LDR r1, [r0, #GPIO_MODER]	;Load r0 with offset into r1
	AND r1, r1, #0xFFFFF3FF		;r1 = r1 & 0xFFFFF3FF
	ORR r1, r1, #0x00000400		;r1 = r1 | 0x00000400
	STR r1, [r0, #GPIO_MODER]	;store r1 into r0 + offset of MODER
loop	LDR r1, [r0, #GPIO_ODR]		;load r1 with r0 + offset of ODR
	ORR r1, r1, #0x00000020		;r1 = r1 | 0x00000020
	STR r1, [r0, #GPIO_ODR]		;store r1 into r0 + offset of ODR
	MOV r1, #0x00000000		;Just put 0 into r1
	STR r1, [r0, #GPIO_ODR]		;store r1 into r0 + offset of ODR
	
 	B 		loop			;branch to loop where the LED turns on

	ENDP					;End main
					
	ALIGN			

	END					;End of program

