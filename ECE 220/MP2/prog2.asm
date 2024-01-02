;Noah DuVal
;
;663669152
;
;This program is to run as a calculator that takes inputs in reverse Polish notation
;and outputs the result of the calculation onto the screen as well as stores the result in R5
;The calculator uses stacks and subroutines in order to complete the goal in mind. 
;To start the code I first started with creating the subroutines for all of the opperators
;Once that was done then I had to create the main part of the code that was responsible
;for sorting the inputs and determing when to call what subroutines and ultimately manipulate the
;many little piece that make this puzzle complete. 



.ORIG x3000

	AND R0, R0, #0		;Hold the input
	AND R1, R1, #0		;Used to hold ascii values
	AND R2, R2, #0		;Temp register
	AND R3, R3, #0		;changes as it goes, but mostly used as inputs for subroutines
	AND R4, R4, #0		;same as r3
	AND R5, R5, #0		;Holds the result
	AND R6, R6, #0		
	AND R7, R7, #0
	
INPUT				;Start of main loop that gather the inputs

	GETC
	OUT			;echos input that is stored in R0
	
	AND R1, R1, #0
	LD R1, EQUAL_SIGN
	ADD R1, R0, R1
	BRz ONLY_ONE		;Is input '='

	AND R1, R1, #0
	LD R1, SPACE
	ADD R1, R0, R1
	BRz INPUT		;Is input a space	
	

;;;;;;;;;;;;;;;;;;;;;;;;;;SECOND ATTEMPT	

CHECK
	ST R0, CHECK_SAVER0
	AND R1, R1, #0
	LD R1, MULT_SIGN
	ADD R1, R0, R1
	BRz S_MULT		;Is input *

	LD R1, PLUS_SIGN
	ADD R1, R0, R1
	BRz S_PLUS		;Is input +

	LD R1, MIN_SIGN
	ADD R1, R0, R1
	BRz S_MIN		;Is input -

	LD R1, DIV_SIGN
	ADD R1, R0, R1
	BRz S_DIV		;Is input /


	LD R0, CHECK_SAVER0
	LD R1, ZERO
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #0
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 0

	LD R0, CHECK_SAVER0
	LD R1, ONE
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #1
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 1

	LD R0, CHECK_SAVER0
	LD R1, TWO
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #2
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 2

	LD R0, CHECK_SAVER0
	LD R1, THREE
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #3
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 3

	LD R0, CHECK_SAVER0
	LD R1, FOUR
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #4
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 4

	LD R0, CHECK_SAVER0
	LD R1, FIVE
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #5
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 5

	LD R0, CHECK_SAVER0
	LD R1, SIX
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #6
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 6

	LD R0, CHECK_SAVER0
	LD R1, SEVEN
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #7
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 7

	LD R0, CHECK_SAVER0
	LD R1, EIGHT
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #8
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 8

	LD R0, CHECK_SAVER0
	LD R1, NINE
	ADD R1, R0, R1
	AND R0, R0, #0
	ADD R0, R0, #9
	ADD R1, R1, #0
	BRz S_NUMB		;Is input 9

	LD R0, CHECK_SAVER0
	LD R1, EXP_SIGN
	ADD R1, R0, R1
	BRz S_EXP		;Is input ^

	BRnzp INVALID		;no valide char entered

S_NUMB				;Input was a number and is pushed on stack
	JSR PUSH
	BRnzp INPUT

S_MULT				;Pops values into R3 and R4
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp INVALID		;Checks underflow

	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp INVALID		;Checks underflow

	JSR MUL			;performs mult
	BRnzp APP_PUSH		;Pushes result

S_PLUS				;same as above, but with addition
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR PLUS
	BRnzp APP_PUSH

S_MIN				;same idea follows her and for rest of opps
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR MIN
	BRnzp APP_PUSH

S_DIV
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR DIV
	BRnzp APP_PUSH

S_EXP
	JSR POP
	ADD R4, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp INVALID

	JSR EXP
	BRnzp APP_PUSH

APP_PUSH			;pushes the result to the stack and returns to the input
	
	JSR PUSH
	BRnzp INPUT
	
	

ONLY_ONE			;Checks that there is only one left in stack
	
	ADD R3, R3, #0
	ADD R4, R4, #0
	ADD R6, R6, #0
	LD R3, STACK_TOP
	LD R4, STACK_START
	
	NOT R3, R3
	ADD R3, R3, #1
	ADD R6, R3, R4		;STACK_START - STACK_TOP = 1 ?
	ADD R6, R6, #-1
	BRz ONE_LEFT		;Only one left in stack
	
INVALID				;Prints 'invalid expression'

	AND R0, R0, #0
	LEA R0, STRING	
	PUTS
	
	BRnzp DONE

ONE_LEFT			;Only one left in the stack
	
	JSR POP
	AND R5, R5, #0
	ADD R5, R0, #0
	AND R3, R3, #0
	ADD R3, R0, #0
	JSR PRINT_HEX		;Prints final result to monitor

DONE	
	HALT			;end of prog



SPACE		.FILL #-32		;neg ascii values
MULT_SIGN	.FILL #-42
PLUS_SIGN	.FILL #-43
MIN_SIGN	.FILL #-45
DIV_SIGN	.FILL #-47
ZERO		.FILL #-48
ONE		.FILL #-49
TWO		.FILL #-50
THREE		.FILL #-51
FOUR		.FILL #-52
FIVE		.FILL #-53
SIX		.FILL #-54
SEVEN		.FILL #-55
EIGHT		.FILL #-56
NINE		.FILL #-57
EQUAL_SIGN	.FILL #-61
EXP_SIGN	.FILL #-94
STRING		.STRINGZ	" INVALID EXPRESSION"

CHECK_SAVER0 .BLKW #1		;stores R0



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

	ST R7, HEX_SAVER7
	AND R0, R0, #0		;R0 will be used to print
	AND R1, R1, #0		;R1 will be used as the digit counter
	AND R2, R2, #0		;R2 will be used as the bit counter
	AND R4, R4, #0		;R4 will be used to store the digit
	;LDI R3, HEX_SAVE_R3	;Loads count into R3

	ADD R1, R1, #4		;Sets the digit counter to 4
LOOP
	BRnz FINAL		;Jumps back to line printing;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;out of print hex
	AND R2, R2, #0		;Resets counter for next time around
	AND R4, R4, #0		;Resets 'digit'
	ADD R2, R2, #4		;Bit counter
GOT4
	BRnz	NEXT		;4 bits have been received from R3

	ADD R4, R4, R4		;Shifts the digit left
	ADD R3, R3, #0		;Allows BR to function on first digit

	BRzp	FALSE		;Add 0 if R3 MSB is 0
	ADD R4, R4, #1		;Add 1 if R3 MSB is 1
FALSE
	ADD R3, R3, R3		;Left shift in R3
	ADD R2, R2, #-1		;decrement bit counter
	BRnzp 	GOT4		;Next digit
NEXT
	ADD R4, R4, #-9		;Set up for <=9
	BRnz ADDZERO		;Add '0' if digit is <= 9
	ADD R4, R4, #9		;Restore 9 for BR
	ADD R4, R4, #10		;Add 65-10 if digit is > 9
	ADD R4, R4, #10
	ADD R4, R4, #10
	ADD R4, R4, #10
	ADD R4, R4, #10
	ADD R4, R4, #10
	ADD R4, R4, #5
	ADD R4, R4, #-10
	ADD R0, R0, R4		;Print
	OUT
	BRnzp	CLOSE
ADDZERO
	ADD R4, R4, #9
	ADD R4, R4, #10		;Adds '0' in ascii values
	ADD R4, R4, #10
	ADD R4, R4, #10
	ADD R4, R4, #10
	ADD R4, R4, #8
	ADD R0, R0, R4
	OUT			;Out the digit before going onto the next
CLOSE
	AND R0, R0, #0
	ADD R1, R1, #-1		;decrement the digit counter
	BRnzp LOOP		;End of subset, loops back to start

FINAL
	LD R7, HEX_SAVER7
	RET

HEX_SAVER7 .BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;

;not used
;
EVALUATE

;your code goes here




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	
	ADD R0, R3, R4		;simple add

	RET

PLUS_SAVER3	.BLKW #1	;
PLUS_SAVER4	.BLKW #1	;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

	ST R3, MIN_SAVER3
	ST R4, MIN_SAVER4

;	BRn NEGATIVE		;X - ( -Y) = X+Y
;	AND R5, R5, #0
;REDO	ADD R3, R3, #-1
;	ADD R4, R4, #-1
;	BRp REDO
;	ADD R0, R3, #0
;	BRnzp MIND
;NEGATIVE
;	ADD R3, R3, #1
;	ADD R4, R4, #1
;	BRn NEGATIVE
;	ADD R0, R3, #0
;
;MIND

	NOT R4, R4		;negates then adds
	ADD R4, R4, #1
	ADD R0, R3, R4


	LD R3, MIN_SAVER3
	LD R4, MIN_SAVER4

	RET

MIN_SAVER3	.BLKW #1	;
MIN_SAVER4	.BLKW #1	;
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here

	ST R7, MUL_SAVER7
	ST R5, MUL_SAVER5
	ST R2, MUL_SAVER2
	ST R3, MUL_SAVER3
	;BRz ZER
	ST R4, MUL_SAVER4
	;BRz ZER
	AND R5, R5, #0
	ADD R5, R3, #0
	ADD R4, R4, #-1		;counts times to add
	
MULT	ADD R3, R3, R5		;repeated addition
	ADD R4, R4, #-1		;decrements counter
	BRp	MULT
	
	ADD R0, R3, #0
	
	LD R2, MUL_SAVER2
	LD R3, MUL_SAVER3
	LD R4, MUL_SAVER4
	LD R5, MUL_SAVER5
	LD R7, MUL_SAVER7

	RET	

;ZER
;	AND R0, R0, #0
;	RET

MUL_SAVER5	.BLKW #1	;
MUL_SAVER2	.BLKW #1	;
MUL_SAVER3	.BLKW #1	;
MUL_SAVER4	.BLKW #1	;
MUL_SAVER7	.BLKW #1	;	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	
	ST R3, DIV_SAVER3
	ST R4, DIV_SAVER4
;	AND R5, R5, #0
;
;DLOOP	
;	ADD R5, R5, #1
;	JSR MIN
;	AND R3, R3, #0
;	ADD R3, R0, #0
;	BRz RETURN
;	BRn SKIP
;	BRp DLOOP
;
;SKIP	
;	ADD R5, R5, #-1
;	
;;RETURN
;	
;	ADD R0, R5, #0
;

	NOT R2, R4		;repeated subtraction
	ADD R2, R2, #1
	AND R0, R0, #0
	ADD R0, R0, #-1
DIV_LOOP
	ADD R0, R0, #1
	ADD R3, R3, R2
	BRzp DIV_LOOP
	
	LD R3, DIV_SAVER3
	LD R4, DIV_SAVER4

	RET

DIV_SAVER3	.BLKW #1	;
DIV_SAVER4	.BLKW #1	;
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

	ST R2, EXP_SAVER2	
	ST R3, EXP_SAVER3
	ST R4, EXP_SAVER4
	ST R7, EXP_SAVER7
	AND R5, R5, #0
	AND R2, R2, #0

	ADD R5, R4, #-1
	AND R4, R4, #0
	ADD R4, R3, #0

REPEAT				;repeated mult using subroutine

	JSR MUL			;nested sub
	ADD R2, R0, #0
	ADD R5, R5, #-1
	BRp	REPEAT
	
	AND R0, R0, #0
	ADD R0, R2, #0		;moves result form R2 to R0
	
	LD R3, EXP_SAVER3
	LD R4, EXP_SAVER4
	LD R7, EXP_SAVER7
	LD R2, EXP_SAVER2

	RET

EXP_SAVER3	.BLKW #1	;
EXP_SAVER4	.BLKW #1	;
EXP_SAVER7	.BLKW #1	;	
EXP_SAVER2	.BLKW #1	;
EP_SAVER4	.BLKW #1	;
EP_SAVER7	.BLKW #1	;
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
HEX_SAVE_R3	.BLKW #1	; Mem save for R3
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
