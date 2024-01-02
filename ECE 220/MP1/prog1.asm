;Noah DuVal  
;663669152

;This program counts the occurrences of letters and non letters and places
;them into a histogram to which is printed on the monitor at the end of the program.
;In order to start to get a basic structure and or plan for this program
;I started with writing over the flowchart. I looked at the boxes and 
;wrote the lines of code that would perform that function as well as creating
;all of loops and directions the code will take as it flows its way through the chart.
;Next I added the code to create the newlines and characters and simply had to place the 
;count of the letter inside of that loop creating seamless algorithm that is complete. 




	.ORIG	x3000		; starting address is x3000



; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).

; The string starts at x4000.

; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).

; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register


	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

	AND R0, R0, #0		;Used to OUT CHAR
	AND R3, R3, #0		;Used to point hist addr
	AND R5, R5, #0		;Used to hold Char
	AND R6, R6, #0		;Used to count lines

	LD R5, CHAR_START	;Loads first char
	LD R6, NUM_BINS		;Loads number of bins
	LD R3, HIST_ADDR	;Loads start of count 

NEW_LINES
			
	ADD R0, R0, #10		;Prints newline
	OUT

	AND R0, R0, #0		;Prints Char
	ADD R0, R5, #0 		
	OUT
	
	AND R0, R0, #0		;Prints space
	LD R0, SPACE	
	OUT

	BRnzp PRINT_HEX		;Prints the count

INCREMENT

	ADD R5, R5, #1		;Increments character to be printed
	ADD R6, R6, #-1		;Decrements lines to be printed
	ADD R3, R3, #1		;Increments count pointer

	BRp NEW_LINES

	BRnzp DONE



PRINT_HEX

	AND R0, R0, #0		;R0 will be used to print
	AND R1, R1, #0		;R1 will be used as the digit counter
	AND R2, R2, #0		;R2 will be used as the bit counter
	AND R4, R4, #0		;R4 will be used to store the digit
	

	ADD R1, R1, #4		;Sets the digit counter to 4
LOOP
	BRnz INCREMENT		;Jumps back to line printing
	AND R2, R2, #0		;Resets counter for next time around
	AND R4, R4, #0		;Resets 'digit'
	ADD R2, R2, #4		;Bit counter
GOT4
	BRnz	NEXT		;4 bits have been received from R3

	ADD R4, R4, R4		;Shifts the digit left
	ADD R3, R3, #0		;Allows BR to function on first digit
	
	BRzp	FALSE		;Add 0 if R3 MSB is 0
	ADD R4, R4, #1		:Add 1 if R3 MSB is 1
FALSE
	ADD R3, R3, R3		;Left shift in R3
	ADD R2, R2, #1		;Increment bit counter
	BRnzp 	GOT4		;Next digit
NEXT
	ADD R4, R4, #-9		;Set up for <=9
	BRnz ADDZERO		;Add '0' if digit is <= 9
	ADD R4, R4, #9
	ADD R4, R4, #65		;Add 65-10 if digit is > 9
	ADD R4, R4, #-10
	ADD R0, R0, R4
	OUT
	BRnzp	CLOSE
ADDZERO
	ADD R4, R4, #9
	ADD R4, R4, #48
	ADD R0, R0, R4
	OUT			;Out the digit before going onto the next
CLOSE
	AND R0, R0, #0
	ADD R1, R1, #1		;Increment the digit counter
	BRnzp LOOP		;End of subset, loops back to start

DONE	HALT			;End of Program


				; the data needed by the program

NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
CHAR_START	.FILL X40
SPACE		.FILL x20	


; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING	.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



			

	.END
