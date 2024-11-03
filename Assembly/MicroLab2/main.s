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
;Pseudo code:
;Start
;btnState = OFF
;btnVal = 0
;BlinkState = 1 (can be 1, 2, 3)
;LED = 0 (off or on)
;Loop
;LowCounter = 0
;LoopCounter = 0
;Check Push-button
;If low, increment low counter
;If BlinkState == 3:
;	LED = !LED
;If loop counter less than 1000:
;Increment loop counter go back to check push button
;Else if loop counter == 1000:
;Reset loop counter and
;If high counter >500 && btnState == OFF: (send to )
;btnState = ON,
;and change to next Blink state 1-2-3-1-
;	If blink state == 1:
;		Blinkstate ++
;		LED = ON
;	Else if blink state == 2:
;		Blinkstate ++
;	Else blink state == 3:
;		Blinkstate = 1
;		LED = OFF
;	If high counter <= 500:
;		btnState == OFF
;Go back to Loop
;End
;*******************************************************************************


	INCLUDE core_cm4_constants.s
	INCLUDE stm32l476xx_constants.s
	
	AREA    main, CODE, READONLY
	EXPORT	__main
	ENTRY			
				
__main	PROC
		
    ; Enable the clock to GPIO Port A	and C
	LDR r0, =RCC_BASE	;Load reset and clock controll into r0
	LDR r1, [r0, #RCC_AHB2ENR]	;Load Base with specific offset into r1
	ORR r1, r1, #RCC_AHB2ENR_GPIOAEN	;Or r1 with this mask
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
	LDR r5, =GPIOC_BASE			;Load r0 with GPIOA
	LDR r6, [r5, #GPIO_MODER]	;Load r0 with offset into r1
	AND r6, r6, #0xF3FFFFFF		;r1 = r1 & 0xFFFFF3FF
	;ORR r6, r6, #0x00000000		;r1 = r1 | 0x00000400
	STR r6, [r5, #GPIO_MODER]	;store r1 into r0 + offset of MODER
;Set up some variables
			MOV r7, #0		;btnVal = 0
			MOV r8, #1		;BlinkState(r8) = 1
			MOV r9, #0		;LED = OFF(0)
BUTTONOFF	MOV r2, #0		;btnState(r2) = OFF(0)
LOOP		MOV r3, #0		;LowCnt = 0
			MOV r4, #0		;LoopCnt = 0
			;Read Push-button state into PBState
CHECK_BUT	LDR r5, =GPIOC_BASE		;Load r5 with GPIOC
			LDR r6, [r5, #GPIO_IDR]	;Load r6 with Base + offset
			AND r6, r6, #0x00002000	;AND mask with only the spot to read
			CMP r6, #0x00002000		;If not low:
			BEQ	NOTLOW				;skip incrementinglow	
LOW			ADD r3, r3, #1			;if it is low, LowCnt ++
NOTLOW		CMP r8, #3				;If BlinkState == 3:
			BNE NOTBLINKING
						;LED = !LED (blinking)
BLINKING	ADD r9, r9, #0x00000020 	;change LED bit to !LED bit
			AND r9, r9, #0x00000020		;Mask out any other values (the carry)
			STR r9, [r0, #GPIO_ODR]		;store r1 into r0 + offset of ODR turning LED on or off			
NOTBLINKING	ADD r4, r4, #1				;Increment loop counter
			CMP r4, #1000				;If LoopCnt < 1000:
			BLS CHECK_BUT				;Go to CHECK_LED
RESET		MOV r4, #0					;Reset loop counter and
			CMP r3, #500				;If low counter <500: 
			BLS BUTTONOFF				;Go to ButtonOff
			CMP r2, #1					;If btnState == ON: 
			BEQ	LOOP					;Go to Loop
			MOV r2, #1					;if off then btnState = ON
			;(Change to next Blink state 1-2-3-1-)
ONE			CMP r8, #1					;If blink state != 1: Go to Two
			BNE TWO
			ADD r8, r8, #1				;Blinkstate ++
						;LED = ON
			MOV r1, #0x00000020			;r1 = 0x00000020
			STR r1, [r0, #GPIO_ODR]		;store r1 into r0 + offset of ODR		
			B LOOP						;Go to Loop
TWO			CMP r8, #2					;(Else) if blinkState != 2:
			BNE THREE					;Go to Three
			ADD r8, r8, #1				;Blinkstate ++
			B LOOP						;Go to Loop
THREE		MOV r8, #1					;Blinkstate = 1
						;LED = OFF
			MOV r1, #0x00000000			;r1 = 0x00000000
			STR r1, [r0, #GPIO_ODR]		;store r1 into r0 + offset of ODR
			B LOOP						;Go to Loop

	ENDP
					
	ALIGN			

	END
