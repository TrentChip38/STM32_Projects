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
;Pseudocode
;Start
;NumCount = 0
;On/Off = 0
;RESETLOOP
;Loop Count = 0
;LOOP
;	Check buttons
;	Wait 100 loop here?
;	If Green: start (On = 1)
;	If Yellow: pause (On = 0)
;	If Red: reset (NumCount = 0)
;	Increment
;	If On: Increment LoopCount
;If LoopCount = loopAmount: 
;NumCount++
;		Go to ResetLoop
;Go to LOOP
;End
;
;*******************************************************************************


	INCLUDE core_cm4_constants.s
	INCLUDE stm32l476xx_constants.s
	
	AREA    main, CODE, READONLY
	EXPORT	__main
	ENTRY			
				
__main	PROC
		
    ; Enable the clock to GPIO Port A, B, and C
	LDR r0, =RCC_BASE	;Load reset and clock controll into r0
	LDR r1, [r0, #RCC_AHB2ENR]			;Load Base with specific offset into r1
	ORR r1, r1, #RCC_AHB2ENR_GPIOAEN	;Or r1 with this mask
	ORR r1, r1, #RCC_AHB2ENR_GPIOBEN	;Or r1 with this mask
	ORR r1, r1, #RCC_AHB2ENR_GPIOCEN	;Or r1 with this mask
	STR r1, [r0, #RCC_AHB2ENR]			;Store r1 into Base with offset
	
	; MODE: 00: Input mode, 01: General purpose output mode
    ;       10: Alternate function mode, 11: Analog mode (reset state)
	
	; Turn on the LED and User Push-button
	LDR r0, =GPIOA_BASE			;Load r0 with GPIOA
	LDR r1, [r0, #GPIO_MODER]	;Load r0 with offset into r1
	AND r1, r1, #0xFFFFF3FF		;r1 = r1 & 0xFFFFF3FF
	ORR r1, r1, #0x00000400		;r1 = r1 | 0x00000400
	STR r1, [r0, #GPIO_MODER]	;store r1 into r0 + offset of MODER
	;Set mode for pins used on b as sinking
	LDR r5, =GPIOB_BASE			;Load r0 with GPIOB address
	LDR r6, [r5, #GPIO_MODER]	;Load r5 with offset into r6
	LDR r2, =0xFFF00000			;Store mask in r2
	AND r6, r2 					;And r6 with the mask
	LDR r2, =0x00055555			;Load next mask
	ORR r6, r2					;Or r6 with this mask
	STR r6, [r5, #GPIO_MODER]	;store r6 into r5 + offset of MODER
	;configure pins in C to be used as button inputs reading ground
	LDR r7, =GPIOC_BASE			;Load r0 with GPIOC
	LDR r8, [r7, #GPIO_MODER]	;Load r7 with offset into r8
	LDR r2, =0xF3FFFF00			;Load mask into r2
	AND r8, r2					;And r8 with mask
	STR r8, [r7, #GPIO_MODER]	;store r8 into r7 + offset of MODER
	;Set up some variables and set PUPDR modes
			LDR r5, =GPIOC_BASE			;Load r5 with GPIOC
			LDR r6, [r5, #GPIO_PUPDR]	;Load r6 with Base + offset
			LDR r6, =0x00000055			;Load value to set mode
			STR r6, [r5, #GPIO_PUPDR]	;Store that into GPIOC + offset
				;Set sinking pins on B
			LDR r5, =GPIOB_BASE			;Load r5 with GPIOC
			LDR r6, [r5, #GPIO_PUPDR]	;Load r6 with Base + offset
			LDR r2, =0xFFF00000			;Store mask in r2
			AND r6, r2					;AND mask with r6
			LDR r2, =0x000AAAAA			;Load next mask in r2
			ORR r6, r2					;Or with mask
			STR r6, [r5, #GPIO_PUPDR]	;Store r6 into its place
			
			;Set my variables to be used in the loop
			MOV r1, #0					;NumCnt = 0
			MOV r2, #0					;LoopCnt = 0
			MOV r3, #0					;ON/OFF = 0
			LDR r4, =0x00400000			;Increment num amount
			LDR r9, =0x0000E0AF			;Times to loop
RESET		MOV r2, #0					;Reset loop cnt
LOOP		ADD r2, r2, #1				;Increment loop
				;Output to all the LEDs
			LDR r6, [r5, #GPIO_ODR]		;Load B +ODR
			LDR r7, =0x000FFFFF			;Load mask
			ORR r6, r7					;Orr r6 with mask
			LDR r7, =0xFFF00000			;Load another mask
			EOR r0, r1, #0xFFFFFFFF		;r0 = r1 XOR with all 1's
			LSR r0, #22					;Logic shift right by 22
			ORR r7, r0					;Mask r7 with r0
			AND r6, r7					;And r6 with r7
			STR r6, [r5, #GPIO_ODR]		;Store that in B + ODR
				;Read buttons
			LDR r7, =GPIOC_BASE			;Load GPIOC
			LDR r8, [r7, #GPIO_IDR]		;Load GPIOC with offset into r8
			AND r8, #0x0000000F			;And r8 with 0xF
			CMP r8, #0x0000000E			;Compare r8 to 0xE
			BNE	NOTGREEN				;Don't turn on
GREEN		MOV r3, #1					;if it is low, State = ON
NOTGREEN	CMP r8, #0x0000000D			;Compare r8 to 0xD
			BNE NOTYELLOW				;Dont pause
YELLOW		MOV r3, #0					;If button low, State = OFF
NOTYELLOW	CMP r8, #0x0000000B			;Compare r8 to 0xB
			BNE NOTRED					;Button not low
RED			MOV r1, #0					;If low, Reset num count
NOTRED		
			;check if loop count is the amount
			CMP r2, r9					;Compare to loop amount
			BEQ EXIT					;If equal go to EXIT
			B LOOP						;If not then loop again
EXIT		CMP r3, #0					;Check if supposed to be on or off
			BEQ RESET					;If off then reset without incrementing
			ADD r1, r1, r4				;If on then increment and reset
			B RESET						;Reset loop
	ENDP								;End of program
		
	ALIGN			
			
	END